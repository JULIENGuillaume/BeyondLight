//
// Created by diguie_t on 12/3/2017.
//

#include <json.hpp>
#include "IndexController.hh"
#include "../../../common/Toolbox.hh"
#include "../../WebCore.hh"

const std::string IndexController::_buildingsUrl = "file:///" + common::Toolbox::getApplicationDir() + "/../resources/html/buildings.html";

IndexController::IndexController() :
    _needToInsertBuilding(false) {

}


void IndexController::setModelHandler(std::shared_ptr<ModelHandler> modelHandler) {

}

std::string IndexController::onQuery(CefRefPtr<CefBrowser> browser,
                              CefRefPtr<CefFrame> frame, int64 query_id,
                              const CefString &request, bool persistent,
                              CefRefPtr<CefMessageRouterBrowserSide::Callback> callback) {
    std::string message(request);
    if (message.find("index-buildings") == 0) {
        this->buildings(browser, frame, callback);
    } else if (message.find("index-overview") == 0) {
        this->overview(browser, frame, callback);
    }
    return (std::string());
}

void IndexController::setWebCore(std::weak_ptr<WebCore> webCore) {
    this->_webCore = webCore;
    overview(nullptr, nullptr, nullptr);
}

void IndexController::buildings(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame,
                                CefRefPtr<CefMessageRouterBrowserSide::Callback> callback) {

    if (callback != nullptr) {
        callback->Success(std::string());
    }

    this->_needToInsertBuilding = true;
    this->_webCore.lock()->getBrowser()->GetMainFrame()->LoadURL(_buildingsUrl);
}

void IndexController::overview(CefRefPtr<CefBrowser> browser,
                               CefRefPtr<CefFrame> frame,
                               CefRefPtr<CefMessageRouterBrowserSide::Callback> callback) {
    if (callback != nullptr) {
        callback->Success(std::string());
    }
    this->_webCore.lock()->getBrowser()->GetMainFrame()->LoadURL("file:///" + common::Toolbox::getApplicationDir() + "/../resources/html/index.html");
}

void IndexController::onFrameEnd() {
    if (this->_needToInsertBuilding) {
        this->_needToInsertBuilding = false;
        auto network = this->_webCore.lock()->getNetworkHandler();
        network->send("4242");
        std::string jsonReceived = network->getLine();
        std::cout << jsonReceived << std::endl;
        nlohmann::json building;
        try {
            building = nlohmann::json::parse(jsonReceived);
        } catch (...) {
            std::cerr << "json parse error" << std::endl;
            return ;
        }
        unsigned int id = building.at("id").get<unsigned int>();
        std::string name = building.at("name").get<std::string>();
        //std::cout << "After asking for buildings, got: " << network->getLine() << std::endl;
        std::string js = std::string("createBuilding(") + std::to_string(id) + ",\"" + name + "\", 1, 42, 1337, 323, 12);";
        this->_webCore.lock()->getBrowser()->GetMainFrame()->ExecuteJavaScript(js, _buildingsUrl, 0);
    }
}
