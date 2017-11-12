#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "WebCore.hh"
#include "RenderHandler.hh"
#include "include/cef_app.h"

WebCore::WebCore(const std::string &url)
	: _mouseX(0), _mouseY(0)
{
	_renderHandler = new RenderHandler();
	_renderHandler->init();
	// initial size
	_renderHandler->resize(256, 256);

	CefWindowInfo window_info;
	HWND hwnd = GetConsoleWindow();
	window_info.SetAsWindowless(hwnd);

    /*cmds->AppendArgument("disable-gpu");
    cmds->AppendArgument("enable-begin-frame-scheduling");
    cmds->AppendArgument("disable-d3d11");*/
    // https://peter.sh/experiments/chromium-command-line-switches/#winhttp-proxy-resolver
    CefBrowserSettings browserSettings;
    //browserSettings.accelerated_compositing = STATE_DISABLED;
    browserSettings.webgl = STATE_DISABLED;
    browserSettings.plugins = STATE_DISABLED;
    //browserSettings.java = STATE_DISABLED
    browserSettings.javascript_close_windows = STATE_DISABLED;
    browserSettings.javascript_access_clipboard = STATE_DISABLED;
    browserSettings.javascript_dom_paste = STATE_DISABLED;
    browserSettings.local_storage = STATE_DISABLED;
    browserSettings.databases = STATE_DISABLED;
    browserSettings.universal_access_from_file_urls = STATE_DISABLED;
    browserSettings.web_security = STATE_ENABLED;
	browserSettings.windowless_frame_rate = 30; // 30 is default
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


void WebCore::mouseMove(double x, int y)
{
	_mouseX = x;
	_mouseY = y;

	CefMouseEvent evt;
	evt.x = x;
	evt.y = y;

	//TODO
	bool mouse_leave = false;

	_browser->GetHost()->SendMouseMoveEvent(evt, mouse_leave);
}

void WebCore::mouseClick(CefBrowserHost::MouseButtonType btn, bool mouse_up)
{
	CefMouseEvent evt;
	evt.x = _mouseX;
	evt.y = _mouseY;

	//TODO
	int click_count = 1;

	_browser->GetHost()->SendMouseClickEvent(evt, btn, mouse_up, click_count);
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

    unsigned int nativeKey = 0;
    if (key == GLFW_KEY_BACKSPACE) {
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
    else /*(action == GLFW_RELEASE)*/
        event.type = KEYEVENT_KEYUP;

    _browser->GetHost()->SendKeyEvent(event);
}

RenderHandler *WebCore::getRenderHandler() const {
    return (this->_renderHandler);
}
