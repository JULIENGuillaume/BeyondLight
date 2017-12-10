//
// Created by diguie_t on 12/3/2017.
//

#include <json.hpp>
#include "OverviewController.hh"
#include "../../../../common/Toolbox.hh"
#include "../../MvcHandler.hh"
#include "LeftMenu.hh"

namespace bl {
	namespace mvc {

		OverviewController::OverviewController() {

		}

		std::string OverviewController::onQuery(
				CefRefPtr<CefBrowser> browser,
				CefRefPtr<CefFrame> frame,
				int64 query_id,
				const CefString &request,
				bool persistent,
				CefRefPtr<CefMessageRouterBrowserSide::Callback> callback
		) {
			std::vector<std::string> requestArgs = common::Toolbox::split(request, ":");

			if (!requestArgs.empty()) {
				const std::string &controllerRoute = LeftMenu::getRequestControllerRouter(requestArgs[0]);
				if (controllerRoute.empty()) {

				} else {
					callback->Success("OK");
					return (controllerRoute);
				}
			} else {
				callback->Failure(0, "Empty query");
			}
			return (std::string());
		}

		void OverviewController::setWebCore(WebCore *webCore) {
			this->m_webCore = webCore;
			this->m_webCore->getBrowser()->GetMainFrame()->LoadURL("file:///" + common::Toolbox::getApplicationDir() + "/../resources/html/index.html");
		}

		void OverviewController::onFrameEnd() {
		}
	}
}