//
// Created by Guillaume Julien on 14/12/2017.
//

#include <boost/uuid/uuid_io.hpp>
#include "Planet.hh"
#include "../building/IronMine.hh"
#include "../building/CrystalExtractor.hh"

bl::server::game::planet::Planet::Planet() :
		UniqueObject() {
	this->addBuilding(std::shared_ptr<building::IBuilding>(new building::IronMine(*this)));
	this->addBuilding(std::shared_ptr<building::IBuilding>(new building::CrystalExtractor(*this)));
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
		this->m_resourceProductionBuildings.push_back(std::dynamic_pointer_cast<building::specialities::IResourceProductionBuilding>(building));
	}
}

bool bl::server::game::planet::Planet::tryToUpdateBuilding(int id) {
	this->updateResources();
	for (const auto& building : this->m_buildings) {
		if (building->getId() == id)
			return building->upgrade();
	}
	return false;
}

void bl::server::game::planet::Planet::updateResources() {
	for (auto &building : this->m_resourceProductionBuildings)
		building->updateResource();
}

nlohmann::json bl::server::game::planet::Planet::serialize() const {
	nlohmann::json json;
	std::vector<nlohmann::json> buildings;

	for (const auto &ptrBuild : this->m_buildings) {
		buildings.emplace_back(ptrBuild->serialize());
	}
	json["buildings"] = buildings;
	json["resources"] = this->m_stockResources.serialize();
	return json;
}

bl::common::pattern::ISerializable *bl::server::game::planet::Planet::deserialize(nlohmann::json const &json) {
	std::vector<nlohmann::json> buildings = json["buildings"];

	for (const auto& build : buildings) {
		std::shared_ptr<building::IBuilding> newBuild{};
		newBuild->deserialize(build);
		this->m_buildings.push_back(newBuild);
	}
	this->m_stockResources.deserialize(json["resources"]);
	return nullptr;
}

const std::shared_ptr<bl::server::game::building::IBuilding> &bl::server::game::planet::Planet::getBuildingInfo(int id) const {
	for (const auto& building : this->m_buildings) {
		if (building->getId() == id)
			return building;
	}
	throw std::runtime_error("Can't locate any building with id " + std::to_string(id) + " on planet " + boost::uuids::to_string(this->m_uuid));
}
