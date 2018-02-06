//
// Created by Guillaume on 04/12/2017.
//

#include <iostream>
#include "../planet/Planet.hh"
#include "ABuilding.hh"

bl::server::game::building::ABuilding::ABuilding(
		int id,
		std::string const &name,
		std::string const &desc,
		std::vector<resource::UpgradeCost> const &upgrades,
		planet::Planet &planet
) :
		m_planet(planet) {
	m_id = id;
	m_name = name;
	m_description = desc;
	m_upgrades = upgrades;
}

nlohmann::json bl::server::game::building::ABuilding::serialize() const {
	nlohmann::json json = decorator::IdentifiableCapacity::serialize();
	auto upgradablePart = decorator::UpgradableCapacity::serialize();
	json.insert(upgradablePart.begin(), upgradablePart.end());
	return json;
}

bl::common::pattern::ISerializable *bl::server::game::building::ABuilding::deserialize(nlohmann::json const &json) {
	decorator::IdentifiableCapacity::deserialize(json);
	decorator::UpgradableCapacity::deserialize(json);
	time_t lastUpdateTime = json["serializeTime"];
	this->updateBuildingOnDeltaTime(static_cast<uint64_t>(difftime(time(nullptr), lastUpdateTime)));
	return this;
}

bool bl::server::game::building::ABuilding::upgrade() {
	return decorator::UpgradableCapacity::upgrade(this->m_planet.getStockResources());
}
