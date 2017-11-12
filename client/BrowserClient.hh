#ifndef BROWSER_CLIENT_HH
#define BROWSER_CLIENT_HH

#include "include/cef_client.h"

class RenderHandler;

// for manual render handler
class BrowserClient : public CefClient, public CefKeyboardHandler
{
private:
    CefRefPtr<CefRenderHandler> _renderHandler;

public:
	BrowserClient(RenderHandler *renderHandler);
	virtual CefRefPtr<CefRenderHandler> GetRenderHandler() override;

	bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent &event,
					   MSG *os_event, bool *is_keyboard_shortcut) override;

	bool OnKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent &event,
					MSG *os_event) override;

IMPLEMENT_REFCOUNTING(BrowserClient);
};
#endif //BROWSER_CLIENT_HH
