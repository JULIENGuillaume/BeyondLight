//
// Created by Guillaume on 06/02/2018.
//

#include "IridiumRefinery.hh"
#include "IronMine.hh"
#include "ResearchCenter.hh"
#include "CrystalExtractor.hh"
#include "../planet/Planet.hh"

bl::server::game::building::IridiumRefinery::IridiumRefinery(bl::server::game::planet::Planet &planet) :
		ABuilding(IridiumRefinery::id, "Iridium refinery", "Refine a part of the iron production to iridium. Reduce iron production.", {
				resource::UpgradeCost(common::game::Resources(10000, 3000), 60),
				resource::UpgradeCost(common::game::Resources(50000, 20000, 200), 600),
				resource::UpgradeCost(common::game::Resources(120000, 60000, 2000), 6000)
		}, {1}, {{IronMine::id, 6}, {CrystalExtractor::id, 4}}, planet)
{}

nlohmann::json bl::server::game::building::IridiumRefinery::serialize() const {
	nlohmann::json json = ABuilding::serialize();
	json["timeLeftFromProd"] = this->m_timeLeftFromLastProd;
	return json;
}

bl::common::pattern::ISerializable *bl::server::game::building::IridiumRefinery::deserialize(nlohmann::json const &json) {
	this->m_timeLeftFromLastProd = json["timeLeftFromProd"];
	ABuilding::deserialize(json);
	return this;
}

void bl::server::game::building::IridiumRefinery::updateResource() {
	updateBuildingOnDeltaTime(this->m_chrono.getElapsedSeconds());
}

void bl::server::game::building::IridiumRefinery::updateBuildingOnDeltaTime(uint64_t seconds) {
	if (this->m_level >= 1) {
		auto actualTime = seconds + this->m_timeLeftFromLastProd;
		if (actualTime >= this->m_secondsForProduction) {
			this->m_planet.getStockResources().addIridium((actualTime / this->m_secondsForProduction) * (static_cast<uint64_t>(2 * std::pow(1.12, this->m_level))));
			this->m_timeLeftFromLastProd = actualTime % this->m_secondsForProduction;
			this->m_chrono.reset();
		}
	} else {
		this->m_chrono.reset();
	}
}
