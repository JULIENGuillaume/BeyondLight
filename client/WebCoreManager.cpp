//
// Created by diguie_t on 11/11/2017.
//

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
    *exit_code = CefExecuteProcess(args, nullptr, nullptr);
    if (*exit_code >= 0) {
        return false;
    }

    CefSettings settings;
    bool result = CefInitialize(args, settings, nullptr, nullptr);
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