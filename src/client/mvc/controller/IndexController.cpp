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
    return (std::string());
}

void IndexController::setWebCore(std::weak_ptr<WebCore> webCore) {
    webCore.lock()->getBrowser()->GetMainFrame()->LoadURL("file:///" + common::Toolbox::getApplicationDir() + "/../resources/html/index.html"); // todo trouver un moyen de changer la route du controlleurhandler depuis ici
}
