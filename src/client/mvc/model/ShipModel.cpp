//
// Created by diguie_t on 3/3/2018.
//

#include <iostream>
#include <ClientNetworkHandler.hh>
#include "ShipModel.hh"
#include "../../../common/Toolbox.hh"
#include "json.hpp"
#include "ABaseModel.hh"

namespace bl {
	namespace mvc {
		ShipModel::ShipModel(
				std::shared_ptr<network::client::ClientNetworkHandler> networkHandler,
				unsigned int id
		) :
				ABaseModel::ABaseModel(networkHandler),
				m_id(id) {
			//this->update();
		}

		unsigned int ShipModel::getId() const {
			return m_id;
		}

		const std::string &ShipModel::getName() const {
			return m_name;
		}

		void ShipModel::update() {
			this->m_unlocked = true;
			this->m_name = "Nexus";
			this->m_desc = "The Nexus ship";
			this->m_quantity = 421015;
			this->m_resourcesNeeded.setIron(2000);
			this->m_resourcesNeeded.setIridium(1000);
			/*if (this->m_networkHandler.get()) {
				try {
					m_networkHandler->send(m_networkHandler->getApiHelper()->buildNewApiRequest(m_networkHandler->getApiHelper()->REQUEST_TECHNOLOGY_INFO,
																								std::to_string(m_id)));
					auto msg = this->m_networkHandler->getMessage();
					if (msg.getBody().type != bl::network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK)
						return;
					nlohmann::json technology = nlohmann::json::parse(msg.getBody().message);
					std::cerr << "Technology: " << msg.getBody().message << std::endl;
					m_id = technology["id"];
					m_name = technology["name"];
					m_desc = technology["description"];
					m_unlocked = technology["unlocked"];
					//this->m_resourcesNeeded.deserialize(building["resourcesRequired"]["resources"]);
				} catch (std::exception &e) {
					std::cerr << "json parse error building " << e.what() << std::endl;
					return;
				}
			}*/
		}

		bool ShipModel::buildShip(unsigned int nbToBuild) {
			return (true);
		}

		const common::game::Resources &ShipModel::getResourcesNeeded() const {
			return (this->m_resourcesNeeded);
		}

		const std::string &ShipModel::getDesc() const {
			return (this->m_desc);
		}

		bool ShipModel::isUnlocked() const {
			return (this->m_unlocked);
		}

		unsigned int ShipModel::getQuantity() const {
			return m_quantity;
		}
	}
}