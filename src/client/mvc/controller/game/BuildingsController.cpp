//
// Created by diguie_t on 12/9/2017.
//

#include "json.hpp"
#include "../../MvcHandler.hh"
#include "BuildingsController.hh"
#include "../../../../common/Toolbox.hh"
#include "LeftMenu.hh"
#include "../../model/BuildingModel.hh"
#include "../../model/ResourcesModel.hh"

namespace bl {
	namespace mvc {
		const std::string BuildingsController::m_buildingsUrl = "file:///" + bl::common::Toolbox::getApplicationDir() + "/../resources/html/buildings.html";

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
			std::vector<std::string> requestArgs = bl::common::Toolbox::split(request, ":");
			if (!requestArgs.empty()) {
				const std::string &controllerRoute = LeftMenu::getRequestControllerRouter(requestArgs[0]);
				if (controllerRoute.empty()) {
					auto modelHandler = this->m_webCore->getMvcHandler()->getModelHandler();
					if (requestArgs[0].find("index-building-upgrade") == 0 && requestArgs.size() == 2) {
						auto building = modelHandler->getModel<BuildingModel>(requestArgs[1] == "1" ? "building-iron-mine" : "building-crystal-extractor"); //fixme WTF ?
						if (building->incrLevel()) {
							this->m_webCore->reload(false); // fixme remove hack
							callback->Success(std::to_string(building->getLevel()));
						} else {
							callback->Failure(404, "MARCHE PAAAAAAAAS");
						}
						return (true);
					} else if (requestArgs[0].find("update-player-resources") == 0 && requestArgs.size() == 1) {
						auto playerResources = modelHandler->getModel<ResourcesModel>("player-resources");
						playerResources->update();
						const auto resources = playerResources->getResources();
						callback->Success(std::to_string(resources.getIron())
												  + ":" + std::to_string(resources.getCrystal())
												  + ":" + std::to_string(resources.getIridium())
												  + ":" + std::to_string(resources.getAntiMatter())
												  + ":" + std::to_string(resources.getEnergy()));
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
						js, m_buildingsUrl, 0);
			}

			//TODO: retrieve and use the list of buildings send by server, not by calling update on models one by one
			{
				auto ironMine = modelHandler->getModel<BuildingModel>("building-iron-mine");
				ironMine->update();
				const auto resourcesNeeded = ironMine->getResourcesNeeded();
				std::string js = std::string("createBuilding(")
						+ std::to_string(ironMine->getId()) + ",\""
						+ ironMine->getName() + "\",\""
						+ ironMine->getDesc() + "\","
						+ std::to_string(ironMine->getLevel()) + ","
						+ std::to_string(resourcesNeeded.getIron()) + ","
						+ std::to_string(resourcesNeeded.getCrystal()) + ","
						+ std::to_string(resourcesNeeded.getIridium()) + ","
						+ std::to_string(resourcesNeeded.getEnergy()) + ","
						+ "0" + ");";
				this->m_webCore->getBrowser()->GetMainFrame()->ExecuteJavaScript(
						js, m_buildingsUrl, 0);
			}
			{
				auto crystalExtractor = modelHandler->getModel<BuildingModel>("building-crystal-extractor");
				crystalExtractor->update();
				const auto resourcesNeeded = crystalExtractor->getResourcesNeeded();
				std::string js = std::string("createBuilding(")
						+ std::to_string(crystalExtractor->getId()) + ",\""
						+ crystalExtractor->getName() + "\",\""
						+ crystalExtractor->getDesc() + "\","
						+ std::to_string(crystalExtractor->getLevel()) + ","
						+ std::to_string(resourcesNeeded.getIron()) + ","
						+ std::to_string(resourcesNeeded.getCrystal()) + ","
						+ std::to_string(resourcesNeeded.getIridium()) + ","
						+ std::to_string(resourcesNeeded.getEnergy()) + ","
						+ "1" + ");";
				this->m_webCore->getBrowser()->GetMainFrame()->ExecuteJavaScript(
						js, m_buildingsUrl, 0);
			}
			{
				auto researchCenter = modelHandler->getModel<BuildingModel>("building-research-center");
				researchCenter->update();
				const auto resourcesNeeded = researchCenter->getResourcesNeeded();
				std::string js = std::string("createBuilding(")
						+ std::to_string(researchCenter->getId()) + ",\""
						+ researchCenter->getName() + "\",\""
						+ researchCenter->getDesc() + "\","
						+ std::to_string(researchCenter->getLevel()) + ","
						+ std::to_string(resourcesNeeded.getIron()) + ","
						+ std::to_string(resourcesNeeded.getCrystal()) + ","
						+ std::to_string(resourcesNeeded.getIridium()) + ","
						+ std::to_string(resourcesNeeded.getEnergy()) + ");";
				this->m_webCore->getBrowser()->GetMainFrame()->ExecuteJavaScript(
						js, m_buildingsUrl, 0);
			}
			{
				auto iridiumRefinery = modelHandler->getModel<BuildingModel>("building-iridium-refinery");
				iridiumRefinery->update();
				const auto resourcesNeeded = iridiumRefinery->getResourcesNeeded();
				std::string js = std::string("createBuilding(")
						+ std::to_string(iridiumRefinery->getId()) + ",\""
						+ iridiumRefinery->getName() + "\",\""
						+ iridiumRefinery->getDesc() + "\","
						+ std::to_string(iridiumRefinery->getLevel()) + ","
						+ std::to_string(resourcesNeeded.getIron()) + ","
						+ std::to_string(resourcesNeeded.getCrystal()) + ","
						+ std::to_string(resourcesNeeded.getIridium()) + ","
						+ std::to_string(resourcesNeeded.getEnergy()) + ");";
				this->m_webCore->getBrowser()->GetMainFrame()->ExecuteJavaScript(
						js, m_buildingsUrl, 0);
			}
		}
	}
}