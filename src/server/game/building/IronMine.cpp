//
// Created by Guillaume on 04/12/2017.
//

#include "../planet/Planet.hh"
#include "IronMine.hh"

bl::server::game::building::IronMine::IronMine(planet::Planet &planet) :
		ABuilding(1, "Iron mine", "A mine to retrieve iron from the depth of the earth", {
				resource::UpgradeCost(true),
				resource::UpgradeCost(true),
				resource::UpgradeCost(true),
				resource::UpgradeCost(true),
				resource::UpgradeCost(true)
		}, planet) {}

void bl::server::game::building::IronMine::updateResource() {
	//TODO: update resources according to time, not on every call
	this->m_planet.getStockResources().addIron(static_cast<uint64_t>(10 * std::pow(1.42, this->m_level)));
}
