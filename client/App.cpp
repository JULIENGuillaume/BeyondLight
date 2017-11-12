//
// Created by diguie_t on 11/12/2017.
//

#include "App.hh"

void App::AddRef() const {

}

bool App::Release() const {
    return false;
}

bool App::HasOneRef() const {
    return false;
}

void App::OnBeforeCommandLineProcessing(const CefString &process_type,
                                        CefRefPtr<CefCommandLine> command_line) {
    CefApp::OnBeforeCommandLineProcessing(process_type, command_line);
}

void App::OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar) {
    CefApp::OnRegisterCustomSchemes(registrar);
}

CefRefPtr<CefResourceBundleHandler> App::GetResourceBundleHandler() {
    return CefApp::GetResourceBundleHandler();
}

CefRefPtr<CefBrowserProcessHandler> App::GetBrowserProcessHandler() {
    return CefApp::GetBrowserProcessHandler();
}

CefRefPtr<CefRenderProcessHandler> App::GetRenderProcessHandler() {
    return CefApp::GetRenderProcessHandler();
}

App::~App() {

}
