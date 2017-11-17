#include <chrono>
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "WebCore.hh"
#include "RenderHandler.hh"
#include "include/cef_app.h"

WebCore::WebCore(const std::string &url)
	: _mouseX(0), _mouseY(0)
{
	_renderHandler = new RenderHandler();
	_renderHandler->Initialize();
	// initial size
	_renderHandler->resize(1280, 720);
    _curMouseMod = 0;

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
    browserSettings.web_security = STATE_ENABLED;
	browserSettings.windowless_frame_rate = 25; // 30 is default
	_client = new BrowserClient(_renderHandler);
	_browser = CefBrowserHost::CreateBrowserSync(window_info, _client.get(), url, browserSettings, nullptr);
}

WebCore::~WebCore()
{
	_browser->GetHost()->CloseBrowser(true);
	CefDoMessageLoopWork();

	_browser = nullptr;
	_client = nullptr;
}

void WebCore::reshape(int w, int h)
{
	_renderHandler->resize(w, h);
	_browser->GetHost()->WasResized();
}


void WebCore::mouseMove(double x, double y, int entered)
{
	this->_mouseX = x;
	this->_mouseY = y;

    CefMouseEvent mouseEvent;
    mouseEvent.x = x;
    mouseEvent.y = y;
    mouseEvent.modifiers = this->_curMouseMod;

    bool mouseLeave = entered == 0;

	_browser->GetHost()->SendMouseMoveEvent(mouseEvent, mouseLeave);
}

void WebCore::mouseClick(CefBrowserHost::MouseButtonType btn, bool mouse_up, int mods)
{
    static auto before = std::chrono::system_clock::now(); // todo improve
    static int count = 0;

    this->_curMouseMod = 0;
    if (btn == CefBrowserHost::MouseButtonType::MBT_LEFT) {
        this->_curMouseMod = EVENTFLAG_LEFT_MOUSE_BUTTON;
    } else if (btn == CefBrowserHost::MouseButtonType::MBT_RIGHT) {
        this->_curMouseMod = EVENTFLAG_RIGHT_MOUSE_BUTTON;
    } else if (btn == CefBrowserHost::MouseButtonType::MBT_MIDDLE) {
        this->_curMouseMod = EVENTFLAG_MIDDLE_MOUSE_BUTTON;
    } else {
        this->_curMouseMod = 0;
    }
	CefMouseEvent evt;
	evt.x = _mouseX;
    evt.y = _mouseY;
    evt.modifiers = this->_curMouseMod;

    if(!mouse_up) {
        auto now = std::chrono::system_clock::now();
        double diff_ms = std::chrono::duration <double, std::milli> (now - before).count();
        before = now;
            if(diff_ms > 10 && diff_ms < 200) {
            ++count;
        } else {
            count = 1;
        }
    }

	_browser->GetHost()->SendMouseClickEvent(evt, btn, mouse_up, count);
}

void WebCore::charPress(unsigned int key) {
    CefKeyEvent evt;

    evt.type = KEYEVENT_CHAR;
    evt.windows_key_code = key;
    evt.character = key;
    evt.modifiers = 0;
    evt.native_key_code = key;
    evt.unmodified_character = key;

    this->_browser->GetHost()->SendKeyEvent(evt);
}

void WebCore::keyPress(int key, int scancode, int action, int mods)
{
    CefKeyEvent event;

    CefRefPtr<CefFrame> frame = this->_browser->GetMainFrame(); // todo remove test
    frame->ExecuteJavaScript("i = 0;", frame->GetURL(), 0);
    unsigned int nativeKey = 0;
    if (key == GLFW_KEY_BACKSPACE) { // todo convert all keys
        nativeKey = VK_BACK;
    } else if (key == GLFW_KEY_PAGE_UP) {
        nativeKey = VK_PRIOR;
    } else if (key == GLFW_KEY_PAGE_DOWN) {
        nativeKey = VK_NEXT;
    }

    event.windows_key_code = nativeKey;
    event.modifiers = 0;
    event.native_key_code = nativeKey;
    event.unmodified_character = nativeKey;

    if (action == GLFW_PRESS)
        event.type = KEYEVENT_RAWKEYDOWN;
    else
        event.type = KEYEVENT_KEYUP;

    _browser->GetHost()->SendKeyEvent(event);
}

RenderHandler *WebCore::getRenderHandler() const {
    return (this->_renderHandler);
}

void WebCore::mouseScroll(int x, int y) {
    static const int scrollbarPixelsPerTick = 50;
    CefMouseEvent mouseEvent;

    mouseEvent.modifiers = this->_curMouseMod;
    mouseEvent.x = x;
    mouseEvent.y = y;

    int deltaX = 0;
    int deltaY = 0;
    deltaX = (x > 0) ? (scrollbarPixelsPerTick) : (-scrollbarPixelsPerTick);
    deltaY = (y > 0) ? (scrollbarPixelsPerTick) : (-scrollbarPixelsPerTick);

    _browser->GetHost()->SendMouseWheelEvent(mouseEvent, deltaX, deltaY);
}
