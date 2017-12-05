//
// Created by diguie_t on 11/26/2017.
//

#include "ControllerFactory.hpp"
#include "ControllerHandler.hh"
#include "LoginController.hh"
#include "IndexController.hh"

std::shared_ptr<IControllerFactory> ControllerHandler::getRouteControllerFactory(const std::string &route) {
    auto pair = this->getData(route);
    if (pair.first) {
        return (pair.second);
    }
    return (nullptr);
}

void ControllerHandler::changeRoute(const std::string &baseRoute, const std::string &subRoute) {
    std::shared_ptr<IControllerFactory> pFactory = this->getRouteControllerFactory(baseRoute);
    if (pFactory == nullptr) {
        std::cerr << "invalid route: " << baseRoute << std::endl;
    }
    this->_currentController.reset();
    this->_currentController = nullptr;
    this->_curBaseRoute = baseRoute;
    this->_curSubRoute = subRoute;
    this->_currentController = pFactory->build(_modelHandler, this->_webCore);
}

ControllerHandler::ControllerHandler(std::shared_ptr<ModelHandler> modelHandler, std::weak_ptr<WebCore> webCore) {
    this->_modelHandler = modelHandler;
    this->_webCore = webCore;
    this->_currentController = nullptr;
    this->_data = {
            {"/login", std::shared_ptr<ControllerFactory<LoginController>>(new ControllerFactory<LoginController>())},
            {"/index", std::shared_ptr<ControllerFactory<IndexController>>(new ControllerFactory<IndexController>())}
    };
    this->changeRoute("/login", "");
}

void ControllerHandler::onQuery(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame, int64 query_id,
                                const CefString &request, bool persistent,
                                CefRefPtr<CefMessageRouterBrowserSide::Callback> callback) {
    // todo check message path
    if (this->_currentController == nullptr /* or is invalid controller */) {
        callback->Failure(0, "Invalid route");
    } else {
        auto newRoute = this->_currentController->onQuery(browser, frame, query_id, request, persistent, callback);
        if (!newRoute.empty())
        this->changeRoute(newRoute, "");
    }
}

void ControllerHandler::onFrameEnd() {
    if (this->_currentController != nullptr) {
        this->_currentController->onFrameEnd();
    }
}
