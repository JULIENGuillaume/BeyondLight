//
// Created by diguie_t on 11/11/2017.
//

#ifndef CEFOFFSCREEN_WEBCOREMANAGER_HH
#define CEFOFFSCREEN_WEBCOREMANAGER_HH

#include "include/cef_app.h"
#include "WebCore.hh"

class WebCoreManager : public CefApp, public CefRenderProcessHandler {
private:
    std::vector<std::shared_ptr<WebCore>> _browsers;
	CefRefPtr<CefMessageRouterRendererSide> message_router_;
	std::shared_ptr<network::client::NetworkHandler> _networkHandler;
	std::shared_ptr<MvcHandler> _mvcHandler;

public:
	explicit WebCoreManager(std::shared_ptr<network::client::NetworkHandler> networkHandler, std::shared_ptr<MvcHandler> mvcHandler);
	~WebCoreManager();

	bool setUp(int *exit_code);
	bool shutDown();

	void update();

	std::weak_ptr<WebCore> createBrowser(const std::string &url);
	void removeBrowser(std::weak_ptr<WebCore> web_core);

    void OnBeforeCommandLineProcessing(const CefString &process_type,
                                       CefRefPtr<CefCommandLine> command_line) override;

    CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override;

    void OnWebKitInitialized() override;

    void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                     CefRefPtr<CefV8Context> context) override;

    void OnContextReleased(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                      CefRefPtr<CefV8Context> context) override;

    void OnUncaughtException(CefRefPtr<CefBrowser> browser,
                             CefRefPtr<CefFrame> frame,
                             CefRefPtr<CefV8Context> context,
                             CefRefPtr<CefV8Exception> exception,
                             CefRefPtr<CefV8StackTrace> stackTrace) override;

    bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                  CefProcessId source_process,
                                  CefRefPtr<CefProcessMessage> message) override;

	/* void OnContextInitialized() override; CefBrowserProcessHandler */

	/* CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override; */

	void AddRef() const override; // fixme should use refcounting

	bool Release() const override; // fixme should use refcounting

	bool HasOneRef() const override; // fixme should use refcounting

private:
	//IMPLEMENT_REFCOUNTING(WebCoreManager); // fixme crashing me using this
	DISALLOW_COPY_AND_ASSIGN(WebCoreManager);
};


#endif //CEFOFFSCREEN_WEBCOREMANAGER_HH
