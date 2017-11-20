//
// Created by diguie_t on 11/20/2017.
//

#include "MessageHandler.hh"
#include "Utils.hh"

bool MessageHandler::OnQuery(CefRefPtr<CefBrowser> browser,
                                             CefRefPtr<CefFrame> frame,
                                             int64 query_id,
                                             const CefString &request,
                                             bool persistent,
                                             CefRefPtr<CefMessageRouterBrowserSide::Callback> callback) {
    // Only handle messages from the startup URL.
    const std::string &url = frame->GetURL();
    if (url.find(_startupUrl) != 0)
        return false;

    const std::string &message_name = request;
    if (message_name.find(_mainRoute) == 0) {
        // Reverse the string and return.
        std::string result = message_name.substr(_mainRoute.length());
        std::vector<std::string> logInfo = Utils::split(result, ":");
        if (logInfo.size() != 2) {
            callback->Failure(0, "Please enter both your login and password");
        } else if (logInfo[0] == "root" && logInfo[1] == "root") {
            callback->Success("Login success");
            browser->GetMainFrame()->LoadURL("file:///" + Utils::getApplicationDir() + "/../html/index.html");
        } else {
            callback->Failure(0, "Bad login or password");
        }
        return true;
    }

    return false;
}

MessageHandler::MessageHandler(const CefString &startup_url)
        : _startupUrl(startup_url) {
}
