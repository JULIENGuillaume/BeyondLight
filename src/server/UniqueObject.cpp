//
// Created by Guillaume Julien on 14/12/2017.
//

#include <iostream>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_serialize.hpp>
#include "UniqueObject.hh"

bl::server::UniqueObject::UniqueObject() : m_uuid(boost::uuids::random_generator()()) {}

bl::server::UniqueObject::UniqueObject(const bl::server::UniqueObject &src) : m_uuid(src.m_uuid) {}

boost::uuids::uuid const &bl::server::UniqueObject::getUuid() const {
	return this->m_uuid;
}
