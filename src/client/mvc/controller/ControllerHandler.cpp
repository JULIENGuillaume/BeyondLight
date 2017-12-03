//
// Created by diguie_t on 11/26/2017.
//

#include "ControllerFactory.hhp"
#include "ControllerHandler.hh"
#include "LoginController.hh"

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
    this->_currentController = pFactory->build(_modelHandler, this->_networkHandler);
}

ControllerHandler::ControllerHandler(std::shared_ptr<ModelHandler> modelHandler, std::shared_ptr<network::client::NetworkHandler> networkHandler) {
    this->_modelHandler = modelHandler;
    this->_networkHandler = networkHandler;
    this->_currentController = nullptr;
    this->_data = {
            {"/login", std::shared_ptr<ControllerFactory<LoginController>>(new ControllerFactory<LoginController>())}
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
        this->_currentController->onQuery(browser, frame, query_id, request, persistent, callback);
    }
}
