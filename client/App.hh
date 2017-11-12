//
// Created by diguie_t on 11/12/2017.
//

#ifndef CEFOFFSCREEN_APP_HH
#define CEFOFFSCREEN_APP_HH

#include "include/cef_app.h"

class App : public CefApp {
private:

public:
    void OnBeforeCommandLineProcessing(const CefString &process_type,
                                       CefRefPtr<CefCommandLine> command_line) override;

    void
    OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar) override;

    CefRefPtr<CefResourceBundleHandler> GetResourceBundleHandler() override;

    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;

    CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override;

protected:
    ~App() override;

public:
    void AddRef() const override;

    bool Release() const override;

    bool HasOneRef() const override;

};


#endif //CEFOFFSCREEN_APP_HH
