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
					this->m_networkHandler->send("3242");
					std::string jsonReceived = this->m_networkHandler->getLine();
					std::cout << "Received " << jsonReceived << std::endl;
					auto toks = ::common::Toolbox::splitAtMax(jsonReceived, ":", 1);
					nlohmann::json resources;
					if (toks.size() == 2 && std::atoi(toks[0].c_str()) == 324201) {
						resources = nlohmann::json::parse(toks[1]);
						std::cout << "Resources is " << resources.dump() << std::endl;
					} else {
						std::cerr << "Invalid reply" << std::endl;
						return;
					}
					this->m_resources.deserialize(resources);
				} catch (...) {
					std::cerr << "json parse error" << std::endl;
					return;
				}
			}
		}

		ResourcesModel::ResourcesModel(
				std::shared_ptr<network::client::NetworkHandler> networkHandler,
				const boost::uuids::uuid &uuid // todo see what we use after serv refactor
		) :
				ABaseModel::ABaseModel(networkHandler),
				m_uuid(uuid) {
		}
	}
}