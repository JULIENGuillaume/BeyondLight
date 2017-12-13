#include <chrono>
#include <iostream>
#include <memory>
#include "GL/glew.h"
#include "WebCore.hh"
#include "RenderHandler.hh"
#include "include/cef_app.h"
#include "BrowserClient.hh"
#include "KeyMapper.hh"

namespace bl {
	WebCore::WebCore(
			const std::string &url,
			std::shared_ptr<network::client::NetworkHandler> networkHandler
	)
			:
			m_mouseX(0),
			m_mouseY(0),
			m_mvcHandler(new mvc::MvcHandler()),
			m_networkHandler(networkHandler),
			m_chrono(std::chrono::system_clock::now()) {
		m_renderHandler = new RenderHandler();
		m_renderHandler->resize(1280, 720);
		m_curMouseMod = 0;
		CefWindowInfo window_info;
		HWND hwnd = GetConsoleWindow();
		window_info.SetAsWindowless(hwnd);
		CefBrowserSettings browserSettings;
		browserSettings.webgl = STATE_DISABLED;
		browserSettings.plugins = STATE_DISABLED;
		browserSettings.javascript_close_windows = STATE_DISABLED;
		browserSettings.javascript_access_clipboard = STATE_DISABLED;
		browserSettings.javascript_dom_paste = STATE_DISABLED;
		browserSettings.local_storage = STATE_DISABLED;
		browserSettings.databases = STATE_DISABLED;
		browserSettings.universal_access_from_file_urls = STATE_DISABLED;
		browserSettings.web_security = STATE_DISABLED; // todo check if better way to solve has been blocked by CORS policy
		browserSettings.windowless_frame_rate = 60; // 30 is default
		m_client = new BrowserClient(this);
		m_browser = CefBrowserHost::CreateBrowserSync(window_info, m_client.get(),
													  url, browserSettings,
													  nullptr);
		this->m_mvcHandler->setWebCore(this);
	}

	WebCore::~WebCore() {
		m_browser->GetHost()->CloseBrowser(true);
		CefDoMessageLoopWork();
		m_browser = nullptr;
		m_client = nullptr;
	}

	void WebCore::reshape(
			int w,
			int h
	) {
		m_renderHandler->resize(w, h);
		m_browser->GetHost()->WasResized();
	}

	void WebCore::mouseMove(
			double x,
			double y,
			int entered
	) {
		this->m_mouseX = static_cast<int>(x);
		this->m_mouseY = static_cast<int>(y);
		CefMouseEvent mouseEvent;
		mouseEvent.x = static_cast<int>(x);
		mouseEvent.y = static_cast<int>(y);
		mouseEvent.modifiers = this->m_curMouseMod;
		bool mouseLeave = entered == 0;
		m_browser->GetHost()->SendMouseMoveEvent(mouseEvent, mouseLeave);
	}

	void WebCore::mouseClick(
			CefBrowserHost::MouseButtonType btn,
			bool mouse_up,
			int mods
	) {
		static int count = 0;
		this->m_curMouseMod = KeyMapper::cefButtonToEventFlag(btn);
		CefMouseEvent evt;
		evt.x = m_mouseX;
		evt.y = m_mouseY;
		evt.modifiers = this->m_curMouseMod;
		if (!mouse_up) {
			auto now = std::chrono::system_clock::now();
			double diff_ms = std::chrono::duration<double, std::milli>(
					now - m_chrono).count();
			m_chrono = now;
			if (diff_ms > 10 && diff_ms < 200) {
				++count;
			} else {
				count = 1;
			}
		}
		m_browser->GetHost()->SendMouseClickEvent(evt, btn, mouse_up, count);
	}

	void WebCore::charPress(unsigned int key) {
		CefKeyEvent evt;
		evt.type = KEYEVENT_CHAR;
		evt.windows_key_code = key;
		evt.character = static_cast<short>(key);
		evt.modifiers = 0;
		evt.native_key_code = key;
		evt.unmodified_character = static_cast<short>(key);
		this->m_browser->GetHost()->SendKeyEvent(evt);
	}

	void WebCore::keyPress(
			int key,
			int scancode,
			int action,
			int mods
	) {
		CefKeyEvent event;
		unsigned int nativeKey = KeyMapper::glfwKeyToNative(key);
		event.windows_key_code = nativeKey;
		event.modifiers = 0;
		event.native_key_code = nativeKey;
		event.unmodified_character = static_cast<short>(nativeKey);
		event.type = KeyMapper::glfwActionToCef(action);
		m_browser->GetHost()->SendKeyEvent(event);
	}

	CefRefPtr<RenderHandler> WebCore::getRenderHandler() const {
		return (this->m_renderHandler);
	}

	void WebCore::mouseScroll(
			int x,
			int y
	) {
		static const int scrollbarPixelsPerTick = 200;
		CefMouseEvent mouseEvent;
		mouseEvent.modifiers = this->m_curMouseMod;
		mouseEvent.x = this->m_mouseX;
		mouseEvent.y = this->m_mouseY;
		int deltaX = 0;
		int deltaY = 0;
		deltaX = (x > 0) ? (scrollbarPixelsPerTick) : (-scrollbarPixelsPerTick);
		deltaY = (y > 0) ? (scrollbarPixelsPerTick) : (-scrollbarPixelsPerTick);
		m_browser->GetHost()->SendMouseWheelEvent(mouseEvent, deltaX, deltaY);
	}

	void WebCore::changeUrl(const std::string &url) {
		this->m_browser->GetMainFrame()->LoadURL(url);
	}

	void WebCore::paste() {
		this->m_browser->GetMainFrame()->Paste();
	}

	void WebCore::copy() {
		this->m_browser->GetMainFrame()->Copy();
	}

	void WebCore::cut() {
		this->m_browser->GetMainFrame()->Cut();
	}

	void WebCore::selectAll() {
		this->m_browser->GetMainFrame()->SelectAll();
	}

	void WebCore::reload(bool ignoreCache) {
		if (ignoreCache) {
			this->m_browser->ReloadIgnoreCache();
		} else {
			this->m_browser->Reload();
		}
	}

	CefRefPtr<const CefBrowser> WebCore::getBrowser() const {
		return m_browser;
	}

	CefRefPtr<const BrowserClient> WebCore::getClient() const {
		return m_client;
	}

	CefRefPtr<CefBrowser> WebCore::getBrowser() {
		return m_browser;
	}

	CefRefPtr<BrowserClient> WebCore::getClient() {
		return m_client;
	}

	std::shared_ptr<const network::client::NetworkHandler> WebCore::getNetworkHandler() const {
		return (this->m_networkHandler);
	}

	std::shared_ptr<const mvc::MvcHandler> WebCore::getMvcHandler() const {
		return (this->m_mvcHandler);
	}

	std::shared_ptr<network::client::NetworkHandler> WebCore::getNetworkHandler() {
		return (this->m_networkHandler);
	}

	std::shared_ptr<mvc::MvcHandler> WebCore::getMvcHandler() {
		return (this->m_mvcHandler);
	}
}