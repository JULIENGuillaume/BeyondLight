//
// Created by diguie_t on 11/20/2017.
//

#ifndef CEFOFFSCREEN_MESSAGEHANDLER_HH
#define CEFOFFSCREEN_MESSAGEHANDLER_HH


#include <iostream>
#include "include/wrapper/cef_message_router.h"

// http://www.magpcss.org/ceforum/viewtopic.php?f=17&t=12317 todo check this for improvement
class MessageHandler : public CefMessageRouterBrowserSide::Handler {
private:
    const std::string _mainRoute = "MainRoute";
    const CefString _startupUrl;

    // Handle messages in the browser process.
    public:
        explicit MessageHandler(const CefString &startup_url);

        bool OnQuery(CefRefPtr<CefBrowser> browser,
                     CefRefPtr<CefFrame> frame,
                     int64 query_id,
                     const CefString &request,
                     bool persistent,
                     CefRefPtr<Callback> callback) override;

    private:
        DISALLOW_COPY_AND_ASSIGN(MessageHandler);
};


#endif //CEFOFFSCREEN_MESSAGEHANDLER_HH
