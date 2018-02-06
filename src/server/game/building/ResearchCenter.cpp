//
// Created by Guillaume on 06/02/2018.
//

#include "ResearchCenter.hh"
#include "IronMine.hh"
#include "CrystalExtractor.hh"
#include "../planet/Planet.hh"

bl::server::game::building::ResearchCenter::ResearchCenter(bl::server::game::planet::Planet &planet) :
		ABuilding(ResearchCenter::id, "Research center", "A building to host your scientists and their experimentation", {
				resource::UpgradeCost(common::game::Resources(5000, 5000), 1000),
				resource::UpgradeCost(common::game::Resources(20000, 4000, 500), 36000)
		}, {}, {{IronMine::id, 4}, {CrystalExtractor::id, 2}}, planet) {
}

void bl::server::game::building::ResearchCenter::updateBuildingOnDeltaTime(uint64_t seconds) {
}
