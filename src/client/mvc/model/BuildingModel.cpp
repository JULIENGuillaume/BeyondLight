//
// Created by diguie_t on 12/14/2017.
//

#include "json.hpp"
#include "BuildingModel.hh"
#include "../../../common/Toolbox.hh"

namespace bl {
	namespace mvc {
		void BuildingModel::markForUpdate() {
			update();
		}

		bool BuildingModel::needUpdate() {
			return false;
		}

		void BuildingModel::markToCommitChange() {
		}

		bool BuildingModel::hasChange() {
			return false;
		}

		BuildingModel::BuildingModel(
				std::shared_ptr<network::client::NetworkHandler> networkHandler,
				unsigned int id
		) :
				ABaseModel::ABaseModel(networkHandler),
				m_hasChange(false),
				m_needUpdate(true),
				m_id(id) {
			this->markForUpdate();
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

		unsigned int BuildingModel::getIronNeeded() const {
			return m_ironNeeded;
		}

		unsigned int BuildingModel::getCrystalNeeded() const {
			return m_crystalNeeded;
		}

		unsigned int BuildingModel::getIridiumNeeded() const {
			return m_iridiumNeeded;
		}

		unsigned int BuildingModel::getEnergyNeeded() const {
			return m_energyNeeded;
		}

		void BuildingModel::update() {
			if (this->m_networkHandler.get()) {
				try {
					this->m_networkHandler->send("4242");
					std::string jsonReceived = this->m_networkHandler->getLine();
					auto toks = common::Toolbox::splitAtMax(jsonReceived, ":", 1);
					nlohmann::json building;
					if (toks.size() == 2 && std::atoi(toks[0].c_str()) == 14242) {
						building = nlohmann::json::parse(toks[1]);
					} else {
						std::cerr << "Invalid reply" << std::endl;
						return;
					}
					auto id = building.at("id").get<unsigned int>();
					auto level = building.at("id").get<unsigned int>();
					std::string name = building.at("name").get<std::string>();
					auto iron = building.at(
							"resourcesRequired").get<nlohmann::json>().at(
							"iron").get<unsigned int>();
					auto crystal = building.at(
							"resourcesRequired").get<nlohmann::json>().at(
							"crystal").get<unsigned int>();
					auto iridium = building.at(
							"resourcesRequired").get<nlohmann::json>().at(
							"iridium").get<unsigned int>();
					auto energy = building.at(
							"resourcesRequired").get<nlohmann::json>().at(
							"energy").get<unsigned int>();
				} catch (...) {
					std::cerr << "json parse error" << std::endl;
					return;
				}
			}
		}

		bool BuildingModel::incrLevel() {
			this->m_networkHandler->send("421356:" + std::to_string(this->m_id));
			auto answers = common::Toolbox::split(this->m_networkHandler->getLine(), ":");
			if (answers[0] == "321") {
				return (false);
			} else if (answers[0] == "421357" && answers[1] == std::to_string(this->m_id)) {
				this->m_level = std::stoi(answers[2]);
				return (true);
			} else {
				return (false);
			}
		}
	}
}