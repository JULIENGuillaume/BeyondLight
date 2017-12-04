//
// Created by diguie_t on 12/3/2017.
//

#ifndef BEYONDLIGHT_INDEXCONTROLLER_HH
#define BEYONDLIGHT_INDEXCONTROLLER_HH

#include <string>
#include "IBaseController.hh"

class IndexController : public IBaseController {
private:
    std::weak_ptr<WebCore> _webCore;

public:
    IndexController();

    void setModelHandler(std::shared_ptr<ModelHandler> modelHandler) override;
    void setWebCore(std::weak_ptr<WebCore> webCore) override;

    std::string onQuery(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                        int64 query_id, const CefString &request, bool persistent,
                        CefRefPtr<CefMessageRouterBrowserSide::Callback> callback) override;
};


#endif //BEYONDLIGHT_INDEXCONTROLLER_HH
