#include <iostream>
#include "BrowserClient.hh"
#include "RenderHandler.hh"

BrowserClient::BrowserClient(RenderHandler *renderHandler)
	: _renderHandler(renderHandler) {
}

CefRefPtr<CefRenderHandler> BrowserClient::GetRenderHandler() {
    return (this->_renderHandler);

}