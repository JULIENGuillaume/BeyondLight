//
// Created by diguie_t on 11/26/2017.
//

#ifndef MVC_TEST_IBASECONTROLLER_HH
#define MVC_TEST_IBASECONTROLLER_HH

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include "../model/ModelHandler.hh"
#include "../../../network/client/NetworkHandler.hh"
#include "include/wrapper/cef_message_router.h"

class WebCore;

class IBaseController {
public:
    virtual ~IBaseController() {}
    IBaseController() {}
    IBaseController(const IBaseController &) {}
    IBaseController & operator = (const IBaseController &) {return (*this);}
    virtual void setWebCore(std::weak_ptr<WebCore> webCore) = 0;
    virtual void setModelHandler(std::shared_ptr<ModelHandler> modelHandler) = 0;
    virtual std::string onQuery(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, /* todo improve return type */
                                int64 query_id, const CefString &request, bool persistent,
                                CefRefPtr<CefMessageRouterBrowserSide::Callback> callback) = 0;
    virtual void onFrameEnd() = 0;
};

#endif //MVC_TEST_IBASECONTROLLER_HH
