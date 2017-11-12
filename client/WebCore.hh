#ifndef WEB_CORE_HH
#define WEB_CORE_HH

#include <string>
#include <vector>
#include "include/cef_client.h"
#include "BrowserClient.hh"

class WebCore {
private:
    int _mouseX;
    int _mouseY;

    CefRefPtr<CefBrowser> _browser;
    CefRefPtr<BrowserClient> _client;

    RenderHandler* _renderHandler;
public:
	WebCore(const std::string &url);
	~WebCore();

	void reshape(int w, int h);

	void mouseMove(double x, int y);
	void mouseClick(CefBrowserHost::MouseButtonType btn, bool mouse_up);
	void keyPress(int key, int scancode, int action, int mods);

	RenderHandler* getRenderHandler() const;

	void charPress(unsigned int key);
};

#endif // WEB_CORE_HH