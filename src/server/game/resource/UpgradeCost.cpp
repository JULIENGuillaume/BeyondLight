//
// Created by Guillaume on 04/12/2017.
//

#include <iostream>
#include "UpgradeCost.hh"


server::game::resource::UpgradeCost::UpgradeCost(bool valid) {
	this->m_validity = valid;
}

nlohmann::json server::game::resource::UpgradeCost::serialize() const {
	nlohmann::json json;
	json["iron"] = 8007;
	json["crystal"] = 42;
	json["iridium"] = 2;
	json["energy"] = 1337;
	json["upgradeTime"] = 60;

	return json;
}

common::pattern::ISerializable *server::game::resource::UpgradeCost::deserialize(nlohmann::json const &json) {
	std::cout << "Got following resources: " << std::endl;
	std::cout << "\t-Iron: " << json["iron"] << std::endl;
	std::cout << "\t-Crystal: " << json["crystal"] << std::endl;
	std::cout << "\t-Iridium: " << json["iridium"] << std::endl;
	std::cout << "\t-Energy: " << json["energy"] << std::endl;
	std::cout << "\t-Upgrade time: " << json["upgradeTime"] << std::endl;
	return this;
}

bool server::game::resource::UpgradeCost::isValid() const {
	return m_validity;
}

bool server::game::resource::UpgradeCost::launchUpgrade() const {
	return true;
}
