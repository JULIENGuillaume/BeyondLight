﻿#ifndef BROWSER_CLIENT_HH
#define BROWSER_CLIENT_HH

#include "ClientNetworkHandler.hh"
#include "include/cef_client.h"
#include "include/wrapper/cef_message_router.h"
#include "mvc/MvcHandler.hh"

class RenderHandler;
namespace bl {
	// for manual render handler
	class BrowserClient :
			public CefClient,
			public CefKeyboardHandler,
			public CefDisplayHandler,
			public CefLifeSpanHandler,
			public CefRequestHandler,
			public CefLoadHandler {
	public:
		explicit BrowserClient(WebCore *webCore);
		CefRefPtr<CefRenderHandler> GetRenderHandler() override;
		CefRefPtr<CefDisplayHandler> GetDisplayHandler() override;
		CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;
		CefRefPtr<CefRequestHandler> GetRequestHandler() override;
		bool OnProcessMessageReceived(
				CefRefPtr<CefBrowser> browser,
				CefProcessId source_process,
				CefRefPtr<CefProcessMessage> message
		) override;
		CefRefPtr<CefResourceHandler> GetResourceHandler(
				CefRefPtr<CefBrowser> browser,
				CefRefPtr<CefFrame> frame,
				CefRefPtr<CefRequest> request
		) override;
		void OnTitleChange(
				CefRefPtr<CefBrowser> browser,
				const CefString &title
		) override;
		void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
		bool DoClose(CefRefPtr<CefBrowser> browser) override;
		void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;
		bool OnBeforeBrowse(
				CefRefPtr<CefBrowser> browser,
				CefRefPtr<CefFrame> frame,
				CefRefPtr<CefRequest> request,
				bool is_redirect
		) override;
		void OnRenderProcessTerminated(
				CefRefPtr<CefBrowser> browser,
				TerminationStatus status
		) override;
		void OnLoadStart(
				CefRefPtr<CefBrowser> browser,
				CefRefPtr<CefFrame> frame,
				TransitionType transition_type
		) override;
		CefRefPtr<CefLoadHandler> GetLoadHandler() override;
		void OnLoadEnd(
				CefRefPtr<CefBrowser> browser,
				CefRefPtr<CefFrame> frame,
				int httpStatusCode
		) override;
	private:
		CefRefPtr<CefMessageRouterBrowserSide> m_message_router;
		scoped_ptr<CefMessageRouterBrowserSide::Handler> m_message_handler;
		// Track the number of browsers using this Client.
		int m_browser_ct;
		WebCore *m_webCore;
		IMPLEMENT_REFCOUNTING(BrowserClient);
		DISALLOW_COPY_AND_ASSIGN(BrowserClient);
	};
}
#endif //BROWSER_CLIENT_HH
