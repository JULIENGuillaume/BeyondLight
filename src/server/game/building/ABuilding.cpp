//
// Created by Guillaume on 04/12/2017.
//

#include "ABuilding.hh"

server::game::building::ABuilding::ABuilding(int id,
                                             std::string const &name,
                                             std::string const &desc,
                                             std::vector<server::game::resource::UpgradeCost> const &upgrades) : m_id(id),
                                                                                                                 m_name(name),
                                                                                                                 m_desc(desc),
                                                                                                                 m_upgrades(upgrades) {}

nlohmann::json server::game::building::ABuilding::serialize() const {
	nlohmann::json json;

	json["id"] = m_id;
	json["level"] = m_level;
	if (this->getResources().isValid())
		json["resourcesRequired"] = this->getResources().serialize();
	json["isUpgrading"] = m_upgrading;
	json["timeLeft"] = m_upgradeTimeLeft;
	json["name"] = m_name;
	json["description"] = m_desc;

	return json;
}

common::pattern::ISerializable *server::game::building::ABuilding::deserialize(nlohmann::json const &json) {
	return this;
}

const std::string &server::game::building::ABuilding::getName() const {
	return this->m_name;
}

const std::string &server::game::building::ABuilding::getDescription() const {
	return this->m_desc;
}

const server::game::resource::UpgradeCost &server::game::building::ABuilding::getResources() const {
	if (this->m_level >= this->m_upgrades.size())
		return server::game::resource::UpgradeCost(false);
	return this->m_upgrades[this->m_level];
}

int server::game::building::ABuilding::getId() const {
	return this->m_id;
}

int server::game::building::ABuilding::getLevel() const {
	return this->m_level;
}

bool server::game::building::ABuilding::isUpgrading() const {
	return this->m_upgrading;
}

int server::game::building::ABuilding::getFullUpgradeTime() const {
	return 60;
}

int server::game::building::ABuilding::getTimeLeft() const {
	return this->m_upgradeTimeLeft;
}
