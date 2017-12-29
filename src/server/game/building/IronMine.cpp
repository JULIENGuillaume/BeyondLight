//
// Created by Guillaume on 04/12/2017.
//

#include <iostream>
#include "../planet/Planet.hh"
#include "IronMine.hh"

nlohmann::json bl::server::game::building::IronMine::serialize() const {
	nlohmann::json json = ABuilding::serialize();
	json["timeLeftFromProd"] = this->m_timeLeftFromLastProd;
	return json;
}

bl::common::pattern::ISerializable *bl::server::game::building::IronMine::deserialize(nlohmann::json const &json) {
	this->m_timeLeftFromLastProd = json["timeLeftFromProd"];
	ABuilding::deserialize(json);
	return this;
}

bl::server::game::building::IronMine::IronMine(planet::Planet &planet) :
		ABuilding(1, "Iron mine", "A mine to retrieve iron from the depth of the earth", {
				resource::UpgradeCost(common::game::Resources(), 60),
				resource::UpgradeCost(common::game::Resources(100), 200),
				resource::UpgradeCost(common::game::Resources(1000, 50), 800),
				resource::UpgradeCost(common::game::Resources(3000, 300), 1200),
				resource::UpgradeCost(common::game::Resources(3000, 300, 50), 3600)
		}, planet) {
}

void bl::server::game::building::IronMine::updateResource() {
	updateBuildingOnDeltaTime(this->m_chrono.getElapsedSeconds());
	this->m_chrono.reset();
}

void bl::server::game::building::IronMine::updateBuildingOnDeltaTime(uint64_t seconds) {
	if (this->m_level >= 1) {
		auto actualTime = seconds + this->m_timeLeftFromLastProd;
		if (actualTime >= this->m_secondsForProduction) {
			this->m_planet.getStockResources().addIron((actualTime / this->m_secondsForProduction) * (static_cast<uint64_t>(10 * std::pow(1.42, this->m_level))));
			this->m_timeLeftFromLastProd = actualTime % this->m_secondsForProduction;
		}
	}
}
