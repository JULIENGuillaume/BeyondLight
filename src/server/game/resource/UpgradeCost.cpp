//
// Created by Guillaume on 04/12/2017.
//

#include <iostream>
#include "UpgradeCost.hh"

bl::server::game::resource::UpgradeCost::UpgradeCost(bool valid) {
	this->m_validity = valid;
	this->m_resources = common::game::Resources();
}

bl::server::game::resource::UpgradeCost::UpgradeCost(
		const bl::common::game::Resources &resources,
		uint64_t upgradeTime
) :
		m_validity(true),
		m_resources(resources),
		m_upgradeTime(upgradeTime) {
}

nlohmann::json bl::server::game::resource::UpgradeCost::serialize() const {
	nlohmann::json json;
	json["resources"] = this->m_resources.serialize();
	json["upgradeTime"] = this->m_upgradeTime;
	return json;
}

bl::common::pattern::ISerializable *bl::server::game::resource::UpgradeCost::deserialize(nlohmann::json const &json) {
	/*std::cout << "Got following resources: " << std::endl;
	std::cout << "\t-Iron: " << json["iron"] << std::endl;
	std::cout << "\t-Crystal: " << json["crystal"] << std::endl;
	std::cout << "\t-Iridium: " << json["iridium"] << std::endl;
	std::cout << "\t-Energy: " << json["energy"] << std::endl;
	std::cout << "\t-Upgrade time: " << json["upgradeTime"] << std::endl;*/
	this->m_resources.deserialize(json["resources"]);
	this->m_upgradeTime = json["upgradeTime"];
	return this;
}

bool bl::server::game::resource::UpgradeCost::isValid() const {
	return m_validity;
}

bool bl::server::game::resource::UpgradeCost::launchUpgrade(bl::common::game::Resources &stock) const {
	//std::cout << "Iron stock is " << stock.getIron() << std::endl;
	//std::cout << "Iron needed is " << this->m_resources.getIron() << std::endl;
	if (stock >= this->m_resources) {
		stock = stock - this->m_resources;
		//std::cout << "Launch upgrades" << std::endl;
		return true;
	}
	//std::cout << "Do not launch upgrade" << std::endl;
	return false;
}
