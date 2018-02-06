//
// Created by Guillaume on 23/12/2017.
//

#include <functional>
#include "ServerCore.hh"
#include "../common/Toolbox.hh"
#include "api/Api.hh"

bl::server::LoadedData bl::server::ServerCore::m_data = {};

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
		/*while (m_isRunning) {
			std::shared_ptr<::bl::server::game::planet::Planet> planet;
			auto msgFrom = m_serverNetworkHandler.getMessage();
			auto msg = msgFrom.second.getBody();
			auto toks = common::Toolbox::split(msg.message, ":");
			nlohmann::json sendingJson;
			std::string toSend;
			if (m_data.activeSessions.find(msg.sessionId) != m_data.activeSessions.end()) {
				auto session = m_data.activeSessions[msg.sessionId];
				planet = m_data.loadedPlanets.find(session->getUser().getLastPlanetId())->second;
				std::cout << msg << std::endl;
				switch (msg.code) {
					case 4242:
						std::cout << "Request buildings" << std::endl;
						sendingJson = planet->getBuildingInfo(std::stol(msg.message.substr(1)))->serialize();
						toSend = sendingJson.dump();
						m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK, 4242, toSend, msgFrom.first);
						break;
					case 3242:
						planet->updateResources();
						std::cout << "Request resources" << std::endl;
						sendingJson["resources"] = (planet->serialize())["resources"];
						toSend = sendingJson.dump();
						m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK, 3242, toSend, msgFrom.first);
						m_database.update("planets", "uuid", planet->getUuidAsString(), planet->serialize());
						break;
					case 421356:
						if (toks.size() == 1) {
							std::cout << "Trying to update" << std::endl;
							int buildingId = std::stol(toks[0].substr(1));
							if (!planet->tryToUpdateBuilding(buildingId)) {
								m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO, 421356, "", msgFrom.first);
							} else {
								//socket->send("421357:" + toks[0] + ":" + std::to_string(planet.getBuildingInfo(buildingId)->getLevel()));
								m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK, 421356,
								                            toks[0].substr(1) + ":" + std::to_string(planet->getBuildingInfo(buildingId)->getLevel()), msgFrom.first);
							}
							m_database.update("planets", "uuid", planet->getUuidAsString(), planet->serialize());
						} else {
							m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO, 421356, "", msgFrom.first);
						}
						break;
					case 1337:
						std::cout << "Ending session" << std::endl;
						m_database.update("planets", "uuid", planet->getUuidAsString(), planet->serialize());
						m_data.loadedPlanets.erase(planet->getUuidAsString());
						m_data.activeUsers.erase(session->getUser().getUuidAsString());
						m_data.loggedUsers.erase(session->getUser().getLogin());
						m_data.activeSessions.erase(session->getUuidAsString());
						//this->m_isRunning = false;
						//m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK, 1337, "", msgFrom.first);
						break;
					default:
						m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ERROR, 404, "Unknown command", msgFrom.first);
						break;
				}
			} else {
				m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ERROR, 403, "You don't have any session opened, please log in first", msgFrom.first);
			}
		}*/
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
		this->m_serverNetworkHandler.send(network::server::SERVER_MESSAGE_TYPE_ANSWER_OK, 0, "",msg.first);
		return;
	}
	bl::network::server::ServerMessage message;
	message.getBody().code = msg.second.getBody().code;
	message.getBody().type = bl::network::server::SERVER_MESSAGE_TYPE_ANSWER_KO;
	message.getBody().message = "Unknown command";
	try {
		message = refApi.execute(msg.second);
	} catch (std::exception const& e) {
		std::cerr << "Command execution failed with " << e.what() << std::endl;
	}
	if (msg.second.getBody().msgType == network::client::CLIENT_MESSAGE_TYPE_REQUEST)
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
