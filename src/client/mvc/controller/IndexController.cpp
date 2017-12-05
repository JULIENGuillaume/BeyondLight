//
// Created by diguie_t on 12/3/2017.
//

#include <json.hpp>
#include "IndexController.hh"
#include "../../../common/Toolbox.hh"
#include "../../WebCore.hh"

const std::string IndexController::_buildingsUrl = "file:///" + common::Toolbox::getApplicationDir() + "/../resources/html/buildings.html";

IndexController::IndexController() :
		_needToInsertBuilding(false) {

}


void IndexController::setModelHandler(std::shared_ptr<ModelHandler> modelHandler) {

}

std::string IndexController::onQuery(CefRefPtr<CefBrowser> browser,
                                     CefRefPtr<CefFrame> frame, int64 query_id,
                                     const CefString &request, bool persistent,
                                     CefRefPtr<CefMessageRouterBrowserSide::Callback> callback) {
	std::string message(request);
	if (message.find("index-buildings") == 0) {
		this->buildings(browser, frame, callback);
	} else if (message.find("index-overview") == 0) {
		this->overview(browser, frame, callback);
	} else if (message.find("index-building-upgrade") == 0) {
		auto result = message.substr(std::string("index-building-upgrade-").length());

		auto network = this->_webCore.lock()->getNetworkHandler();
		network->send("421356:" + result);
		auto answers = common::Toolbox::split(network->getLine(), ":");
		if (answers[0] == "321")
			callback->Failure(404, "MARCHE PAAAAAAAAS");
		else if (answers[0] == "421357" && answers[1] == result)
			callback->Success(answers[2]);
		else
			callback->Failure(404, "MARCHE PAAAAAAAAS");
// todo get building level
	} else {
		std::wcout << L"unknown query: " << request.c_str() << std::endl;
	}
	return (std::string());
}

void IndexController::setWebCore(std::weak_ptr<WebCore> webCore) {
	this->_webCore = webCore;
	overview(nullptr, nullptr, nullptr);
}

void IndexController::buildings(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame,
                                CefRefPtr<CefMessageRouterBrowserSide::Callback> callback) {

	if (callback != nullptr) {
		callback->Success(std::string());
	}

	this->_needToInsertBuilding = true;
	this->_webCore.lock()->getBrowser()->GetMainFrame()->LoadURL(_buildingsUrl);
}

void IndexController::overview(CefRefPtr<CefBrowser> browser,
                               CefRefPtr<CefFrame> frame,
                               CefRefPtr<CefMessageRouterBrowserSide::Callback> callback) {
	if (callback != nullptr) {
		callback->Success(std::string());
	}
	this->_webCore.lock()->getBrowser()->GetMainFrame()->LoadURL("file:///" + common::Toolbox::getApplicationDir() + "/../resources/html/index.html");
}

void IndexController::onFrameEnd() {
	if (this->_needToInsertBuilding) {
		this->_needToInsertBuilding = false;
		auto network = this->_webCore.lock()->getNetworkHandler();
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
		auto iron = building.at("resourcesRequired").get<nlohmann::json>().at("iron").get<unsigned int>();
		auto crystal = building.at("resourcesRequired").get<nlohmann::json>().at("crystal").get<unsigned int>();
		auto iridium = building.at("resourcesRequired").get<nlohmann::json>().at("iridium").get<unsigned int>();
		auto energy = building.at("resourcesRequired").get<nlohmann::json>().at("energy").get<unsigned int>();

		//std::cout << "After asking for buildings, got: " << network->getLine() << std::endl;
		std::string js = std::string("createBuilding(")
		                 + std::to_string(id) + ",\""
		                 + name + "\","
		                 + std::to_string(level) + ","
		                 + std::to_string(iron) + ","
		                 + std::to_string(crystal) + ","
		                 + std::to_string(iridium) + ","
		                 + std::to_string(energy) + ");";
		this->_webCore.lock()->getBrowser()->GetMainFrame()->ExecuteJavaScript(js, _buildingsUrl, 0);
		js = std::string("createBuilding(")
		     + std::to_string(id + 1) + ",\""
		     + name + "\","
		     + std::to_string(level) + ","
		     + std::to_string(iron) + ","
		     + std::to_string(crystal) + ","
		     + std::to_string(iridium) + ","
		     + std::to_string(energy) + ");";
		this->_webCore.lock()->getBrowser()->GetMainFrame()->ExecuteJavaScript(js, _buildingsUrl, 0);
	}
}
