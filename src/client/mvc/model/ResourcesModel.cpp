//
// Created by diguie_t on 12/19/2017.
//

#include "ResourcesModel.hh"
#include "../../../common/Toolbox.hh"

namespace bl {
	namespace mvc {
		void ResourcesModel::update() {
			if (this->m_networkHandler.get()) {
				try {
					//this->m_networkHandler->send("3242");
					m_networkHandler->send(m_networkHandler->getApiHelper()->buildNewApiRequest(m_networkHandler->getApiHelper()->REQUEST_BUILDING_UPGRADE));
					//this->m_networkHandler->send(network::client::ClientMessageType::CLIENT_MESSAGE_TYPE_REQUEST, 3242, "");
					auto msg = this->m_networkHandler->getMessage().getBody();
					std::string jsonReceived = msg.message;
					nlohmann::json resources;
					if (msg.type == network::server::SERVER_MESSAGE_TYPE_ANSWER_OK) {
						resources = nlohmann::json::parse(jsonReceived);
					} else {
						std::cerr << "Invalid reply" << std::endl;
						return;
					}
					this->m_resources.deserialize(resources["resources"]);
				} catch (...) {
					std::cerr << "json parse error" << std::endl;
					return;
				}
			}
		}

		ResourcesModel::ResourcesModel(
				std::shared_ptr<network::client::ClientNetworkHandler> networkHandler,
				const boost::uuids::uuid &uuid // todo see what we use after serv refactor
		) :
				ABaseModel::ABaseModel(networkHandler),
				m_uuid(uuid) {
		}

		const common::game::Resources &ResourcesModel::getResources() const {
			return (this->m_resources);
		}
	}
}