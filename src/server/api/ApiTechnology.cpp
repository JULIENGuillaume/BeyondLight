//
// Created by Guillaume on 29/12/2017.
//

#include "../ServerCore.hh"
#include "ApiTechnology.hh"
#include "Api.hh"

bl::server::api::ApiTechnology::ApiTechnology(bl::server::api::Api &basicApi) : basicApi(basicApi) {}

bl::network::server::ServerMessage  bl::server::api::ApiTechnology::execute(bl::network::client::ClientMessage &message) {
	static std::unordered_map<uint64_t, std::function<network::server::ServerMessage(bl::network::client::ClientMessage)>> lMap = {
			{154, [this](bl::network::client::ClientMessage message) -> network::server::ServerMessage { return getTechnologyInfo(message);}},
			{157, [this](bl::network::client::ClientMessage message) -> network::server::ServerMessage { return unlockTechnology(message);}},
	};
	return (lMap.at(message.getBody().code))(message);
}

bl::network::server::ServerMessage bl::server::api::ApiTechnology::getTechnologyInfo(bl::network::client::ClientMessage &message) {
	bl::network::server::ServerMessage answer{};
	answer.getBody().type = bl::network::server::SERVER_MESSAGE_TYPE_ANSWER_KO;
	answer.getBody().code = message.getBody().code;
	auto const& techs = basicApi.getCore().getModels().technologies;
	try {
		auto tech = techs.at(std::stoi(message.getBody().message.substr(1)));
		auto sendingJson = tech->serialize();
		sendingJson["unlockable"] = tech->isUnlockable(*basicApi.getCore().getData().loadedPlanets[basicApi.getCore().getData().activeSessions[message.getBody().sessionId]->getUser().getLastPlanetId()]);
		sendingJson["unlocked"] = tech->isUnlockedByPlayer(basicApi.getCore().getData().activeSessions[message.getBody().sessionId]->getUser());
		answer.getBody().message = sendingJson.dump();
		answer.getBody().type = bl::network::server::SERVER_MESSAGE_TYPE_ANSWER_OK;
	} catch (std::exception &e) {
		answer.getBody().message = e.what();
	}
	return answer;
}

bl::network::server::ServerMessage bl::server::api::ApiTechnology::unlockTechnology(bl::network::client::ClientMessage &message) {
	bl::network::server::ServerMessage answer{};
	answer.getBody().type = bl::network::server::SERVER_MESSAGE_TYPE_ANSWER_KO;
	answer.getBody().code = message.getBody().code;
	auto const& techs = basicApi.getCore().getModels().technologies;
	try {
		auto tech = techs.at(std::stoi(message.getBody().message.substr(1)));
		if (tech->unlock(*basicApi.getCore().getData().loadedPlanets[basicApi.getCore().getData().activeSessions[message.getBody().sessionId]->getUser().getLastPlanetId()])) {
			basicApi.getCore().getData().activeSessions[message.getBody().sessionId]->getUser().addTechnology(tech->getId());
			answer.getBody().type = bl::network::server::SERVER_MESSAGE_TYPE_ANSWER_OK;
			answer.getBody().message = std::to_string(tech->getId());
		}
	} catch (std::exception &e) {
		answer.getBody().message = e.what();
	}
	return answer;
}
