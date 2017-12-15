//
// Created by Guillaume Julien on 14/12/2017.
//

#include "Planet.hh"
#include "../building/IronMine.hh"

bl::server::game::planet::Planet::Planet() :
		UniqueObject() {
	this->addBuilding(std::shared_ptr<building::IBuilding>(new building::IronMine(*this)));
}

bl::server::game::planet::Planet::Planet(const bl::server::game::planet::Planet &src) :
		UniqueObject(src),
		m_buildings(src.m_buildings) {
}

bl::common::game::Resources &bl::server::game::planet::Planet::getStockResources() {
	return this->m_stockResources;
}

const bl::common::game::Resources &bl::server::game::planet::Planet::getStockResources() const {
	return this->m_stockResources;
}

void bl::server::game::planet::Planet::addBuilding(const std::shared_ptr<building::IBuilding> &building) {
	this->m_buildings.push_back(building);
	if (std::dynamic_pointer_cast<building::specialities::IResourceProductionBuilding>(building) != nullptr) {
		this->m_resourceProductionBuildings.push_back(building);
	}
}

void bl::server::game::planet::Planet::updateResources() {
	for (auto &building : this->m_resourceProductionBuildings)
		building->updateResource();
}
