//
// Created by diguie_t on 12/3/2017.
//

#include "IndexController.hh"
#include "../../../common/Toolbox.hh"
#include "../../WebCore.hh"

IndexController::IndexController() {

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
    callback->Success(std::string());
    auto network = this->_webCore.lock()->getNetworkHandler();
	network->send("4242");
	std::cout << "After asking for buildings, got: " << network->getLine() << std::endl;
    this->_webCore.lock()->getBrowser()->GetMainFrame()->LoadURL("file:///" + common::Toolbox::getApplicationDir() + "/../resources/html/buildings.html");
}

void IndexController::overview(CefRefPtr<CefBrowser> browser,
                               CefRefPtr<CefFrame> frame,
                               CefRefPtr<CefMessageRouterBrowserSide::Callback> callback) {
    if (callback != nullptr) {
        callback->Success(std::string());
    }
    this->_webCore.lock()->getBrowser()->GetMainFrame()->LoadURL("file:///" + common::Toolbox::getApplicationDir() + "/../resources/html/index.html");
}