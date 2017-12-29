//
// Created by Guillaume on 04/12/2017.
//

#include "../planet/Planet.hh"
#include "ABuilding.hh"

bl::server::game::building::ABuilding::ABuilding(
		int id,
		std::string const &name,
		std::string const &desc,
		std::vector<resource::UpgradeCost> const &upgrades,
		planet::Planet &planet
) :
		m_id(id),
		m_name(name),
		m_desc(desc),
		m_upgrades(upgrades),
		m_planet(planet) {}

nlohmann::json bl::server::game::building::ABuilding::serialize() const {
	nlohmann::json json;
	json["id"] = m_id;
	json["level"] = m_level;
	if (this->getResources().isValid()) {
		json["resourcesRequired"] = this->getResources().serialize();
	}
	json["isUpgrading"] = m_upgrading;
	json["timeLeft"] = m_upgradeTimeLeft;
	json["name"] = m_name;
	json["description"] = m_desc;
	return json;
}

bl::common::pattern::ISerializable *bl::server::game::building::ABuilding::deserialize(nlohmann::json const &json) {
	m_id = json["id"];
	m_level = json["level"];
	m_upgrading = json["isUpgrading"];
	m_upgradeTimeLeft = json["timeLeft"];
	m_name = json["name"];
	m_desc = json["description"];

	return this;
}

const std::string &bl::server::game::building::ABuilding::getName() const {
	return this->m_name;
}

const std::string &bl::server::game::building::ABuilding::getDescription() const {
	return this->m_desc;
}

const bl::server::game::resource::UpgradeCost &bl::server::game::building::ABuilding::getResources() const {
	static auto noUpgradeAvailable = bl::server::game::resource::UpgradeCost(false);
	if (this->m_level >= (int) this->m_upgrades.size()) {
		return noUpgradeAvailable;
	}
	return this->m_upgrades[this->m_level];
}

int bl::server::game::building::ABuilding::getId() const {
	return this->m_id;
}

int bl::server::game::building::ABuilding::getLevel() const {
	return this->m_level;
}

bool bl::server::game::building::ABuilding::isUpgrading() const {
	return this->m_upgrading;
}

int bl::server::game::building::ABuilding::getFullUpgradeTime() const {
	return 60;
}

int bl::server::game::building::ABuilding::getTimeLeft() const {
	return this->m_upgradeTimeLeft;
}

bool bl::server::game::building::ABuilding::upgrade() {
	auto res = this->getResources();
	if (res.isValid()) {
		auto ret = res.launchUpgrade(this->m_planet.getStockResources());
		if (ret) {
			this->m_level++;
		}
		return ret;
	}
	return false;
}
