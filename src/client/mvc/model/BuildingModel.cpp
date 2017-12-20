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
				std::shared_ptr<network::client::NetworkHandler> networkHandler,
				unsigned int id
		) :
				ABaseModel::ABaseModel(networkHandler),
				m_id(id) {
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
					this->m_networkHandler->send("4242");
					std::string jsonReceived = this->m_networkHandler->getLine();
					std::cout << "Received " << jsonReceived << std::endl;
					auto toks = bl::common::Toolbox::splitAtMax(jsonReceived, ":", 1);
					nlohmann::json buildings;
					if (toks.size() == 2 && std::atoi(toks[0].c_str()) == 14242) {
						buildings = ((nlohmann::json::parse(toks[1]))["buildings"]);
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
			this->m_networkHandler->send("421356:" + std::to_string(this->m_id));
			auto answers = bl::common::Toolbox::split(this->m_networkHandler->getLine(), ":");
			if (answers[0] == "321") {
				return (false);
			} else if (answers[0] == "421357" && answers[1] == std::to_string(this->m_id)) {
				this->m_level = std::stoi(answers[2]);
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