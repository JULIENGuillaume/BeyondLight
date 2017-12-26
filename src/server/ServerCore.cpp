//
// Created by Guillaume on 23/12/2017.
//

#include "ServerCore.hh"
#include "game/planet/Planet.hh"
#include "../common/Toolbox.hh"

bl::server::ServerCore::ServerCore() : m_serverNetworkHandler(8080) {
	m_isRunning = true;
}

void bl::server::ServerCore::start() {
	try {
		::bl::server::game::planet::Planet planet;
		bool loggedIn = true;
		while (m_isRunning) {
			auto msgFrom = m_serverNetworkHandler.getMessage();
			auto msg = msgFrom.second.getBody();
			auto toks = common::Toolbox::split(msg.message, ":");
			switch (msg.code) {
				case 4242:
					if (loggedIn) {
						nlohmann::json sendingJson;
						sendingJson["buildings"] = (planet.serialize())["buildings"];
						std::string toSend = sendingJson.dump();
						m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK, 4242, toSend, msgFrom.first);
					} else {
						m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO, 4242, "", msgFrom.first);
					}
					break;
				case 3242:
					if (loggedIn) {
						planet.updateResources();
						nlohmann::json sendingJson;
						sendingJson["resources"] = (planet.serialize())["resources"];
						std::string toSend = sendingJson.dump();
						m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK, 3242, toSend, msgFrom.first);
					} else {
						m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO, 3242, "", msgFrom.first);
					}
					break;
				case 421356:
					if (toks.size() == 1 && loggedIn) {
						int buildingId = std::atoi(toks[0].c_str());
						if (!planet.tryToUpdateBuilding(buildingId)) {
							m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO, 421356, "", msgFrom.first);
						} else {
							//socket->send("421357:" + toks[0] + ":" + std::to_string(planet.getBuildingInfo(buildingId)->getLevel()));
							m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK, 421356,
							                            toks[0] + ":" + std::to_string(planet.getBuildingInfo(buildingId)->getLevel()), msgFrom.first);
						}
					} else {
						m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO, 421356, "", msgFrom.first);
					}
					break;
				case 1337:
					this->m_isRunning = false;
					loggedIn = false;
					m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK, 1337, "", msgFrom.first);
					break;
				default:
					m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ERROR, 404, "Unknown command", msgFrom.first);
					break;
			}
		}
	} catch (std::exception const &e) {
		std::cerr << "Server core end with error: " << e.what() << std::endl;
	}
}