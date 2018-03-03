//
// Created by diguie_t on 3/3/2018.
//

#include "ShipsController.hh"
#include "../../../../common/Toolbox.hh"
#include "../../MvcHandler.hh"
#include "LeftMenu.hh"
#include "../../model/ResourcesModel.hh"
#include "../../model/TechnologyModel.hh"
#include "../../model/ShipModel.hh"

namespace bl {
	namespace mvc {
		const std::string ShipsController::m_shipsUrl = "file:///" + bl::common::Toolbox::getApplicationDir() + "/../resources/html/ships.html";

		void ShipsController::setWebCore(bl::WebCore *webCore) {
			this->m_webCore = webCore;
			this->m_webCore->getBrowser()->GetMainFrame()->LoadURL(m_shipsUrl);
		}

		bool ShipsController::onQuery(
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
					if (requestArgs[0] == "index-ship-create" && requestArgs.size() == 3) {
						const std::string &result = requestArgs[1];
						unsigned int nbToBuild = 0;;
						try {
							nbToBuild = std::stoul(requestArgs[2], nullptr, 10);
						} catch (std::invalid_argument e) {
							callback->Failure(1, "Invalid value: " + requestArgs[2]);
							return (true);
						}
						auto network = this->m_webCore->getNetworkHandler();
						auto ship = this->m_webCore->getMvcHandler()->getModelHandler()->getModel<ShipModel>("ship-nexus"); //fixme
						if (ship->buildShip(nbToBuild)) {
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

		void ShipsController::onFrameEnd() {
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
						js, m_shipsUrl, 0);
			}
			{
				auto ship = modelHandler->getModel<ShipModel>("ship-nexus");
				ship->update();
				std::string js = std::string("createShip(")
						+ std::to_string(ship->getId()) + ",\""
						+ ship->getName() + "\",\""
						+ ship->getDesc() + "\","
						+ std::to_string(ship->getResourcesNeeded().getIron()) + ","
						+ std::to_string(ship->getResourcesNeeded().getCrystal()) + ","
						+ std::to_string(ship->getResourcesNeeded().getIridium()) + ","
						+ std::to_string(ship->getResourcesNeeded().getEnergy()) + ","
						+ std::to_string(static_cast<int>(ship->isUnlocked())) + ","
						+ std::to_string(ship->getQuantity()) + ");";
				//const auto resourcesNeeded = refiningIridiumTechnology->getResourcesNeeded();
				this->m_webCore->getBrowser()->GetMainFrame()->ExecuteJavaScript(js, m_shipsUrl, 0);
			}
		}
	}
}