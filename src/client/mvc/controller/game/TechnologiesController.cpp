//
// Created by diguie_t on 12/9/2017.
//

#include "TechnologiesController.hh"
#include "../../../../common/Toolbox.hh"
#include "../../MvcHandler.hh"
#include "LeftMenu.hh"
#include "../../model/ResourcesModel.hh"

namespace bl {
	namespace mvc {
		const std::string TechnologiesController::m_technologiesUrl = "file:///" + ::common::Toolbox::getApplicationDir() + "/../resources/html/technologies.html";

		void TechnologiesController::setWebCore(bl::WebCore *webCore) {
			this->m_webCore = webCore;
			this->m_webCore->getBrowser()->GetMainFrame()->LoadURL(m_technologiesUrl);
		}

		bool TechnologiesController::onQuery(
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
				if (controllerRoute.empty()) {
					if (requestArgs[0] == "index-technology-upgrade" && requestArgs.size() == 2) {
						static int level = 1;
						const std::string &result = requestArgs[1];
						auto network = this->m_webCore->getNetworkHandler();
						callback->Success(std::to_string(++level));
						return (true);
					}
				} else {
					callback->Success("OK");
					newRoute = controllerRoute;
					return (true);
				}
			}
			return (false);
		}

		void TechnologiesController::onFrameEnd() {
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
						js, m_technologiesUrl, 0);
			}
			std::string js = std::string("createTechnologie(")
					+ std::to_string(1) + ",\""
					+ "Quantum Technology" + "\","
					+ std::to_string(1) + ","
					+ std::to_string(400000) + ","
					+ std::to_string(30000) + ","
					+ std::to_string(10000) + ","
					+ std::to_string(5000) + ");";
			this->m_webCore->getBrowser()->GetMainFrame()->ExecuteJavaScript(js, m_technologiesUrl, 0);
		}
	}
}