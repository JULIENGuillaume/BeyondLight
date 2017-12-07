//
// Created by diguie_t on 12/3/2017.
//

#include <json.hpp>
#include "IndexController.hh"
#include "../../../common/Toolbox.hh"
#include "../MvcHandler.hh"

namespace bl {
	namespace mvc {
		const std::string IndexController::m_buildingsUrl = "file:///" + common::Toolbox::getApplicationDir() + "/../resources/html/buildings.html";
		const std::string IndexController::m_technologiesUrl = "file:///" + common::Toolbox::getApplicationDir() + "/../resources/html/technologies.html";

		IndexController::IndexController() :
				m_needToInsertBuilding(false),
				m_needToInsertTechnologies(false) {
		}

		std::string IndexController::onQuery(
				CefRefPtr<CefBrowser> browser,
				CefRefPtr<CefFrame> frame,
				int64 query_id,
				const CefString &request,
				bool persistent,
				CefRefPtr<CefMessageRouterBrowserSide::Callback> callback
		) {
			std::string message(request);
			if (message.find("index-buildings") == 0) {
				this->buildings(browser, frame, callback);
			} else if (message.find("index-technologies") == 0) {
				this->technologies(browser, frame, callback);
			} else if (message.find("index-overview") == 0) {
				this->overview(browser, frame, callback);
			} else if (message.find("index-technology-upgrade") == 0) {
				static int level = 1;
				auto result = message.substr(
						std::string("index-technology-upgrade-").length());
				auto network = this->m_webCore->getNetworkHandler();
				callback->Success(std::to_string(++level));
			} else if (message.find("index-building-upgrade") == 0) {
				auto result = message.substr(
						std::string("index-building-upgrade-").length());
				auto network = this->m_webCore->getNetworkHandler();
				network->send("421356:" + result);
				auto answers = common::Toolbox::split(network->getLine(), ":");
				if (answers[0] == "321") {
					callback->Failure(404, "MARCHE PAAAAAAAAS");
				} else if (answers[0] == "421357" && answers[1] == result) {
					callback->Success(answers[2]);
				} else {
					callback->Failure(404, "MARCHE PAAAAAAAAS");
				}
				// todo get building level
			} else {
				std::wcout << L"unknown query: " << request.c_str()
						<< std::endl;
			}
			return (std::string());
		}

		void IndexController::setWebCore(WebCore *webCore) {
			this->m_webCore = webCore;
			overview(nullptr, nullptr, nullptr);
		}

		void IndexController::buildings(
				CefRefPtr<CefBrowser> browser,
				CefRefPtr<CefFrame> frame,
				CefRefPtr<CefMessageRouterBrowserSide::Callback> callback
		) {
			if (callback != nullptr) {
				callback->Success(std::string());
			}
			this->m_needToInsertBuilding = true;
			this->m_webCore->getBrowser()->GetMainFrame()->LoadURL(
					m_buildingsUrl);
		}

		void IndexController::technologies(
				CefRefPtr<CefBrowser> browser,
				CefRefPtr<CefFrame> frame,
				CefRefPtr<CefMessageRouterBrowserSide::Callback> callback
		) {
			if (callback != nullptr) {
				callback->Success(std::string());
			}
			this->m_needToInsertTechnologies = true;
			this->m_webCore->getBrowser()->GetMainFrame()->LoadURL(m_technologiesUrl);
		}

		void IndexController::overview(
				CefRefPtr<CefBrowser> browser,
				CefRefPtr<CefFrame> frame,
				CefRefPtr<CefMessageRouterBrowserSide::Callback> callback
		) {
			if (callback != nullptr) {
				callback->Success(std::string());
			}
			this->m_webCore->getBrowser()->GetMainFrame()->LoadURL("file:///" + common::Toolbox::getApplicationDir() + "/../resources/html/index.html");
		}

		void IndexController::onFrameEnd() {
			if (this->m_needToInsertTechnologies) {
				this->m_needToInsertTechnologies = false;
				std::string js = std::string("createTechnologie(")
						+ std::to_string(1) + ",\""
						+ "Quantum Technology" + "\","
						+ std::to_string(1) + ","
						+ std::to_string(400000) + ","
						+ std::to_string(30000) + ","
						+ std::to_string(10000) + ","
						+ std::to_string(5000) + ");";
				this->m_webCore->getBrowser()->GetMainFrame()->ExecuteJavaScript(
						js, m_technologiesUrl, 0);
			}
			if (this->m_needToInsertBuilding) {
				this->m_needToInsertBuilding = false;
				auto network = this->m_webCore->getNetworkHandler();
				network->send("4242");
				std::string jsonReceived = network->getLine();
				std::cout << jsonReceived << std::endl;
				auto toks = common::Toolbox::splitAtMax(jsonReceived, ":", 1);
				nlohmann::json building;
				if (toks.size() == 2 && std::atoi(toks[0].c_str()) == 14242) {
					try {
						building = nlohmann::json::parse(toks[1]);
					} catch (...) {
						std::cerr << "json parse error" << std::endl;
						return;
					}
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
			}
		}
	}
}