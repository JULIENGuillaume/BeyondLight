//
// Created by Guillaume Julien on 14/12/2017.
//

#include "Planet.hh"
#include "../building/IronMine.hh"

bl::server::game::planet::Planet::Planet() : UniqueObject() {
	this->m_buildings.emplace_back(std::make_shared(building::IronMine()));
}

bl::server::game::planet::Planet::Planet(const bl::server::game::planet::Planet &src) : UniqueObject(src), m_buildings(src.m_buildings) {}
