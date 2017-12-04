//
// Created by Guillaume on 04/12/2017.
//

#include "IronMine.hh"

server::game::building::IronMine::IronMine() : ABuilding(1,
                                                         "Iron mine",
                                                         "A mine to retrieve iron from the depth of the earth",
                                                         {
		                                                         resource::UpgradeCost(true),
		                                                         resource::UpgradeCost(true),
		                                                         resource::UpgradeCost(true),
		                                                         resource::UpgradeCost(true),
		                                                         resource::UpgradeCost(true)
                                                         }) {}


