//
// Created by Guillaume on 29/12/2017.
//

#include "../ServerCore.hh"
#include "ApiUser.hh"
#include "Api.hh"
#include "../../common/Toolbox.hh"

bl::server::api::ApiUser::ApiUser(bl::server::api::Api &basicApi) : basicApi(basicApi) {}

bl::network::server::ServerMessage  bl::server::api::ApiUser::execute(bl::network::client::ClientMessage &message) {
	static std::unordered_map<uint64_t, std::function<network::server::ServerMessage(bl::network::client::ClientMessage)>> lMap = {
			{234, [this](bl::network::client::ClientMessage message) -> network::server::ServerMessage { return addChatMessage(message);}},
			{235, [this](bl::network::client::ClientMessage message) -> network::server::ServerMessage { return getChatMessages(message);}},
	};
	return (lMap.at(message.getBody().code))(message);
}

bl::network::server::ServerMessage bl::server::api::ApiUser::addChatMessage(bl::network::client::ClientMessage &message) {
	bl::network::server::ServerMessage answer{};
	answer.getBody().type = bl::network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO;
	answer.getBody().code = message.getBody().code;
	auto &user = basicApi.getCore().getData().activeSessions[message.getBody().sessionId]->getUser();
	auto data = message.getBody().message.substr(1);
	if (!data.empty()) {
		basicApi.getCore().getData().chatInstance.addMsg(user.getLogin(), data);
		answer.getBody().type = bl::network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK;
	} else {
		answer.getBody().message = "Invalid request to send a message: expected a login and a message";
	}
	return answer;
}

bl::network::server::ServerMessage bl::server::api::ApiUser::getChatMessages(bl::network::client::ClientMessage &message) {
	bl::network::server::ServerMessage answer{};
	answer.getBody().type = bl::network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO;
	answer.getBody().code = message.getBody().code;
	auto &user = basicApi.getCore().getData().activeSessions[message.getBody().sessionId]->getUser();
	auto data = std::stoul(message.getBody().message.substr(1));
	std::cout << "Data is " << data << std::endl;
	auto msgs = basicApi.getCore().getData().chatInstance.getNLastMessages(static_cast<uint32_t>(data));
	std::cout << "Msgs" << std::endl;
	bool first = true;
	for (auto const& s : msgs) {
		if (!first)
			answer.getBody().message += std::string("\\:");
		answer.getBody().message += s.first + "\\:" + s.second;
		first = false;
	}
	answer.getBody().type = bl::network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK;
	return answer;
}
