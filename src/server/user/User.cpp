/*
** User.cpp for BeyondLight in /home/guillaume/delivery/BeyondLight/User.cpp
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Thu Nov 09 17:56:28 2017 Guillaume Julien
** Last update Thu Nov 09 17:56:28 2017 Guillaume Julien
*/

#include "User.hh"

nlohmann::json bl::server::user::User::serialize() const {
	nlohmann::json json = UniqueObject::serialize();

	json["login"] = this->m_login;
	json["lastPlanet"] = this->m_lastPlanetId;
	return json;
}

bl::common::pattern::ISerializable *bl::server::user::User::deserialize(nlohmann::json const &json) {
	UniqueObject::deserialize(json);
	this->m_login = json["login"];
	this->m_lastPlanetId = json["lastPlanet"];
	return this;
}

const std::string &bl::server::user::User::getLogin() const {
	return m_login;
}

void bl::server::user::User::setLogin(const std::string &login) {
	m_login = login;
}

const std::string &bl::server::user::User::getLastPlanetId() const {
	return m_lastPlanetId;
}

void bl::server::user::User::setLastPlanetId(const std::string &lastPlanetId) {
	m_lastPlanetId = lastPlanetId;
}

const std::unordered_set<int> &bl::server::user::User::getTechnologies() const {
	return m_technologies;
}

void bl::server::user::User::addTechnology(int techId) {
	this->m_technologies.insert(techId);
}
