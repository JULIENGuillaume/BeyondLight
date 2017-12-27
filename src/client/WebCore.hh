﻿#ifndef WEB_CORE_HH
#define WEB_CORE_HH

#include <string>
#include <vector>
#include <ClientNetworkHandler.hh>
#include "include/cef_client.h"

namespace bl {
	class BrowserClient;

	class RenderHandler;
	namespace mvc {
		class MvcHandler;
	}
}
namespace bl {
	class WebCore { // fixme this can be null and cause a crash, for example in onClick func, investigate wth this class isn't deleted correctly
	public:
		WebCore(
				const std::string &url,
				std::shared_ptr<network::client::ClientNetworkHandler> networkHandler
		);
		~WebCore();
		void reshape(
				int w,
				int h
		);
		void mouseMove(
				double x,
				double y,
				int entered
		);
		void mouseClick(
				CefBrowserHost::MouseButtonType btn,
				bool mouse_up,
				int mods
		);
		void keyPress(
				int key,
				int scancode,
				int action,
				int mods
		);
		void mouseScroll(
				int x,
				int y
		);
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
		std::shared_ptr<const network::client::ClientNetworkHandler>
		getNetworkHandler() const;
		std::shared_ptr<const mvc::MvcHandler> getMvcHandler() const;
		CefRefPtr<CefBrowser> getBrowser();
		CefRefPtr<BrowserClient> getClient();
		std::shared_ptr<network::client::ClientNetworkHandler> getNetworkHandler();
		std::shared_ptr<mvc::MvcHandler> getMvcHandler();
	private:
		int m_mouseX;
		int m_mouseY;
		unsigned int m_curMouseMod;
		CefRefPtr<CefBrowser> m_browser;
		CefRefPtr<BrowserClient> m_client;
		CefRefPtr<RenderHandler> m_renderHandler;
		std::shared_ptr<mvc::MvcHandler> m_mvcHandler;
		std::shared_ptr<network::client::ClientNetworkHandler> m_networkHandler;
		std::chrono::time_point<std::chrono::system_clock> m_chrono;
	};
}
#endif // WEB_CORE_HH