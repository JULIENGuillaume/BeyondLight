//
// Created by diguie_t on 11/11/2017.
//

#include <iostream>
#include "include/cef_app.h"
#include "WebCoreManager.hh"

WebCoreManager::WebCoreManager() {

}

WebCoreManager::~WebCoreManager() {

}

bool WebCoreManager::setUp(int *exit_code)
{
    assert(exit_code != nullptr);

    CefMainArgs args;
     *exit_code = CefExecuteProcess(args, nullptr /*this*/, nullptr);
    if (*exit_code >= 0) {
        return false;
    }

    CefSettings settings;
    settings.multi_threaded_message_loop = false;
    settings.no_sandbox = true;
    //settings.pack_loading_disabled = true;
    settings.single_process = false;
    settings.command_line_args_disabled = false;
    settings.windowless_rendering_enabled = true;
    bool result = CefInitialize(args, settings, this, nullptr);
    if (!result) {
        *exit_code = -1;
        return false;
    }
    return true;
}

bool WebCoreManager::shutDown()
{
    _browsers.clear();
    CefShutdown();
    return true;
}

void WebCoreManager::update()
{
    CefDoMessageLoopWork();
}

std::weak_ptr<WebCore> WebCoreManager::createBrowser(const std::string &url)
{
    auto web_core = std::make_shared<WebCore>(url);
    _browsers.push_back(web_core);
    return web_core;
}

void WebCoreManager::removeBrowser(std::weak_ptr<WebCore> web_core)
{
    auto elem = web_core.lock();
    if (elem) {
        auto found = std::find(_browsers.begin(), _browsers.end(), elem);
        if (found != _browsers.end()) {
            _browsers.erase(found);
        }
    }
}

void WebCoreManager::AddRef() const {

}

bool WebCoreManager::Release() const {
    return false;
}

bool WebCoreManager::HasOneRef() const {
    return false;
}

// https://peter.sh/experiments/chromium-command-line-switches/#winhttp-proxy-resolver
void WebCoreManager::OnBeforeCommandLineProcessing(const CefString &process_type,
                                              CefRefPtr<CefCommandLine> command_line) {
    std::cout << "-         cmd            -" << std::endl;
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

    std::vector<CefString> args;
    command_line.get()->GetArgv(args);
    for (const CefString &arg : args) {
        std::wcout << arg.c_str() << std::endl;
    }
    std::cout << std::endl;
    CefApp::OnBeforeCommandLineProcessing(process_type, command_line);
}
