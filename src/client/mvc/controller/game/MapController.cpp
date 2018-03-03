//
// Created by diguie_t on 3/3/2018.
//

#include "json.hpp"
#include "MapController.hh"
#include "../../../../common/Toolbox.hh"
#include "../../MvcHandler.hh"
#include "LeftMenu.hh"
#include "../../model/ResourcesModel.hh"
#include "../../model/PlanetModel.hh"

namespace bl {
	namespace mvc {
		const std::string MapController::m_mapUrl = "file:///" + bl::common::Toolbox::getApplicationDir() + "/../resources/html/map.html";;

		bool MapController::onQuery(
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
					if (requestArgs[0] == "index-map-attack" && requestArgs.size() == 2) {
						unsigned int planetPosition = 0;
						try {
							planetPosition = std::stoul(requestArgs[1], nullptr, 10);
						} catch (const std::invalid_argument &e) {
							callback->Failure(1, "Invalid position: " + requestArgs[1]);
							return (true);
						}
						auto network = this->m_webCore->getNetworkHandler();
						//auto ship = this->m_webCore->getMvcHandler()->getModelHandler()->getModel<ShipModel>("ship-nexus"); //fixme
						PlanetModel planetModel(this->m_webCore->getNetworkHandler(), planetPosition);
						planetModel.update();
						if (planetModel.isAttackable()) {
							this->m_webCore->reload(false); // fixme remove hack
							callback->Success("0");
						} else {
							callback->Failure(404, "MARCHE PAAAAAAAAS");
						}
						return (true);
					} else if (requestArgs[0].find("update-player-resources") == 0 && requestArgs.size() == 1) {
						auto modelHandler = this->m_webCore->getMvcHandler()->getModelHandler();
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

		void MapController::setWebCore(WebCore *webCore) {
			this->m_webCore = webCore;
			this->m_webCore->getBrowser()->GetMainFrame()->LoadURL(m_mapUrl);
		}

		void MapController::onFrameEnd() {
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
						js, m_mapUrl, 0);
			}
			int position = 42; // todo
			std::string username = "Allan add username";
			int iron = 1;
			int crystal = 2;
			int iridium = 3;
			int energy = 4;
			std::string attackable = "true";
			this->m_webCore->getBrowser()->GetMainFrame()->ExecuteJavaScript(std::string("createPlanet(")
																					 + std::to_string(position) + ","
																					 + "\"" + username + "\","
																					 + std::to_string(iron) + ","
																					 + std::to_string(crystal) + ","
																					 + std::to_string(iridium) + ","
																					 + std::to_string(energy) + ","
																					 + attackable + ");", m_mapUrl, 0);
		}

		MapController::MapController() {
		}
	}
}