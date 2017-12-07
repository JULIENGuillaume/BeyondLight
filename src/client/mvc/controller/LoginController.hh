//
// Created by diguie_t on 12/3/2017.
//

#ifndef BEYONDLIGHT_LOGINCONTROLLER_HH
#define BEYONDLIGHT_LOGINCONTROLLER_HH


#include "include/wrapper/cef_message_router.h"
#include "IBaseController.hh"
#include "../../WebCore.hh"

namespace bl {
    namespace mvc {
        class LoginController : public IBaseController {
        private:
            WebCore *m_webCore;
            std::shared_ptr<ModelHandler> m_modelHandler;

        public:
            bool handleLogin(CefRefPtr<CefBrowser> browser, std::string message,
                             CefRefPtr<CefMessageRouterBrowserSide::Callback> callback);

            void
            handleRegister(CefRefPtr<CefBrowser> browser, std::string message,
                           CefRefPtr<CefMessageRouterBrowserSide::Callback> callback);

            std::string
            onQuery(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                    int64 query_id, const CefString &request, bool persistent,
                    CefRefPtr<CefMessageRouterBrowserSide::Callback> callback);

            void onFrameEnd() override;

            void setWebCore(WebCore *webCore) override;

        };
    }
}

#endif //BEYONDLIGHT_LOGINCONTROLLER_HH
