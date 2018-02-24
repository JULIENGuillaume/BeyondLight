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
					std::cout << "Request resources" << std::endl;
					m_networkHandler->send(m_networkHandler->getApiHelper()->buildNewApiRequest(m_networkHandler->getApiHelper()->REQUEST_CURRENT_RESOURCES));
					//this->m_networkHandler->send(network::client::ClientMessageType::CLIENT_MESSAGE_TYPE_REQUEST, 3242, "");
					std::cout << "Getting answer" << std::endl;
					auto msg = this->m_networkHandler->getMessage();
					std::cout << "Message is " << msg << std::endl;
					if (msg.getBody().type != bl::network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK) {
						std::cout << "Answer failed..." << std::endl;
						return;
					}
					std::cout << "Succeed request" << std::endl;
					std::string jsonReceived = msg.getBody().message;
					nlohmann::json resources;
					if (msg.getBody().type == network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK) {
						resources = nlohmann::json::parse(jsonReceived);
					} else {
						std::cerr << "Invalid reply" << std::endl;
						return;
					}
					std::cout << resources.dump() << std::endl;
					std::cout << "Deserializing" << std::endl;
					this->m_resources.deserialize(resources);
					std::cout << "Bye bye" << std::endl;
				} catch (std::exception &e) {
					std::cerr << "json parse error resources: " << e.what() << std::endl;
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