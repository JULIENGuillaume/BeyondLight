//
// Created by diguie_t on 11/20/2017.
//

#include "MessageHandler.hh"
#include "../common/NetworkWrapper.hh"
#include "../common/Toolbox.hh"

bool MessageHandler::OnQuery(CefRefPtr<CefBrowser> browser,
                                             CefRefPtr<CefFrame> frame,
                                             int64 query_id,
                                             const CefString &request,
                                             bool persistent,
                                             CefRefPtr<CefMessageRouterBrowserSide::Callback> callback) {
    // Only handle messages from the startup URL.
    std::cout << "networkhandler test value: " << this->_networkHandler->test << std::endl; // todo remove debug
    auto socket = NetworkWrapper::m_socket;
    const std::string &url = frame->GetURL();
    if (url.find(_startupUrl) != 0)
        return false;

    const std::string &message_name = request;
    if (message_name.find(_mainRoute) == 0) {
        // Reverse the string and return.
        std::string result = message_name.substr(_mainRoute.length());
        std::vector<std::string> logInfo = common::Toolbox::split(result, ":");
        if (logInfo.size() != 2) {
            callback->Failure(0, "Please enter both your login and password");
        } else {
	        socket->send("042:" + logInfo[0] + ":" + logInfo[1]);
	        auto toks = common::Toolbox::split(socket->receive(), ":");
	        std::cout << "Received " << toks[0] << " " << toks[1] << std::endl;
	        if (!toks.empty() && std::atoi(toks[0].c_str()) == 123) {
		        callback->Success("Login success");
		        browser->GetMainFrame()->LoadURL("file:///" + common::Toolbox::getApplicationDir() + "/../resources/html/index.html");
	        } else {
		        callback->Failure(0, "Bad login or password");
	        }
		        
        } 
	    
	    /*else if (logInfo[0] == "root" && logInfo[1] == "root") {
            socket->send("042:" + logInfo[0] + ":" + logInfo[1]);
            std::cout << socket->receive() << std::endl;
            callback->Success("Login success");
            browser->GetMainFrame()->LoadURL("file:///" + Utils::getApplicationDir() + "/../client/html/index.html");
        } else {
            callback->Failure(0, "Bad login or password");
        }*/
        return true;
    }

    return false;
}

MessageHandler::MessageHandler(const CefString &startup_url, std::shared_ptr<network::client::NetworkHandler> networkHandler)
        : _startupUrl(startup_url), _networkHandler(networkHandler) {
}
