//
// Created by Guillaume Julien on 14/12/2017.
//

#include <time.h>
#include <boost/uuid/uuid_io.hpp>
#include <iostream>
#include "Planet.hh"
#include "../building/IronMine.hh"
#include "../building/CrystalExtractor.hh"
#include "../building/ResearchCenter.hh"

bl::server::game::planet::Planet::Planet() :
		UniqueObject() {
	this->resetBuildings();
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
	this->m_idToBuildings.emplace(building->getId(), building);
	if (std::dynamic_pointer_cast<building::specialities::IResourceProductionBuilding>(building) != nullptr) {
		this->m_resourceProductionBuildings.push_back(std::dynamic_pointer_cast<building::specialities::IResourceProductionBuilding>(building));
	}
}

bool bl::server::game::planet::Planet::tryToUpdateBuilding(int id) {
	std::cout << "Updating resources" << std::endl;
	this->updateResources();
	std::cout << "Searching for building " << id << std::endl;
	if (this->m_idToBuildings.find(id) != this->m_idToBuildings.end()) {
		std::cout << "Launching upgrade !" << std::endl;
		return this->m_idToBuildings[id]->upgrade();
	}
	std::cout << "Not found" << std::endl;
	return false;
}

void bl::server::game::planet::Planet::updateResources() {
	for (auto &building : this->m_resourceProductionBuildings)
		building->updateResource();
}

nlohmann::json bl::server::game::planet::Planet::serialize() const {
	nlohmann::json json = UniqueObject::serialize();
	std::vector<nlohmann::json> buildings;

	for (const auto &ptrBuild : this->m_buildings) {
		buildings.emplace_back(ptrBuild->serialize());
	}
	json["buildings"] = buildings;
	json["resources"] = this->m_stockResources.serialize();
	json["owner"] = this->m_planetOwner;
	return json;
}

bl::common::pattern::ISerializable *bl::server::game::planet::Planet::deserialize(nlohmann::json const &json) {
	try {
		UniqueObject::deserialize(json);
		this->m_stockResources.deserialize(json["resources"]);
		this->m_planetOwner = json["owner"];

		this->resetBuildings();
		std::vector<nlohmann::json> buildings = json["buildings"];
		for (const auto& build : buildings) {
			m_idToBuildings[build["id"]]->deserialize(build);
		}
	} catch (std::exception const& e) {
		std::cerr << e.what() << std::endl;
	}

	return this;
}

const std::shared_ptr<bl::server::game::building::IBuilding> &bl::server::game::planet::Planet::getBuildingInfo(int id) const {
	for (const auto& building : this->m_buildings) {
		if (building->getId() == id)
			return building;
	}
	throw std::runtime_error("Can't locate any building with id " + std::to_string(id) + " on planet " + boost::uuids::to_string(this->m_uuid));
}

void bl::server::game::planet::Planet::resetBuildings() {
	this->m_buildings.clear();
	this->m_resourceProductionBuildings.clear();
	this->m_idToBuildings.clear();
	this->addBuilding(std::shared_ptr<building::IBuilding>(new building::IronMine(*this)));
	this->addBuilding(std::shared_ptr<building::IBuilding>(new building::CrystalExtractor(*this)));
	this->addBuilding(std::shared_ptr<building::IBuilding>(new building::ResearchCenter(*this)));
}

bool bl::server::game::planet::Planet::claimBy(const bl::server::user::User &claimer) {
	this->m_planetOwner = claimer.getUuidAsString();
	return true;
}

const std::string &bl::server::game::planet::Planet::getPlanetOwner() const {
	return m_planetOwner;
}
