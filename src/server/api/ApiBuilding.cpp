//
// Created by Guillaume on 29/12/2017.
//

#include "../ServerCore.hh"
#include "ApiBuilding.hh"
#include "Api.hh"

bl::server::api::ApiBuilding::ApiBuilding(bl::server::api::Api &basicApi) : basicApi(basicApi) {}

bl::network::server::ServerMessage  bl::server::api::ApiBuilding::execute(bl::network::client::ClientMessage &message) {
	static std::unordered_map<uint64_t, std::function<network::server::ServerMessage(bl::network::client::ClientMessage)>> lMap = {
			{4242, [this](bl::network::client::ClientMessage message) -> network::server::ServerMessage { return getBuildingInfo(message);}},
			{421356, [this](bl::network::client::ClientMessage message) -> network::server::ServerMessage { return upgradeBuilding(message);}}
	};
	return (lMap.at(message.getBody().code))(message);

}

bl::network::server::ServerMessage bl::server::api::ApiBuilding::getBuildingInfo(bl::network::client::ClientMessage &message) {
	bl::network::server::ServerMessage answer{};
	answer.getBody().type = bl::network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO;
	answer.getBody().code = message.getBody().code;
	auto planet = this->basicApi.getCore().getData().loadedPlanets[this->basicApi.getCore().getData().activeSessions[message.getBody().sessionId]->getUser().getLastPlanetId()];
	try {
		auto building = planet->getBuildingInfo(std::stol(message.getBody().message.substr(1)));
		building->unlock(*planet);
		auto sendingJson = building->serialize();
		answer.getBody().message = sendingJson.dump();
		answer.getBody().type = bl::network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK;
	} catch (std::exception &e) {
		answer.getBody().message = e.what();
	}
	return answer;
}

bl::network::server::ServerMessage bl::server::api::ApiBuilding::upgradeBuilding(bl::network::client::ClientMessage &message) {
	bl::network::server::ServerMessage answer{};
	answer.getBody().type = bl::network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO;
	answer.getBody().code = message.getBody().code;
	auto planet = this->basicApi.getCore().getData().loadedPlanets[this->basicApi.getCore().getData().activeSessions[message.getBody().sessionId]->getUser().getLastPlanetId()];
	try {
		int buildingId = std::stol(message.getBody().message.substr(1));
		if (!planet->tryToUpdateBuilding(buildingId)) {
			answer.getBody().message = "Can't upgrade building";
		} else {
			answer.getBody().message = message.getBody().message.substr(1) + ":" + std::to_string(planet->getBuildingInfo(buildingId)->getLevel());
			answer.getBody().type = bl::network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK;
		}
		this->basicApi.getCore().getDatabase().update("planets", "uuid", planet->getUuidAsString(), planet->serialize());
		answer.getBody().type = bl::network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK;
	} catch (std::exception &e) {
		answer.getBody().message = e.what();
	}
	return answer;
}
