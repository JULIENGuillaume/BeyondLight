﻿#ifndef WEB_CORE_HH
#define WEB_CORE_HH

#include <string>
#include <vector>
#include <NetworkHandler.hh>
#include "include/cef_client.h"

class BrowserClient;
class RenderHandler;
class MvcHandler;

class WebCore {
private:
    int _mouseX;
    int _mouseY;
    int _curMouseMod;

    CefRefPtr<CefBrowser> _browser;
    CefRefPtr<BrowserClient> _client;
	CefRefPtr<RenderHandler> _renderHandler; // todo RAII
	std::shared_ptr<MvcHandler> _mvcHandler;
	std::shared_ptr<network::client::NetworkHandler> _networkHandler;
public:
	WebCore(const std::string &url, std::shared_ptr<network::client::NetworkHandler> networkHandler);
	~WebCore();

	void setMvcHandler(std::shared_ptr<MvcHandler> mvcHandler);
	void reshape(int w, int h);

	void mouseMove(double x, double y, int entered);
	void mouseClick(CefBrowserHost::MouseButtonType btn, bool mouse_up, int mods);
	void keyPress(int key, int scancode, int action, int mods);
	void mouseScroll(int x, int y);
	void changeUrl(const std::string &url);
	void charPress(unsigned int key);
	void paste();
	void copy();
	void selectAll();
	void cut();
	void reload(bool ignoreCache);

	CefRefPtr<RenderHandler> getRenderHandler() const;
	CefRefPtr<const CefBrowser> getBrowser() const;
	CefRefPtr<const BrowserClient> getClient() const;
	std::shared_ptr<const network::client::NetworkHandler> getNetworkHandler() const;
	std::shared_ptr<const MvcHandler> getMvcHandler() const;

	CefRefPtr<CefBrowser> getBrowser();
	CefRefPtr<BrowserClient> getClient();
	std::shared_ptr<network::client::NetworkHandler> getNetworkHandler();
	std::shared_ptr<MvcHandler> getMvcHandler();
};

#endif // WEB_CORE_HH