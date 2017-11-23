﻿#ifndef WEB_CORE_HH
#define WEB_CORE_HH

#include <string>
#include <vector>
#include "include/cef_client.h"
#include "BrowserClient.hh"
#include "NetworkHandler.hh"

class WebCore {
private:
    int _mouseX;
    int _mouseY;
    int _curMouseMod;

    CefRefPtr<CefBrowser> _browser;
    CefRefPtr<BrowserClient> _client;
	std::shared_ptr<network::client::NetworkHandler> _networkHandler;
    RenderHandler* _renderHandler;
public:
	WebCore(const std::string &url, std::shared_ptr<network::client::NetworkHandler> networkHandler);
	~WebCore();

	void reshape(int w, int h);

	void mouseMove(double x, double y, int entered);
	void mouseClick(CefBrowserHost::MouseButtonType btn, bool mouse_up, int mods);
	void keyPress(int key, int scancode, int action, int mods);
	void mouseScroll(int x, int y);
	void changeUrl(const std::string &url);
	RenderHandler* getRenderHandler() const;
	void charPress(unsigned int key);
	void paste();
	void copy();
	void selectAll();
	void cut();
	void reload(bool ignoreCache);
};

#endif // WEB_CORE_HH