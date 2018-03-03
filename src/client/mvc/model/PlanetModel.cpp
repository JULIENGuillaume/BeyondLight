//
// Created by diguie_t on 3/3/2018.
//

#include <iostream>
#include "ClientNetworkHandler.hh"
#include "../../../common/Toolbox.hh"
#include "json.hpp"
#include "ABaseModel.hh"
#include "PlanetModel.hh"

namespace bl {
	namespace mvc {
		PlanetModel::PlanetModel(
				std::shared_ptr<network::client::ClientNetworkHandler> networkHandler,
				unsigned int id
		) :
				ABaseModel::ABaseModel(networkHandler),
				m_position(id) {
			//this->update();
		}

		void PlanetModel::update() {
			this->m_attackable = true;
			this->m_ownerUserName = "Allan add username";
			this->m_resources.setIron(20000);
			this->m_resources.setIridium(1000);
			/*if (this->m_networkHandler.get()) { // todo
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

		unsigned int PlanetModel::getPosition() const {
			return m_position;
		}

		const std::string &PlanetModel::getOwnerUserName() const {
			return m_ownerUserName;
		}

		bool PlanetModel::isAttackable() const {
			return m_attackable;
		}

		const common::game::Resources &PlanetModel::getResources() const {
			return m_resources;
		}
	}
}