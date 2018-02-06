//
// Created by Guillaume on 19/12/2017.
//

#include <iostream>
#include "../planet/Planet.hh"
#include "CrystalExtractor.hh"
#include "IronMine.hh"

nlohmann::json bl::server::game::building::CrystalExtractor::serialize() const {
	nlohmann::json json = ABuilding::serialize();
	json["timeLeftFromProd"] = this->m_timeLeftFromLastProd;
	return json;
}

bl::common::pattern::ISerializable *bl::server::game::building::CrystalExtractor::deserialize(nlohmann::json const &json) {
	this->m_timeLeftFromLastProd = json["timeLeftFromProd"];
	ABuilding::deserialize(json);
	return this;
}

bl::server::game::building::CrystalExtractor::CrystalExtractor(planet::Planet &planet) :
		ABuilding(CrystalExtractor::id, "Crystal extractor", "Retrieve powerful crystals", {
				resource::UpgradeCost(common::game::Resources(200), 60),
				resource::UpgradeCost(common::game::Resources(1500, 200), 200),
				resource::UpgradeCost(common::game::Resources(4000, 1200), 800),
				resource::UpgradeCost(common::game::Resources(10000, 3000), 1200),
				resource::UpgradeCost(common::game::Resources(50000, 10000, 1000), 12000)
		}, {}, {{IronMine::id, 2}}, planet) {
}

void bl::server::game::building::CrystalExtractor::updateResource() {
	updateBuildingOnDeltaTime(this->m_chrono.getElapsedSeconds());
	this->m_chrono.reset();
}

void bl::server::game::building::CrystalExtractor::updateBuildingOnDeltaTime(uint64_t seconds) {
	if (this->m_level >= 1) {
		auto actualTime = seconds + this->m_timeLeftFromLastProd;
		if (actualTime >= this->m_secondsForProduction) {
			this->m_planet.getStockResources().addCrystal((actualTime / this->m_secondsForProduction) * (static_cast<uint64_t>(5 * std::pow(1.20, this->m_level))));
			this->m_timeLeftFromLastProd = actualTime % this->m_secondsForProduction;
			this->m_chrono.reset();
		}
	} else {
		this->m_chrono.reset();
	}
}
