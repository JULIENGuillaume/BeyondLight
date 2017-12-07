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
            std::weak_ptr<WebCore> _webCore;
            bool _needToInsertBuilding;
            bool _needToInsertTechnologies;
            static const std::string _buildingsUrl;
            static const std::string _technologiesUrl;

        public:
            IndexController();

            void setModelHandler(
                    std::shared_ptr<ModelHandler> modelHandler) override;

            void setWebCore(std::weak_ptr<WebCore> webCore) override;

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