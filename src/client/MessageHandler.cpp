//
// Created by diguie_t on 11/20/2017.
//

#include "WebCore.hh"
#include "MessageHandler.hh"

bool MessageHandler::OnQuery(CefRefPtr<CefBrowser> browser,
                                             CefRefPtr<CefFrame> frame,
                                             int64 query_id,
                                             const CefString &request,
                                             bool persistent,
                                             CefRefPtr<CefMessageRouterBrowserSide::Callback> callback) {
    // Only handle messages from the startup URL.
	this->_webCore->getMvcHandler()->getControllerHandler()->onQuery(browser, frame, query_id, request, persistent, callback);
    //const std::string &url = frame->GetURL();
	//if (url.find(_startupUrl) != 0)
	//	return false;
	return (true); // todo check the diff between true & false
}

MessageHandler::MessageHandler(const CefString &startup_url, WebCore *webCore) :
		_startupUrl(startup_url),
		_webCore(webCore) {
}
