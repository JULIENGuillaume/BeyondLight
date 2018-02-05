//
// Created by Guillaume Julien on 05/02/2018.
//

#include "IdentifiableCapacity.hh"

int bl::server::game::decorator::IdentifiableCapacity::getId() const {
	return m_id;
}

void bl::server::game::decorator::IdentifiableCapacity::setId(int id) {
	m_id = id;
}

const std::string &bl::server::game::decorator::IdentifiableCapacity::getName() const {
	return m_name;
}

void bl::server::game::decorator::IdentifiableCapacity::setName(const std::string &name) {
	m_name = name;
}

const std::string &bl::server::game::decorator::IdentifiableCapacity::getDescription() const {
	return m_description;
}

void bl::server::game::decorator::IdentifiableCapacity::setDescription(const std::string &description) {
	m_description = description;
}

nlohmann::json bl::server::game::decorator::IdentifiableCapacity::serialize() const {
	nlohmann::json json;

	json["name"] = m_name;
	json["description"] = m_description;
	json["id"] = m_id;
	return json;
}

bl::common::pattern::ISerializable *bl::server::game::decorator::IdentifiableCapacity::deserialize(nlohmann::json const &json) {
	m_id = json["id"];
	m_name = json["name"];
	m_description = json["description"];
	return this;
}

bl::server::game::decorator::IdentifiableCapacity::IdentifiableCapacity(
		int id,
		const std::string &name,
		const std::string &description
) :
		m_id(id),
		m_name(name),
		m_description(description) {

}
