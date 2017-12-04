#ifndef BROWSER_CLIENT_HH
#define BROWSER_CLIENT_HH

#include "NetworkHandler.hh"
#include "include/cef_client.h"
#include "include/wrapper/cef_message_router.h"
#include "mvc/MvcHandler.hh"

class RenderHandler;

// for manual render handler
class BrowserClient : public CefClient, public CefKeyboardHandler,
					  public CefDisplayHandler,
					  public CefLifeSpanHandler,
					  public CefRequestHandler
{
private:
	CefRefPtr<CefMessageRouterBrowserSide> message_router_;
	scoped_ptr<CefMessageRouterBrowserSide::Handler> message_handler_;
	// Track the number of browsers using this Client.
	int browser_ct_;
	WebCore *_webCore;


public:
	explicit BrowserClient(WebCore *webCore);
	CefRefPtr<CefRenderHandler> GetRenderHandler() override;
	CefRefPtr<CefDisplayHandler> GetDisplayHandler() override;
	CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;
	CefRefPtr<CefRequestHandler> GetRequestHandler() override;

	bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
								  CefProcessId source_process,
								  CefRefPtr<CefProcessMessage> message) override;

	CefRefPtr<CefResourceHandler> GetResourceHandler(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request) override;

	void OnTitleChange(CefRefPtr<CefBrowser> browser,
					   const CefString &title) override;
	void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
	bool DoClose(CefRefPtr<CefBrowser> browser) override;
	void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;
	bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
				   CefRefPtr<CefRequest> request, bool is_redirect) override;
	void OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser,
								   TerminationStatus status) override;

private:
	IMPLEMENT_REFCOUNTING(BrowserClient);
	DISALLOW_COPY_AND_ASSIGN(BrowserClient);
};
#endif //BROWSER_CLIENT_HH
