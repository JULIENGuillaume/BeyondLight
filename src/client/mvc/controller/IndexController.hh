//
// Created by diguie_t on 12/3/2017.
//

#ifndef BEYONDLIGHT_INDEXCONTROLLER_HH
#define BEYONDLIGHT_INDEXCONTROLLER_HH

#include <string>
#include "IBaseController.hh"
#include "../../WebCore.hh"

namespace bl {
    namespace mvc {
        class IndexController : public IBaseController {
        private:
            WebCore *m_webCore;
            bool m_needToInsertBuilding;
            bool m_needToInsertTechnologies;
            static const std::string m_buildingsUrl;
            static const std::string m_technologiesUrl;

        public:
            IndexController();
            void setWebCore(WebCore *webCore) override;

            void
            buildings(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                      CefRefPtr<CefMessageRouterBrowserSide::Callback> callback);

            void
            overview(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                     CefRefPtr<CefMessageRouterBrowserSide::Callback> callback);

            std::string
            onQuery(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                    int64 query_id, const CefString &request, bool persistent,
                    CefRefPtr<CefMessageRouterBrowserSide::Callback> callback) override;

            void onFrameEnd() override;

            void technologies(CefRefPtr<CefBrowser> browser,
                              CefRefPtr<CefFrame> frame,
                              CefRefPtr<CefMessageRouterBrowserSide::Callback> callback);
        };
    }
}

#endif //BEYONDLIGHT_INDEXCONTROLLER_HH