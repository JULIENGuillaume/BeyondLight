//
// Created by Guillaume on 29/12/2017.
//

#include "../ServerCore.hh"
#include "ApiPlanet.hh"
#include "Api.hh"

bl::server::api::ApiPlanet::ApiPlanet(bl::server::api::Api &basicApi) : basicApi(basicApi) {}

bl::network::server::ServerMessage  bl::server::api::ApiPlanet::execute(bl::network::client::ClientMessage &message) {
	static std::unordered_map<uint64_t, std::function<network::server::ServerMessage(bl::network::client::ClientMessage)>> lMap = {
			{3242, [this](bl::network::client::ClientMessage message) -> network::server::ServerMessage { return getResourcesInfo(message);}}
	};
	return (lMap.at(message.getBody().code))(message);
}

bl::network::server::ServerMessage bl::server::api::ApiPlanet::getResourcesInfo(bl::network::client::ClientMessage &message) {
	bl::network::server::ServerMessage answer{};
	answer.getBody().type = bl::network::server::SERVER_MESSAGE_TYPE_ANSWER_KO;
	answer.getBody().code = message.getBody().code;
	auto planet = this->basicApi.getCore().getData().loadedPlanets[this->basicApi.getCore().getData().activeSessions[message.getBody().sessionId]->getUser().getLastPlanetId()];
	try {
		nlohmann::json sendingJson;
		sendingJson["resources"] = (planet->serialize())["resources"];
		answer.getBody().message = sendingJson.dump();
		answer.getBody().type = bl::network::server::SERVER_MESSAGE_TYPE_ANSWER_OK;
	} catch (std::exception &e) {
		answer.getBody().message = e.what();
	}
	return answer;
}
