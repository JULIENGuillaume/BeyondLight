#include <iostream>
#include <include/cef_v8.h>
#include <include/wrapper/cef_helpers.h>
#include "RenderHandler.hh"
#include "BrowserClient.hh"
#include "MessageHandler.hh"

BrowserClient::BrowserClient(WebCore *webCore) : _webCore(webCore) { // todo improve
    this->browser_ct_ = 0;
}

CefRefPtr<CefRenderHandler> BrowserClient::GetRenderHandler() {
    return (this->_webCore->getRenderHandler());
}

CefRefPtr<CefDisplayHandler> BrowserClient::GetDisplayHandler() {
    return (this);
}

CefRefPtr<CefLifeSpanHandler> BrowserClient::GetLifeSpanHandler() {
    return (this);
}

CefRefPtr<CefRequestHandler> BrowserClient::GetRequestHandler() {
    return (this);
}

void BrowserClient::OnTitleChange(CefRefPtr<CefBrowser> browser,
                                  const CefString &title) {
    CefDisplayHandler::OnTitleChange(browser, title);
}

void BrowserClient::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();

    if (!message_router_) {
        // Create the browser-side router for query handling.
        CefMessageRouterConfig config;
        message_router_ = CefMessageRouterBrowserSide::Create(config);

        // Register handlers with the router.
        message_handler_.reset(new MessageHandler("", this->_webCore)); // todo check startup_url
        message_router_->AddHandler(message_handler_.get(), false);
    }

    browser_ct_++;

    CefLifeSpanHandler::OnAfterCreated(browser);
}

bool BrowserClient::DoClose(CefRefPtr<CefBrowser> browser) {
    return CefLifeSpanHandler::DoClose(browser);
}

void BrowserClient::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();

    if (--browser_ct_ == 0) {
        // Free the router when the last browser is closed.
        message_router_->RemoveHandler(message_handler_.get());
        message_handler_.reset();
        message_router_ = NULL;
    }
    CefLifeSpanHandler::OnBeforeClose(browser);
}

bool BrowserClient::OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
                                   CefRefPtr<CefFrame> frame,
                                   CefRefPtr<CefRequest> request,
                                   bool is_redirect) {
    CEF_REQUIRE_UI_THREAD();

    message_router_->OnBeforeBrowse(browser, frame);
    return false;
}

void BrowserClient::OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser,
                                              CefRequestHandler::TerminationStatus status) {
    CEF_REQUIRE_UI_THREAD();

    message_router_->OnRenderProcessTerminated(browser);
}

bool BrowserClient::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                             CefProcessId source_process,
                                             CefRefPtr<CefProcessMessage> message) {
    CEF_REQUIRE_UI_THREAD();
    return (message_router_->OnProcessMessageReceived(browser,
                                                      source_process,
                                                      message));
}

CefRefPtr<CefResourceHandler> BrowserClient::GetResourceHandler(CefRefPtr<CefBrowser> browser,
                                  CefRefPtr<CefFrame> frame,
                                  CefRefPtr<CefRequest> request) {
    CEF_REQUIRE_IO_THREAD();

    //const std::string& url = request->GetURL();

    // This is a minimal implementation of resource loading. For more complex
    // usage (multiple files, zip archives, custom handlers, etc.) you might want
    // to use CefResourceManager. See the "resource_manager" target for an
    // example implementation.
    /*const std::string& resource_path = shared::GetResourcePath(url); todo
    if (!resource_path.empty())
        return shared::GetResourceHandler(resource_path); todo */

    return CefRequestHandler::GetResourceHandler(browser, frame, request);
}

void BrowserClient::OnLoadStart(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame,
                                CefLoadHandler::TransitionType transition_type) {
    CefLoadHandler::OnLoadStart(browser, frame, transition_type);
}

CefRefPtr<CefLoadHandler> BrowserClient::GetLoadHandler() {
    return (this);
}

void BrowserClient::OnLoadEnd(CefRefPtr<CefBrowser> browser,
                              CefRefPtr<CefFrame> frame, int httpStatusCode) {
    this->_webCore->getMvcHandler()->getControllerHandler()->onFrameEnd();
    CefLoadHandler::OnLoadEnd(browser, frame, httpStatusCode);
}
