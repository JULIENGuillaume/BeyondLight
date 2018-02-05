//
// Created by diguie_t on 11/11/2017.
//

#ifndef CEFOFFSCREEN_WEBCOREMANAGER_HH
#define CEFOFFSCREEN_WEBCOREMANAGER_HH

#include "include/wrapper/cef_message_router.h"
#include "include/cef_app.h"
#include "WebCore.hh"

namespace bl {
	class WebCoreManager :
			public CefApp,
			public CefRenderProcessHandler {
	public:
		explicit WebCoreManager(
				std::shared_ptr<network::client::ClientNetworkHandler> networkHandler
		);
		~WebCoreManager() override; // todo check if we need or not to override
		void update();
		std::weak_ptr<WebCore> createBrowser(const std::string &url);
		void removeBrowser(std::weak_ptr<WebCore> web_core);
		void OnBeforeCommandLineProcessing(
				const CefString &process_type,
				CefRefPtr<CefCommandLine> command_line
		) override;
		CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override;
		void OnWebKitInitialized() override;
		void OnContextCreated(
				CefRefPtr<CefBrowser> browser,
				CefRefPtr<CefFrame> frame,
				CefRefPtr<CefV8Context> context
		) override;
		void OnContextReleased(
				CefRefPtr<CefBrowser> browser,
				CefRefPtr<CefFrame> frame,
				CefRefPtr<CefV8Context> context
		) override;
		void OnUncaughtException(
				CefRefPtr<CefBrowser> browser,
				CefRefPtr<CefFrame> frame,
				CefRefPtr<CefV8Context> context,
				CefRefPtr<CefV8Exception> exception,
				CefRefPtr<CefV8StackTrace> stackTrace
		) override;
		bool OnProcessMessageReceived(
				CefRefPtr<CefBrowser> browser,
				CefProcessId source_process,
				CefRefPtr<CefProcessMessage> message
		) override;
		void AddRef() const override;
		bool Release() const override;
		bool HasOneRef() const override;
	private:
		std::vector<std::shared_ptr<WebCore>> m_browsers;
		CefRefPtr<CefMessageRouterRendererSide> m_message_router;
		std::shared_ptr<network::client::ClientNetworkHandler> m_networkHandler;
		//IMPLEMENT_REFCOUNTING(WebCoreManager); // fixme crashing me using this. This line of the define crash -> "delete static_cast<const WebCoreManager*>(this);"
		DISALLOW_COPY_AND_ASSIGN(WebCoreManager);
	};
}
#endif //CEFOFFSCREEN_WEBCOREMANAGER_HH
