#include <iostream>
#include "BrowserClient.hh"
#include "RenderHandler.hh"

BrowserClient::BrowserClient(RenderHandler *renderHandler)
	: _renderHandler(renderHandler) {
}

CefRefPtr<CefRenderHandler> BrowserClient::GetRenderHandler() {
    return (this->_renderHandler);

}

bool BrowserClient::OnPreKeyEvent(CefRefPtr<CefBrowser> browser,
                                  const CefKeyEvent &event, MSG *os_event,
                                  bool *is_keyboard_shortcut) {
    std::cout << "bh!" << std::endl;
    return CefKeyboardHandler::OnPreKeyEvent(browser, event, os_event,
                                             is_keyboard_shortcut);
}

bool BrowserClient::OnKeyEvent(CefRefPtr<CefBrowser> browser,
                               const CefKeyEvent &event, MSG *os_event) {
    std::cout << "ah!" << std::endl;
    return CefKeyboardHandler::OnKeyEvent(browser, event, os_event);
}
