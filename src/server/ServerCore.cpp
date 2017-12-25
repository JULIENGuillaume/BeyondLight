//
// Created by Guillaume on 23/12/2017.
//

#include "ServerCore.hh"
#include "game/planet/Planet.hh"
#include "user/RegisteredUsers.hh"
#include "../common/Toolbox.hh"

bl::server::ServerCore::ServerCore() : m_serverNetworkHandler(8080) {}

void bl::server::ServerCore::start() {
	auto users = user::RegisteredUsers::getInstance();
	//::bl::server::game::building::IBuilding *build = new ::bl::server::game::building::IronMine(<#initializer#>); TODO: build a planet instead
	::bl::server::game::planet::Planet planet;
	//std::cout << "Main loop reached" << std::endl;
	bool loggedIn = true;
	while (m_isRunning) {
		/*while (m_serverNetworkHandler.getListClient().empty()) {
			std::cout << "Empty" << std::endl;
		}*/
		auto msgFrom = m_serverNetworkHandler.getMessage();
		auto msg = msgFrom.second.getBody();
		//std::cout << "Received " << msg.code << ":" << msg.message << std::endl;
		auto toks = common::Toolbox::split(msg.message, ":");
		switch (msg.code) {
			case 4242:
				if (loggedIn) {
					nlohmann::json sendingJson;
					sendingJson["buildings"] = (planet.serialize())["buildings"];
					std::string toSend = sendingJson.dump();
					//std::cout << "Sending " << toSend << std::endl;
					//socket->send("14242:" + toSend);
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
					//std::cout << "Sending " << toSend << std::endl;
					//socket->send("324201:" + toSend);
					m_serverNetworkHandler.send(network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK, 4242, toSend, msgFrom.first);
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
	//std::cout << "End of server" << std::endl;
}