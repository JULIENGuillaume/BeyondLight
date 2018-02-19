//
// Created by Guillaume on 23/12/2017.
//

#include <functional>
#include "ServerCore.hh"
#include "../common/Toolbox.hh"
#include "api/Api.hh"

bl::server::LoadedData bl::server::ServerCore::m_data = {};
bl::server::ModelData bl::server::ServerCore::m_models = {};

bl::server::ServerCore::ServerCore() : m_serverNetworkHandler(8080, this->m_data) {
	m_isRunning = true;
}

void bl::server::ServerCore::start() {
	try {
		api::Api serverApi(*this);
		while (this->m_isRunning) {
		  auto thread = std::thread(&ServerCore::executeCommand, this, this->m_serverNetworkHandler.getMessage(), std::ref(serverApi));
			thread.detach();
		}
	} catch (std::exception const &e) {
		std::cerr << "Server core end with error: " << e.what() << std::endl;
	}
}

void bl::server::ServerCore::executeCommand(std::pair<boost::asio::ip::udp::endpoint, bl::network::client::ClientMessage> msg,
											bl::server::api::Api &refApi) {
	std::cout << "Executing " << msg.second << std::endl;
	if (msg.second.getBody().code == 1337) {
		auto session = m_data.activeSessions[msg.second.getBody().sessionId];
		auto planet = this->getData().loadedPlanets[this->getData().activeSessions[msg.second.getBody().sessionId]->getUser().getLastPlanetId()];
		m_database.update("planets", "uuid", planet->getUuidAsString(), planet->serialize());
		m_data.loadedPlanets.erase(planet->getUuidAsString());
		m_data.activeUsers.erase(session->getUser().getUuidAsString());
		m_data.loggedUsers.erase(session->getUser().getLogin());
		m_data.activeSessions.erase(session->getUuidAsString());
		std::cout << "Logged out !" << std::endl;
		return;
	}
	if (msg.second.getBody().code == 0) {
		this->getData().activeSessions[msg.second.getBody().sessionId]->setIp(msg.first.address().to_string());
		this->getData().activeSessions[msg.second.getBody().sessionId]->setEndpoint(msg.first);
		this->m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK, 0, "",msg.first);
		return;
	}
	bl::network::server::ServerMessage message;
	message.getBody().code = msg.second.getBody().code;
	message.getBody().type = bl::network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO;
	message.getBody().message = "Unknown command";
	try {
		message = refApi.execute(msg.second);
	} catch (std::exception const& e) {
		std::cerr << "Command execution failed with " << e.what() << std::endl;
	}
	if (msg.second.getBody().msgType == network::client::ClientMessageType::CLIENT_MESSAGE_TYPE_REQUEST)
		this->m_serverNetworkHandler.send(message, msg.first);
}

const bl::network::server::ServerNetworkHandler &bl::server::ServerCore::getServerNetworkHandler() const {
	return m_serverNetworkHandler;
}

const bl::server::storage::Database &bl::server::ServerCore::getDatabase() const {
	return m_database;
}
/*
const bl::server::LoadedData &bl::server::ServerCore::getData() {
	return m_data;
}*/


bl::network::server::ServerNetworkHandler &bl::server::ServerCore::getServerNetworkHandler() {
	return m_serverNetworkHandler;
}

bl::server::storage::Database &bl::server::ServerCore::getDatabase() {
	return m_database;
}

bl::server::LoadedData &bl::server::ServerCore::getData()  {
	return m_data;
}

bl::server::ModelData &bl::server::ServerCore::getModels() {
	return m_models;
}
