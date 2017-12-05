//
// Created by diguie_t on 12/3/2017.
//

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
    this->_webCore.lock()->getBrowser()->GetMainFrame()->LoadURL(_buildingsUrl);
    this->_needToInsertBuilding = true;
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
        this->_webCore.lock()->getBrowser()->GetMainFrame()->ExecuteJavaScript("createBuilding(1, \"lel\", 1, 42, 1337, 323, 12);", _buildingsUrl, 0);
    }
}
