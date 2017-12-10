//
// Created by diguie_t on 11/20/2017.
//

#include "WebCore.hh"
#include "MessageHandler.hh"

namespace bl {
	bool MessageHandler::OnQuery(
			CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			int64 query_id,
			const CefString &request,
			bool persistent,
			CefRefPtr<CefMessageRouterBrowserSide::Callback> callback
	) {
		return (this->m_webCore->getMvcHandler()->getControllerHandler()->onQuery(browser, frame, query_id, request, persistent, callback));
	}

	MessageHandler::MessageHandler(WebCore *webCore) :
			m_webCore(webCore) {
	}
}