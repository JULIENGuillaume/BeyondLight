//
// Created by Guillaume Julien on 14/12/2017.
//

#include <iostream>
#include "UniqueObject.hh"

bl::server::UniqueObject::UniqueObject() : m_uuid(boost::uuids::random_generator()()) {}

bl::server::UniqueObject::UniqueObject(const bl::server::UniqueObject &src) : m_uuid(src.m_uuid) {}

boost::uuids::uuid const &bl::server::UniqueObject::getUuid() const {
	return this->m_uuid;
}

nlohmann::json bl::server::UniqueObject::serialize() const {
	nlohmann::json json;

	json["uuid"] = boost::uuids::to_string(this->m_uuid);
	return json;
}

bl::common::pattern::ISerializable *bl::server::UniqueObject::deserialize(nlohmann::json const &json) {
	std::string tmpUuid = json["uuid"];
	this->m_uuid = boost::lexical_cast<boost::uuids::uuid>(tmpUuid);
	return this;
}

std::string bl::server::UniqueObject::getUuidAsString() const {
	return boost::uuids::to_string(this->m_uuid);
}
