//
// Created by Guillaume on 19/12/2017.
//

#include "../planet/Planet.hh"
#include "CrystalExtractor.hh"

bl::server::game::building::CrystalExtractor::CrystalExtractor(planet::Planet &planet) :
	ABuilding(1, "Iron mine", "A mine to retrieve iron from the depth of the earth", {
		resource::UpgradeCost(common::game::Resources(200), 60),
		resource::UpgradeCost(common::game::Resources(1500, 200), 200),
		resource::UpgradeCost(common::game::Resources(4000, 1200), 800),
		resource::UpgradeCost(common::game::Resources(10000, 3000), 1200)
	}, planet) {
}

void bl::server::game::building::CrystalExtractor::updateResource() {
	auto actualTime = this->m_chrono.getElapsedSeconds() + this->m_timeLeftFromLastProd;
	if (actualTime >= this->m_secondsForProduction) {
		this->m_planet.getStockResources().addCrystal((actualTime / this->m_secondsForProduction) * (static_cast<uint64_t>(5 * std::pow(1.20, this->m_level))));
		this->m_timeLeftFromLastProd = actualTime % this->m_secondsForProduction;
		this->m_chrono.reset();
	}
}
