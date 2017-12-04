//
// Created by diguie_t on 11/11/2017.
//

#include <iostream>
#include <memory>
#include "include/cef_app.h"
#include "WebCoreManager.hh"
#include "../common/Toolbox.hh"


WebCoreManager::WebCoreManager(std::shared_ptr<network::client::NetworkHandler> networkHandler) :
    _networkHandler(networkHandler) {

}

WebCoreManager::~WebCoreManager() {

}

bool WebCoreManager::setUp(int *exit_code)
{
    assert(exit_code != nullptr);

    CefMainArgs args;
     *exit_code = CefExecuteProcess(args, this, nullptr);
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
    std::string rootDir = common::Toolbox::getApplicationDir();
    rootDir = rootDir.substr(0, rootDir.rfind("\\"));
    CefString(&settings.resources_dir_path) = rootDir + "\\resources\\cef";
    CefString(&settings.locales_dir_path) = rootDir + "\\resources\\cef\\locales";
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
    auto web_core = std::make_shared<WebCore>(url, this->_networkHandler);
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

// https://peter.sh/experiments/chromium-command-line-switches/#winhttp-proxy-resolver
void WebCoreManager::OnBeforeCommandLineProcessing(const CefString &process_type,
                                              CefRefPtr<CefCommandLine> command_line) {
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

void WebCoreManager::OnWebKitInitialized() {
    CefMessageRouterConfig config;
    message_router_ = CefMessageRouterRendererSide::Create(config);
}

void WebCoreManager::OnContextCreated(CefRefPtr<CefBrowser> browser,
                                      CefRefPtr<CefFrame> frame,
                                      CefRefPtr<CefV8Context> context) {

    message_router_->OnContextCreated(browser, frame, context);
}

void WebCoreManager::OnContextReleased(CefRefPtr<CefBrowser> browser,
                                       CefRefPtr<CefFrame> frame,
                                       CefRefPtr<CefV8Context> context) {
    message_router_->OnContextReleased(browser, frame, context);
}

void WebCoreManager::OnUncaughtException(CefRefPtr<CefBrowser> browser,
                                         CefRefPtr<CefFrame> frame,
                                         CefRefPtr<CefV8Context> context,
                                         CefRefPtr<CefV8Exception> exception,
                                         CefRefPtr<CefV8StackTrace> stackTrace) {
    std::cerr << "An uncaught exception happened!" << std::endl;
    CefRenderProcessHandler::OnUncaughtException(browser, frame, context,
                                                 exception, stackTrace);
}

bool WebCoreManager::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                              CefProcessId source_process,
                                              CefRefPtr<CefProcessMessage> message) {
    return message_router_->OnProcessMessageReceived(browser, source_process,
                                                     message);
}

CefRefPtr<CefRenderProcessHandler> WebCoreManager::GetRenderProcessHandler() {
    return (this);
}

void WebCoreManager::AddRef() const {

}

bool WebCoreManager::Release() const {
    return false;
}

bool WebCoreManager::HasOneRef() const {
    return false;
}

//void WebCoreManager::OnContextInitialized() {
//    /* // Create the browser window.
//    const CefString& startup_url = GetStartupURL();
//    shared::CreateBrowser(new Client(startup_url), startup_url,
//                          CefBrowserSettings()); todo setup ?*/
//    std::cout << "01" << std::endl;
//    CefBrowserProcessHandler::OnContextInitialized();
//}

/*CefRefPtr<CefBrowserProcessHandler> WebCoreManager::GetBrowserProcessHandler
        () {
    std::cout << "02" << std::endl;
    return (this);
}*/
