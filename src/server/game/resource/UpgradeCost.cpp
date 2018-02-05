//
// Created by Guillaume on 04/12/2017.
//

#include <iostream>
#include "UpgradeCost.hh"

bl::server::game::resource::UpgradeCost::UpgradeCost(bool valid) {
	this->m_validity = valid;
	this->m_resources = common::game::Resources();
}

bl::server::game::resource::UpgradeCost::UpgradeCost(
		const bl::common::game::Resources &resources,
		uint64_t upgradeTime
) :
		m_validity(true),
		m_resources(resources),
		m_upgradeTime(upgradeTime) {
}

nlohmann::json bl::server::game::resource::UpgradeCost::serialize() const {
	nlohmann::json json;
	json["resources"] = this->m_resources.serialize();
	json["upgradeTime"] = this->m_upgradeTime;
	return json;
}

bl::common::pattern::ISerializable *bl::server::game::resource::UpgradeCost::deserialize(nlohmann::json const &json) {
	this->m_resources.deserialize(json["resources"]);
	this->m_upgradeTime = json["upgradeTime"];
	return this;
}

bool bl::server::game::resource::UpgradeCost::isValid() const {
	return m_validity;
}

bool bl::server::game::resource::UpgradeCost::launchUpgrade(bl::common::game::Resources &stock) const {
	if (stock >= this->m_resources) {
		stock = stock - this->m_resources;
		return true;
	}
	return false;
}
