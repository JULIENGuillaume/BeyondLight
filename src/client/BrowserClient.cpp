#include <iostream>
#include <include/cef_v8.h>
#include <include/wrapper/cef_helpers.h>
#include "RenderHandler.hh"
#include "BrowserClient.hh"
#include "MessageHandler.hh"

namespace bl {
	BrowserClient::BrowserClient(WebCore *webCore) :
			m_webCore(
					webCore) { // todo improve
		this->m_browser_ct = 0;
	}

	CefRefPtr<CefRenderHandler> BrowserClient::GetRenderHandler() {
		return (this->m_webCore->getRenderHandler());
	}

	CefRefPtr<CefDisplayHandler> BrowserClient::GetDisplayHandler() {
		return (this);
	}

	CefRefPtr<CefLifeSpanHandler> BrowserClient::GetLifeSpanHandler() {
		return (this);
	}

	CefRefPtr<CefRequestHandler> BrowserClient::GetRequestHandler() {
		return (this);
	}

	void BrowserClient::OnTitleChange(
			CefRefPtr<CefBrowser> browser,
			const CefString &title
	) {
		CefDisplayHandler::OnTitleChange(browser, title);
	}

	void BrowserClient::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
		CEF_REQUIRE_UI_THREAD();
		if (!m_message_router) {
			// Create the browser-side router for query handling.
			CefMessageRouterConfig config;
			m_message_router = CefMessageRouterBrowserSide::Create(config);

			// Register handlers with the router.
			m_message_handler.reset(new MessageHandler("",
													   this->m_webCore)); // todo check startup_url
			m_message_router->AddHandler(m_message_handler.get(), false);
		}
		m_browser_ct++;
		CefLifeSpanHandler::OnAfterCreated(browser);
	}

	bool BrowserClient::DoClose(CefRefPtr<CefBrowser> browser) {
		return CefLifeSpanHandler::DoClose(browser);
	}

	void BrowserClient::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
		CEF_REQUIRE_UI_THREAD();
		if (--m_browser_ct == 0) {
			// Free the router when the last browser is closed.
			m_message_router->RemoveHandler(m_message_handler.get());
			m_message_handler.reset();
			m_message_router = NULL;
		}
		CefLifeSpanHandler::OnBeforeClose(browser);
	}

	bool BrowserClient::OnBeforeBrowse(
			CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefRequest> request,
			bool is_redirect
	) {
		CEF_REQUIRE_UI_THREAD();
		m_message_router->OnBeforeBrowse(browser, frame);
		return false;
	}

	void BrowserClient::OnRenderProcessTerminated(
			CefRefPtr<CefBrowser> browser,
			CefRequestHandler::TerminationStatus status
	) {
		CEF_REQUIRE_UI_THREAD();
		m_message_router->OnRenderProcessTerminated(browser);
	}

	bool BrowserClient::OnProcessMessageReceived(
			CefRefPtr<CefBrowser> browser,
			CefProcessId source_process,
			CefRefPtr<CefProcessMessage> message
	) {
		CEF_REQUIRE_UI_THREAD();
		return (m_message_router->OnProcessMessageReceived(browser,
														   source_process,
														   message));
	}

	CefRefPtr<CefResourceHandler>
	BrowserClient::GetResourceHandler(
			CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefRequest> request
	) {
		CEF_REQUIRE_IO_THREAD();

		//const std::string& url = request->GetURL();

		// This is a minimal implementation of resource loading. For more complex
		// usage (multiple files, zip archives, custom handlers, etc.) you might want
		// to use CefResourceManager. See the "resource_manager" target for an
		// example implementation.
		/*const std::string& resource_path = shared::GetResourcePath(url); todo
		if (!resource_path.empty())
			return shared::GetResourceHandler(resource_path); todo */

		return CefRequestHandler::GetResourceHandler(browser, frame, request);
	}

	void BrowserClient::OnLoadStart(
			CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefLoadHandler::TransitionType transition_type
	) {
		CefLoadHandler::OnLoadStart(browser, frame, transition_type);
	}

	CefRefPtr<CefLoadHandler> BrowserClient::GetLoadHandler() {
		return (this);
	}

	void BrowserClient::OnLoadEnd(
			CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			int httpStatusCode
	) {
		this->m_webCore->getMvcHandler()->getControllerHandler()->onFrameEnd();
		CefLoadHandler::OnLoadEnd(browser, frame, httpStatusCode);
	}
}