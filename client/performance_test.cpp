// Test case for measuring CEF's offscreen rendering performance

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>

#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"

#pragma comment (lib, "winmm.lib")

std::string GetApplicationDir()
{
    HMODULE hModule = GetModuleHandleW(NULL);
    WCHAR   wpath[MAX_PATH];

    GetModuleFileNameW(hModule, wpath, MAX_PATH);
    std::wstring wide(wpath);

    std::string path = CefString(wide);
    path = path.substr( 0, path.find_last_of("\\/") );
    return path;
}

class SimpleHandler : public CefClient, public CefRenderHandler
{
public:

    int sizeX = 8100;
    int sizeY = 1080;

    DWORD lasttime = timeGetTime();

    // CefClient methods:
    virtual CefRefPtr<CefRenderHandler> GetRenderHandler() OVERRIDE { return this; }

    // Inherited via CefRenderHandler
    virtual bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect & rect) override
    {
        rect.Set(0, 0, sizeX, sizeY);
        return true;
    }

    virtual void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList & dirtyRects, const void * buffer, int width, int height) override
    {
        DWORD time = timeGetTime();
        int delta = time - lasttime;
        lasttime = time;

        printf("%3d", delta);
        for (auto r : dirtyRects)
            printf(" %dx%d", r.width, r.height);
        printf("\n");
    }


private:

    // Include the default reference counting implementation.
IMPLEMENT_REFCOUNTING(SimpleHandler);
};



class SimpleApp : public CefApp,
                  public CefBrowserProcessHandler {
public:

    // CefApp methods:
    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE { return this; }

    // CefBrowserProcessHandler methods:
    virtual void OnContextInitialized() OVERRIDE
    {
        CEF_REQUIRE_UI_THREAD();

        CefRefPtr<SimpleHandler> handler(new SimpleHandler());

        CefBrowserSettings browserSettings;
        browserSettings.webgl = STATE_DISABLED;
        browserSettings.plugins = STATE_DISABLED;
        browserSettings.javascript_close_windows = STATE_DISABLED;
        browserSettings.javascript_access_clipboard = STATE_DISABLED;
        browserSettings.javascript_dom_paste = STATE_DISABLED;
        browserSettings.local_storage = STATE_DISABLED;
        browserSettings.databases = STATE_DISABLED;
        browserSettings.universal_access_from_file_urls = STATE_DISABLED;
        browserSettings.web_security = STATE_DISABLED;
        browserSettings.windowless_frame_rate = 60; // 30 is default

        std::string url = "file:///" + GetApplicationDir() + "/../html/index.html";
        //std::string url = "https://www.shadertoy.com/view/Msf3R8";

        CefWindowInfo window_info;
        window_info.SetAsWindowless(GetForegroundWindow());

        CefBrowserHost::CreateBrowser(window_info, handler, url, browserSettings, NULL);
    }

    // https://peter.sh/experiments/chromium-command-line-switches/#winhttp-proxy-resolver
    void OnBeforeCommandLineProcessing(const CefString &process_type,
                                                       CefRefPtr<CefCommandLine> command_line) OVERRIDE {
        command_line.get()->AppendSwitch("disable-3d-apis");
        command_line.get()->AppendSwitch("disable-d3d11");
        command_line.get()->AppendSwitch("disable-databases");
        command_line.get()->AppendSwitch("disable-demo-mode");
        command_line.get()->AppendSwitch("disable-dinosaur-easter-egg");
        command_line.get()->AppendSwitch("disable-domain-reliability");
        command_line.get()->AppendSwitch("disable-es3-apis");
        command_line.get()->AppendSwitch("disable-extensions");
        command_line.get()->AppendSwitch("disable-flash-3d");
        command_line.get()->AppendSwitch("disable-flash-stage3d");
        command_line.get()->AppendSwitch("disable-gpu");
        command_line.get()->AppendSwitch("disable-gpu-compositing");
        command_line.get()->AppendSwitch("disable-gpu-sandbox");
        command_line.get()->AppendSwitch("disable-infobars"); // todo check
        command_line.get()->AppendSwitch("disable-notifications");
        command_line.get()->AppendSwitch("disable-pepper-3d");
        command_line.get()->AppendSwitch("disable-pepper-3d-image-chromium");
        command_line.get()->AppendSwitch("disable-sync");
        //command_line.get()->AppendSwitch("disable-threaded-compositing"); // blank page
        command_line.get()->AppendSwitch("disable-webgl");
        command_line.get()->AppendSwitch("disable-pdf-extension");
        command_line.get()->AppendSwitch("disable-surfaces");
        command_line.get()->AppendSwitch("enable-begin-frame-scheduling");
        command_line.get()->AppendSwitch("off-screen-rendering-enabled");
        //command_line.get()->AppendSwitch("disable-gpu-vsync");
        //command_line.get()->AppendSwitchWithValue("off-screen-frame-rate", "1"); overight by browser settings
        CefApp::OnBeforeCommandLineProcessing(process_type, command_line);
    }

private:
    // Include the default reference counting implementation.
IMPLEMENT_REFCOUNTING(SimpleApp);
};

int main()
{
    timeBeginPeriod(1); // make timeGetTime measure correctly

    CefMainArgs main_args(GetModuleHandle(0));
    int exit_code = CefExecuteProcess(main_args, NULL, NULL);
    if (exit_code >= 0) {
        return exit_code;
    }

    CefSettings settings;
    settings.multi_threaded_message_loop = true;
    settings.no_sandbox = true;
    //settings.pack_loading_disabled = true;
    settings.single_process = false;
    settings.command_line_args_disabled = false;
    settings.windowless_rendering_enabled = true;
    CefRefPtr<SimpleApp> app(new SimpleApp);
    CefInitialize(main_args, settings, app.get(), NULL);

    getchar(); // wait for something to happen

    // Shut down CEF.
    CefShutdown();
    return 0;
}