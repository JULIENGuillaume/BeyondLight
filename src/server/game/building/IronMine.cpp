//
// Created by Guillaume on 04/12/2017.
//

#include <iostream>
#include "../planet/Planet.hh"
#include "IronMine.hh"

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
	if (this->m_level < 1) {
		this->m_chrono.reset();
		return;
	}
	auto actualTime = this->m_chrono.getElapsedSeconds() + this->m_timeLeftFromLastProd;
	if (actualTime >= this->m_secondsForProduction) {
		this->m_planet.getStockResources().addIron((actualTime / this->m_secondsForProduction) * (static_cast<uint64_t>(10 * std::pow(1.42, this->m_level))));
		this->m_timeLeftFromLastProd = actualTime % this->m_secondsForProduction;
		this->m_chrono.reset();
	}
}
