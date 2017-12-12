//
// Created by diguie_t on 12/9/2017.
//

#include "json.hpp"
#include "BuildingsController.hh"
#include "../../../../common/Toolbox.hh"
#include "LeftMenu.hh"

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
						const std::string &buildingId = requestArgs[1];
						auto network = this->m_webCore->getNetworkHandler();
						network->send("421356:" + buildingId);
						auto answers = common::Toolbox::split(network->getLine(), ":");
						if (answers[0] == "321") {
							callback->Failure(404, "MARCHE PAAAAAAAAS");
						} else if (answers[0] == "421357" && answers[1] == buildingId) {
							callback->Success(answers[2]);
						} else {
							callback->Failure(404, "MARCHE PAAAAAAAAS");
						}
						// todo get building level
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
			auto network = this->m_webCore->getNetworkHandler();
			network->send("4242");
			std::string jsonReceived = network->getLine();
			std::cout << jsonReceived << std::endl;
			auto toks = common::Toolbox::splitAtMax(jsonReceived, ":", 1);
			nlohmann::json building;
			try {
				if (toks.size() == 2 && std::atoi(toks[0].c_str()) == 14242) {
					building = nlohmann::json::parse(toks[1]);
				} else {
					std::cerr << "Invalid reply" << std::endl;
					return;
				}
				auto id = building.at("id").get<unsigned int>();
				auto level = building.at("id").get<unsigned int>();
				std::string name = building.at("name").get<std::string>();
				auto iron = building.at(
						"resourcesRequired").get<nlohmann::json>().at(
						"iron").get<unsigned int>();
				auto crystal = building.at(
						"resourcesRequired").get<nlohmann::json>().at(
						"crystal").get<unsigned int>();
				auto iridium = building.at(
						"resourcesRequired").get<nlohmann::json>().at(
						"iridium").get<unsigned int>();
				auto energy = building.at(
						"resourcesRequired").get<nlohmann::json>().at(
						"energy").get<unsigned int>();

				//std::cout << "After asking for buildings, got: " << network->getLine() << std::endl;
				std::string js = std::string("createBuilding(")
						+ std::to_string(id) + ",\""
						+ name + "\","
						+ std::to_string(level) + ","
						+ std::to_string(iron) + ","
						+ std::to_string(crystal) + ","
						+ std::to_string(iridium) + ","
						+ std::to_string(energy) + ");";
				this->m_webCore->getBrowser()->GetMainFrame()->ExecuteJavaScript(
						js, m_buildingsUrl, 0);
				js = std::string("createBuilding(")
						+ std::to_string(id + 1) + ",\""
						+ name + "\","
						+ std::to_string(level) + ","
						+ std::to_string(iron) + ","
						+ std::to_string(crystal) + ","
						+ std::to_string(iridium) + ","
						+ std::to_string(energy) + ");";
				this->m_webCore->getBrowser()->GetMainFrame()->ExecuteJavaScript(
						js, m_buildingsUrl, 0);
			} catch (...) {
				std::cerr << "json parse error" << std::endl;
				return;
			}
		}
	}
}