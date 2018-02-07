//
// Created by diguie_t on 12/14/2017.
//

#include "json.hpp"
#include "BuildingModel.hh"
#include "../../../common/Toolbox.hh"
#include "../../../common/game/Resources.hh"

namespace bl {
	namespace mvc {

		BuildingModel::BuildingModel(
				std::shared_ptr<network::client::ClientNetworkHandler> networkHandler,
				unsigned int id
		) :
				ABaseModel::ABaseModel(networkHandler),
				m_id(id) {
			//this->update();
		}

		unsigned int BuildingModel::getId() const {
			return m_id;
		}

		const std::string &BuildingModel::getName() const {
			return m_name;
		}

		unsigned int BuildingModel::getLevel() const {
			return m_level;
		}

		void BuildingModel::update() {
			if (this->m_networkHandler.get()) {
				try {
					m_networkHandler->send(m_networkHandler->getApiHelper()->buildNewApiRequest(m_networkHandler->getApiHelper()->REQUEST_BUILDING_INFO, std::to_string(m_id)));
					//this->m_networkHandler->send(network::client::ClientMessageType::CLIENT_MESSAGE_TYPE_REQUEST, 4242, "");
					auto msg = this->m_networkHandler->getMessage();
					/*std::string jsonReceived = msg.getBody().message;
					nlohmann::json buildings;
					if (msg.getBody().type == network::server::SERVER_MESSAGE_TYPE_ANSWER_OK) {
						buildings = ((nlohmann::json::parse(jsonReceived))["buildings"]);
					} else {
						return;
					}*/
					nlohmann::json building = nlohmann::json::parse(msg.getBody().message);
					std::cerr << "Building: " << msg.getBody().message << std::endl;
					/*for (const auto& build : buildings) {
						building = build;
						if (building.at("id") == m_id)
							break;
					}*/

					m_level = building["level"];
					m_name = building["name"];
					m_desc = building["description"];
					m_unlocked = building["unlocked"];
					this->m_resourcesNeeded.deserialize(building["resourcesRequired"]["resources"]);
				} catch (std::exception &e) {
					std::cerr << "json parse error building " << e.what() << std::endl;
					return;
				}
			}
		}

		bool BuildingModel::incrLevel() {
			std::cout << "Incr level" << std::endl;
			//this->m_networkHandler->send("421356:" + std::to_string(this->m_id));
			m_networkHandler->send(m_networkHandler->getApiHelper()->buildNewApiRequest(m_networkHandler->getApiHelper()->REQUEST_BUILDING_UPGRADE, std::to_string(m_id)));
			//this->m_networkHandler->send(network::client::ClientMessageType::CLIENT_MESSAGE_TYPE_REQUEST, 421356, std::to_string(this->m_id));
			auto msg = this->m_networkHandler->getMessage();
			auto answers = bl::common::Toolbox::split(msg.getBody().message, ":");
			if (msg.getBody().type == network::server::SERVER_MESSAGE_TYPE_ANSWER_OK && answers[0] == std::to_string(this->m_id)) {
				this->m_level = static_cast<unsigned int>(std::stoi(answers[1]));
				return (true);
			} else {
				return (false);
			}
		}

		const common::game::Resources &BuildingModel::getResourcesNeeded() const {
			return (this->m_resourcesNeeded);
		}

		const std::string &BuildingModel::getDesc() const {
			return (this->m_desc);
		}

		bool BuildingModel::isUnlocked() const {
			return m_unlocked;
		}
	}
}