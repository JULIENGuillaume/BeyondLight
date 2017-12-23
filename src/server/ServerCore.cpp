//
// Created by Guillaume on 23/12/2017.
//

#include "ServerCore.hh"
#include "game/planet/Planet.hh"
#include "user/RegisteredUsers.hh"
#include "../common/Toolbox.hh"

bl::server::ServerCore::ServerCore() : m_serverNetworkHandler(8080) {}

void bl::server::ServerCore::start() {
	auto users = ::server::user::RegisteredUsers::getInstance();
	//::bl::server::game::building::IBuilding *build = new ::bl::server::game::building::IronMine(<#initializer#>); TODO: build a planet instead
	::bl::server::game::planet::Planet planet;
	//std::cout << "Main loop reached" << std::endl;
	bool loggedIn = false;
	while (m_isRunning) {
		while (m_serverNetworkHandler.getListClient().empty()) {
			std::cout << "Empty" << std::endl;
		}
		auto msg = m_serverNetworkHandler.getMessage().getBody();
		std::cout << "Received " << msg.code << ":" << msg.message << std::endl;
		auto toks = common::Toolbox::split(msg.message, ":");
		if (!toks.empty()) {
			switch (msg.code) {
				case 42:
					if (toks.size() == 2 && users->users.find(toks[0]) != users->users.end() && toks[1] == users->users[toks[0]]) {
						loggedIn = true;
						m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK, 42, "");
					} else {
						m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO, 42, "");
					}
					break;
				case 43:
					if (toks.size() == 6) {
						std::cout << "Registered user " << toks[2] << " with password " << toks[4] << std::endl;
						users->users.emplace(toks[2], toks[4]);
						m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK, 43, "");
					} else {
						m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO, 43, "");
					}
					break;
				case 4242:
					if (loggedIn) {
						nlohmann::json sendingJson;
						sendingJson["buildings"] = (planet.serialize())["buildings"];
						std::string toSend = sendingJson.dump();
						std::cout << "Sending " << toSend << std::endl;
						//socket->send("14242:" + toSend);
						m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK, 4242, toSend);
					} else {
						m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO, 4242, "");
					}
					break;
				case 3242:
					if (loggedIn) {
						planet.updateResources();
						nlohmann::json sendingJson;
						sendingJson["resources"] = (planet.serialize())["resources"];
						std::string toSend = sendingJson.dump();
						std::cout << "Sending " << toSend << std::endl;
						//socket->send("324201:" + toSend);
						m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK, 4242, toSend);
					} else {
						m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO, 3242, "");
					}
					break;
				case 421356:
					if (toks.size() == 1 && loggedIn) {
						int buildingId = std::atoi(toks[0].c_str());
						if (!planet.tryToUpdateBuilding(buildingId)) {
							m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO, 421356, "");
						} else {
							//socket->send("421357:" + toks[0] + ":" + std::to_string(planet.getBuildingInfo(buildingId)->getLevel()));
							m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK, 421356, toks[0] + ":" + std::to_string(planet.getBuildingInfo(buildingId)->getLevel()));
						}
					} else {
						m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO, 421356, "");
					}
					break;
				case 1337:
					this->m_isRunning = false;
					m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK, 1337, "");
					break;
				default:
					m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ERROR, 404, "Unknown command");
					break;
			}
		}
		std::cout << "End of server" << std::endl;
	}
}