//
// Created by Guillaume on 06/02/2018.
//

#include "ResearchCenter.hh"
#include "IronMine.hh"
#include "CrystalExtractor.hh"
#include "../planet/Planet.hh"
#include "../../ServerCore.hh"

bl::server::game::building::ResearchCenter::ResearchCenter(bl::server::game::planet::Planet &planet) :
		ABuilding(ResearchCenter::id, "Research center", "A building to host your scientists and their experimentation", {
				resource::UpgradeCost(common::game::Resources(5000, 5000), 1000),
				resource::UpgradeCost(common::game::Resources(20000, 4000, 500), 36000)
		}, {}, {{IronMine::id, 4}, {CrystalExtractor::id, 2}}, planet) {
}

void bl::server::game::building::ResearchCenter::updateBuildingOnDeltaTime(uint64_t seconds) {
	if (this->m_actualResearch >= 0) {
		if (this->m_remainingUpdateTime > seconds)
			this->m_remainingUpdateTime -= seconds;
		else
			this->finalizeResearch();
	}
}

bool bl::server::game::building::ResearchCenter::startResearch(int id) {
	auto const& models = ServerCore::getModels().technologies;
	if (models.find(id) == models.end())
		return false;
	if (!models.at(id)->isUnlockable(this->m_planet))
		return false;
	this->m_remainingUpdateTime = models.at(id)->getResearchTime();
	this->m_actualResearch = id;
	this->m_chrono.reset();
	return true;
}

bool bl::server::game::building::ResearchCenter::isResearchGoing() const {
	return m_actualResearch >= 0;
}

int bl::server::game::building::ResearchCenter::getCurrentResearch() const {
	return m_actualResearch;
}

void bl::server::game::building::ResearchCenter::finalizeResearch() {
	auto user = ServerCore::getData().activeUsers[this->m_planet.getPlanetOwner()];
	user->addTechnology(this->m_actualResearch);
	this->m_actualResearch = -1;
}
