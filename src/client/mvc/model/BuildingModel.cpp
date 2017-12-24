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
			std::cout << "Basic building model has been created" << std::endl;
			this->update();
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
					/*this->m_networkHandler->send("3242");
					std::string jsonReceived1 = this->m_networkHandler->getLine();
					std::cout << "Received " << jsonReceived1 << std::endl;*/
					//this->m_networkHandler->send("4242");
					std::cout << "Sending from building model" << std::endl;
					this->m_networkHandler->send(network::client::ClientMessageType::CLIENT_MESSAGE_TYPE_REQUEST, 4242, "");
					auto msg = this->m_networkHandler->getMessage();
					std::cout << "Received a msg with the code " << msg.getBody().code << " and the answer is " << msg.getBody().type << std::endl;
					std::string jsonReceived = msg.getBody().message;
					std::cout << "Received " << jsonReceived << std::endl;
					nlohmann::json buildings;
					if (msg.getBody().type == network::server::SERVER_MESSAGE_TYPE_ANSWER_OK) {
						buildings = ((nlohmann::json::parse(jsonReceived))["buildings"]);
						std::cout << "Buildings is " << buildings.dump() << std::endl;
					} else {
						std::cerr << "Invalid reply" << std::endl;
						return;
					}
					nlohmann::json building;
					for (const auto& build : buildings) {
						building = build;
						std::cout << "building = " << building.dump() << std::endl;
						if (building.at("id") == m_id)
							break;
					}

					m_level = building["level"];
					std::cout << "Level is " << m_level << std::endl;
					m_name = building["name"];
					m_desc = building["description"];
					std::cout << "Name is " << m_name << std::endl;
					this->m_resourcesNeeded.deserialize(building["resourcesRequired"]["resources"]);
				} catch (...) {
					std::cerr << "json parse error" << std::endl;
					return;
				}
			}
		}

		bool BuildingModel::incrLevel() {
			//this->m_networkHandler->send("421356:" + std::to_string(this->m_id));
			this->m_networkHandler->send(network::client::ClientMessageType::CLIENT_MESSAGE_TYPE_REQUEST, 421356, std::to_string(this->m_id));
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
	}
}