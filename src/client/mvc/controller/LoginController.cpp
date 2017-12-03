//
// Created by diguie_t on 12/3/2017.
//

#include "LoginController.hh"
#include "../../../common/Toolbox.hh"
#include "../../../common/NetworkWrapper.hh"

void LoginController::setModelHandler(std::shared_ptr<ModelHandler> modelHandler) {

}

void LoginController::onQuery(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                       int64 query_id, const CefString &request,
                       bool persistent,
                       CefRefPtr<CefMessageRouterBrowserSide::Callback> callback) {
    std::string message(request);
    if (message.find("login-connect") == 0) {
        this->handleLogin(browser, message.substr(std::string("login-connect").length()), callback);
    } else if (message.find("login-register") == 0) {
        this->handleRegister(browser, message.substr(std::string("login-register").length()), callback);
    } else {
        callback->Failure(0, "Unknown route");
    }
}

void LoginController::handleLogin(CefRefPtr<CefBrowser> browser, std::string message, CefRefPtr<CefMessageRouterBrowserSide::Callback> callback) {
    auto socket = NetworkWrapper::m_socket;

    std::vector<std::string> logInfo = common::Toolbox::split(message, ":");
    if (logInfo.size() != 2) {
        callback->Failure(0, "Please enter both your login and password");
    } else {
        socket->send("042:" + logInfo[0] + ":" + logInfo[1]);
        auto toks = common::Toolbox::split(socket->receive(), ":");
        std::cout << "Received " << toks[0] << " " << toks[1] << std::endl;
        if (!toks.empty() && std::atoi(toks[0].c_str()) == 123) {
            callback->Success("Login success");
            browser->GetMainFrame()->LoadURL(
                    "file:///" + common::Toolbox::getApplicationDir() + "/../resources/html/index.html");
        } else {
            callback->Failure(0, "Bad login or password");
        }

    }
}

void LoginController::handleRegister(CefRefPtr<CefBrowser> browser, std::string message, CefRefPtr<CefMessageRouterBrowserSide::Callback> callback) {
    auto socket = NetworkWrapper::m_socket;

    std::vector<std::string> logInfo = common::Toolbox::split(message, ":");
    if (logInfo.size() == 6) {
        socket->send("043:" + logInfo[0] + ":" + logInfo[1] + ":" + logInfo[2] + ":" + logInfo[3] + ":" + logInfo[4] + ":" + logInfo[5]);
        auto toks = common::Toolbox::split(socket->receive(), ":");
        std::cout << "Received " << toks[0] << " " << toks[1] << std::endl;
    }
}

void LoginController::setNetWorkHandler(std::shared_ptr<network::client::NetworkHandler> networkHandler) {
    this->_networkHandler = networkHandler;
}

