//
// Created by diguie_t on 12/9/2017.
//

#include "json.hpp"
#include "../../MvcHandler.hh"
#include "BuildingsController.hh"
#include "../../../../common/Toolbox.hh"
#include "LeftMenu.hh"
#include "../../model/BuildingModel.hh"

namespace bl {
	namespace mvc {
		const std::string BuildingsController::m_buildingsUrl = "file:///" + common::Toolbox::getApplicationDir() + "/../resources/html/buildings.html";

		void BuildingsController::setWebCore(bl::WebCore *webCore) {
			this->m_webCore = webCore;
			this->m_webCore->getBrowser()->GetMainFrame()->LoadURL(m_buildingsUrl);
		}

		bool BuildingsController::onQuery(
				CefRefPtr<CefBrowser> browser,
				CefRefPtr<CefFrame> frame,
				int64 query_id,
				const CefString &request,
				bool persistent,
				CefRefPtr<CefMessageRouterBrowserSide::Callback> callback,
				std::string &newRoute
		) {
			std::vector<std::string> requestArgs = common::Toolbox::split(request, ":");
			if (!requestArgs.empty()) {
				const std::string &controllerRoute = LeftMenu::getRequestControllerRouter(requestArgs[0]);
				if (controllerRoute.empty()) {
					if (requestArgs[0].find("index-building-upgrade") == 0 && requestArgs.size() == 2) {
						auto modelHandler = this->m_webCore->getMvcHandler()->getModelHandler();
						auto ironMine = modelHandler->getModel<BuildingModel>("building-iron-mine");

						//const std::string &buildingId = requestArgs[1];
						if (ironMine->incrLevel()) {
							callback->Success(std::to_string(ironMine->getLevel()));
						} else {
							callback->Failure(404, "MARCHE PAAAAAAAAS");
						}
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

		void BuildingsController::onFrameEnd() {
			auto modelHandler = this->m_webCore->getMvcHandler()->getModelHandler();
			//TODO: retrieve and use the list of buildings send by server, not by calling update on models one by one
			auto ironMine = modelHandler->getModel<BuildingModel>("building-iron-mine");
			ironMine->markForUpdate();
			std::string js = std::string("createBuilding(")
					+ std::to_string(ironMine->getId()) + ",\""
					+ ironMine->getName() + "\","
					+ std::to_string(ironMine->getLevel()) + ","
					+ std::to_string(ironMine->getIronNeeded()) + ","
					+ std::to_string(ironMine->getCrystalNeeded()) + ","
					+ std::to_string(ironMine->getIridiumNeeded()) + ","
					+ std::to_string(ironMine->getEnergyNeeded()) + ");";
			this->m_webCore->getBrowser()->GetMainFrame()->ExecuteJavaScript(
					js, m_buildingsUrl, 0);
			/*js = std::string("createBuilding(")
					+ std::to_string(ironMine->getId() + 1) + ",\""
					+ ironMine->getName() + "\","
					+ std::to_string(ironMine->getLevel()) + ","
					+ std::to_string(ironMine->getIronNeeded()) + ","
					+ std::to_string(ironMine->getCrystalNeeded()) + ","
					+ std::to_string(ironMine->getIridiumNeeded()) + ","
					+ std::to_string(ironMine->getEnergyNeeded()) + ");";
			this->m_webCore->getBrowser()->GetMainFrame()->ExecuteJavaScript(
					js, m_buildingsUrl, 0);*/
		}
	}
}