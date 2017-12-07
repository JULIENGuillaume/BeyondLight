//
// Created by diguie_t on 11/20/2017.
//

#ifndef CEFOFFSCREEN_MESSAGEHANDLER_HH
#define CEFOFFSCREEN_MESSAGEHANDLER_HH

#include <iostream>
#include "NetworkHandler.hh"
#include "include/wrapper/cef_message_router.h"
#include "mvc/MvcHandler.hh"

namespace bl {
	// http://www.magpcss.org/ceforum/viewtopic.php?f=17&t=12317 todo check this for improvement
	// Handle messages in the browser process.
	class MessageHandler : public CefMessageRouterBrowserSide::Handler {
	public:
		explicit MessageHandler(
				const CefString &startup_url,
				WebCore *webCore
		);
		bool OnQuery(
				CefRefPtr<CefBrowser> browser,
				CefRefPtr<CefFrame> frame,
				int64 query_id,
				const CefString &request,
				bool persistent,
				CefRefPtr<Callback> callback
		) override;
	private:
		const std::string m_mainRoute = "MainRoute";
		const CefString m_startupUrl;
		WebCore *m_webCore; // todo improve
		DISALLOW_COPY_AND_ASSIGN(MessageHandler);
	};
}
#endif //CEFOFFSCREEN_MESSAGEHANDLER_HH
