//
// Created by Guillaume on 25/12/2017.
//

#include <ClientMessage.hh>
#include <ServerMessage.hh>
#include "LoggingHelper.hh"
#include "../common/Toolbox.hh"
#include "user/RegisteredUsers.hh"

bl::server::LoggingHelper::LoggingHelper(const std::shared_ptr<bl::network::socket::TcpBoostSslSocket> &m_socket) : m_socket(m_socket) {

}

bool bl::server::LoggingHelper::executeCommand(std::string const &cmd) {
	bool hasLogged = false;
	auto users = user::RegisteredUsers::getInstance();
	network::client::ClientMessage message;
	{
		std::stringstream ss(cmd);
		cereal::PortableBinaryInputArchive inArchive(ss);
		inArchive(message);
	}
	network::server::ServerMessage answer;
	auto toks = common::Toolbox::split(message.getBody().message, ":");
	switch (message.getBody().code) {
		case 42:
			if (toks.size() == 2 && users->users.find(toks[0]) != users->users.end() && toks[1] == users->users[toks[0]]) {
				answer.getBody().type = network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK;
				answer.getBody().code = 42;
				answer.getBody().message = "";
				hasLogged = true;
			} else {
				answer.getBody().type = network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO;
				answer.getBody().code = 42;
				answer.getBody().message = "Unrecognized login / password";
			}
			break;
		case 43:
			if (toks.size() == 6) {
				answer.getBody().type = network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK;
				answer.getBody().code = 43;
				answer.getBody().message = "";
				users->users.emplace(toks[2], toks[4]);
			} else {
				answer.getBody().type = network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO;
				answer.getBody().code = 43;
				answer.getBody().message = "Invalid register request";
			}
			break;
		default:
			answer.getBody().type = network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ERROR;
			answer.getBody().code = 403;
			answer.getBody().message = "You're not logged in yet";
			break;
	}

	std::stringstream ss;
	cereal::PortableBinaryOutputArchive outArchive(ss);
	outArchive(answer);
	const std::string &strRepresentation = ss.str();
	std::vector<char> fullData(strRepresentation.begin(), strRepresentation.end());
	m_socket->send(std::string(fullData.begin(), fullData.end()));
	return hasLogged;
}
