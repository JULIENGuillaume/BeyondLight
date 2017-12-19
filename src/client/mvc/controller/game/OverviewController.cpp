//
// Created by diguie_t on 12/3/2017.
//

#include <json.hpp>
#include "OverviewController.hh"
#include "../../../../common/Toolbox.hh"
#include "../../MvcHandler.hh"
#include "LeftMenu.hh"
#include "../../model/ResourcesModel.hh"

namespace bl {
	namespace mvc {
		const std::string OverviewController::m_overviewUrl = "file:///" + ::common::Toolbox::getApplicationDir() + "/../resources/html/overview.html";;

		OverviewController::OverviewController() {

		}

		bool OverviewController::onQuery(
				CefRefPtr<CefBrowser> browser,
				CefRefPtr<CefFrame> frame,
				int64 query_id,
				const CefString &request,
				bool persistent,
				CefRefPtr<CefMessageRouterBrowserSide::Callback> callback,
				std::string &newRoute
		) {
			std::vector<std::string> requestArgs = ::common::Toolbox::split(request, ":");

			if (!requestArgs.empty()) {
				const std::string &controllerRoute = LeftMenu::getRequestControllerRouter(requestArgs[0]);
				if (!controllerRoute.empty()) {
					callback->Success("OK");
					newRoute = controllerRoute;
					return (true);
				}
			}
			return (false);
		}

		void OverviewController::setWebCore(WebCore *webCore) {
			this->m_webCore = webCore;
			this->m_webCore->getBrowser()->GetMainFrame()->LoadURL("file:///" + ::common::Toolbox::getApplicationDir() + "/../resources/html/overview.html");
		}

		void OverviewController::onFrameEnd() {
			auto modelHandler = this->m_webCore->getMvcHandler()->getModelHandler();
			{
				auto playerResources = modelHandler->getModel<ResourcesModel>("player-resources");
				playerResources->update();
				const auto resources = playerResources->getResources();
				std::string js = std::string("updateResources(")
						+ std::to_string(resources.getIron()) + ","
						+ std::to_string(resources.getCrystal()) + ","
						+ std::to_string(resources.getIridium()) + ","
						+ std::to_string(resources.getAntiMatter()) + ","
						+ std::to_string(resources.getEnergy()) + ");";
				this->m_webCore->getBrowser()->GetMainFrame()->ExecuteJavaScript(
						js, m_overviewUrl, 0);
			}
		}
	}
}