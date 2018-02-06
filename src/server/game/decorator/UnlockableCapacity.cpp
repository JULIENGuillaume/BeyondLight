//
// Created by Guillaume Julien on 05/02/2018.
//

#include "UnlockableCapacity.hh"
#include "../planet/Planet.hh"
#include "../../ServerCore.hh"

bool bl::server::game::decorator::UnlockableCapacity::unlock(const planet::Planet &planet) {
	std::cout << "Checking unlocked..." << std::endl;
	if (m_unlocked)
		return true;
	std::cout << "Checking unlockable..." << std::endl;
	if (!isUnlockable(planet))
		return false;
	std::cout << "Unlocking" << std::endl;
	m_unlocked = true;
	return true;
}

bool bl::server::game::decorator::UnlockableCapacity::isUnlocked() const {
	return m_unlocked;
}

bool bl::server::game::decorator::UnlockableCapacity::isUnlockable(planet::Planet const &planet) const {
	std::cout << "Getting user..." << std::endl;
	auto user = ServerCore::getData().activeUsers.at(planet.getPlanetOwner());
	std::cout << "Getted user" << std::endl;
	for (auto id : this->m_researchDependencies) {
		std::cout << "Checking research of id " << id << std::endl;
		if (user->getTechnologies().find(id) == user->getTechnologies().end())
			return false;
	}
	for (auto buildings : this->m_buildingDependencies) {
		std::cout << "Checking building of id " << buildings.first << " and of level " << buildings.second << std::endl;
		if (planet.getBuildingInfo(buildings.first)->getLevel() < buildings.second)
			return false;
	}
	std::cout << "Returning unlockable..." << std::endl;
	return true;
}

void bl::server::game::decorator::UnlockableCapacity::addResearchDependency(int dependency) {
	this->m_researchDependencies.push_back(dependency);
}

void bl::server::game::decorator::UnlockableCapacity::addBuildingDependency(
		int dependency,
		int level
) {
	this->m_buildingDependencies.emplace(dependency, level);
}

bl::server::game::decorator::UnlockableCapacity::UnlockableCapacity(
		const std::vector<int> &researchDependencies,
		const std::unordered_map<int, int> &buildingDependencies
) :
		m_researchDependencies(researchDependencies),
		m_buildingDependencies(buildingDependencies) {
}
