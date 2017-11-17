//
// Created by diguie_t on 11/11/2017.
//

#ifndef CEFOFFSCREEN_WEBCOREMANAGER_HH
#define CEFOFFSCREEN_WEBCOREMANAGER_HH

#include "include/cef_app.h"
#include "WebCore.hh"

class WebCoreManager : public CefApp {
private:
    std::vector<std::shared_ptr<WebCore>> _browsers;

public:
	WebCoreManager();
	~WebCoreManager();

	bool setUp(int *exit_code);
	bool shutDown();

	void update();

	std::weak_ptr<WebCore> createBrowser(const std::string &url);
	void removeBrowser(std::weak_ptr<WebCore> web_core);

    void AddRef() const override;

    bool Release() const override;

    bool HasOneRef() const override;

    void OnBeforeCommandLineProcessing(const CefString &process_type,
                                       CefRefPtr<CefCommandLine> command_line) override;
};


#endif //CEFOFFSCREEN_WEBCOREMANAGER_HH
