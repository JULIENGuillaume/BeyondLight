//
// Created by diguie_t on 12/3/2017.
//

#ifndef BEYONDLIGHT_LOGINCONTROLLER_HH
#define BEYONDLIGHT_LOGINCONTROLLER_HH


#include "include/wrapper/cef_message_router.h"
#include "IBaseController.hh"

class LoginController : public IBaseController {
private:
    std::shared_ptr<network::client::NetworkHandler> _networkHandler;

public:
    void setModelHandler(std::shared_ptr<ModelHandler> modelHandler) override;
    void setNetWorkHandler(std::shared_ptr<network::client::NetworkHandler> networkHandler) override;

    void handleLogin(CefRefPtr<CefBrowser> browser, std::string message, CefRefPtr<CefMessageRouterBrowserSide::Callback> callback);
    void handleRegister(CefRefPtr<CefBrowser> browser, std::string message, CefRefPtr<CefMessageRouterBrowserSide::Callback> callback);
    void onQuery(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                     int64 query_id, const CefString &request, bool persistent,
                     CefRefPtr<CefMessageRouterBrowserSide::Callback> callback);

};


#endif //BEYONDLIGHT_LOGINCONTROLLER_HH
