//
// Created by Guillaume Julien on 05/02/2018.
//

#include "UnlockableCapacity.hh"
#include "../planet/Planet.hh"
#include "../../ServerCore.hh"

bool bl::server::game::decorator::UnlockableCapacity::unlock(const planet::Planet &planet) {
	if (m_unlocked)
		return true;
	if (!isUnlockable(planet))
		return false;
	m_unlocked = true;
	return true;
}

bool bl::server::game::decorator::UnlockableCapacity::isUnlocked() const {
	return m_unlocked;
}

bool bl::server::game::decorator::UnlockableCapacity::isUnlockable(planet::Planet const &planet) const {
	auto user = ServerCore::getData().activeSessions.at(planet.getPlanetOwner())->getUser();
	for (auto id : this->m_researchDependencies) {
		if (user.getTechnologies().find(id) == user.getTechnologies().end())
			return false;
	}
	for (auto buildings : this->m_buildingDependencies) {
		if (planet.getBuildingInfo(buildings.first)->getLevel() < buildings.second)
			return false;
	}
	return false;
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
