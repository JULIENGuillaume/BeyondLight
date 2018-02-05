//
// Created by Guillaume Julien on 05/02/2018.
//

#include "UpgradableCapacity.hh"

nlohmann::json bl::server::game::decorator::UpgradableCapacity::serialize() const {
	nlohmann::json json;
	json["level"] = m_level;
	if (this->getUpgradeCost().isValid()) {
		json["resourcesRequired"] = this->getUpgradeCost().serialize();
	}
	json["isUpgrading"] = m_upgrading;
	json["timeLeft"] = m_upgradeTimeLeft;
	json["serializeTime"] = time(nullptr);
	return json;
}

bl::common::pattern::ISerializable *bl::server::game::decorator::UpgradableCapacity::deserialize(nlohmann::json const &json) {
	m_level = json["level"];
	m_upgrading = json["isUpgrading"];
	m_upgradeTimeLeft = json["timeLeft"];
	return this;
}

int bl::server::game::decorator::UpgradableCapacity::getLevel() const {
	return m_level;
}

void bl::server::game::decorator::UpgradableCapacity::setLevel(int level) {
	m_level = level;
}

bool bl::server::game::decorator::UpgradableCapacity::isUpgrading() const {
	return m_upgrading;
}

void bl::server::game::decorator::UpgradableCapacity::setUpgrading(bool upgrading) {
	m_upgrading = upgrading;
}

int bl::server::game::decorator::UpgradableCapacity::getUpgradeTimeLeft() const {
	return m_upgradeTimeLeft;
}

void bl::server::game::decorator::UpgradableCapacity::setUpgradeTimeLeft(int upgradeTimeLeft) {
	m_upgradeTimeLeft = upgradeTimeLeft;
}

bl::server::game::resource::UpgradeCost bl::server::game::decorator::UpgradableCapacity::getUpgradeCost() const {
	static auto noUpgradeAvailable = bl::server::game::resource::UpgradeCost(false);
	if (this->m_level >= (int) this->m_upgrades.size()) {
		return noUpgradeAvailable;
	}
	return this->m_upgrades[this->m_level];
}

bool bl::server::game::decorator::UpgradableCapacity::upgrade(common::game::Resources &stock) {
	auto res = this->getUpgradeCost();
	if (res.isValid()) {
		auto ret = res.launchUpgrade(stock);
		if (ret) {
			this->m_level++;
		}
		return ret;
	}
	return false;
}

bl::server::game::decorator::UpgradableCapacity::UpgradableCapacity(const std::vector<bl::server::game::resource::UpgradeCost> &upgrades) :
		m_upgrades(upgrades) {}
