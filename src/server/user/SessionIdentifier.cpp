//
// Created by Guillaume on 28/12/2017.
//

#include "SessionIdentifier.hh"

const bl::server::user::User &bl::server::user::SessionIdentifier::getUser() const {
	return m_user;
}

void bl::server::user::SessionIdentifier::setUser(bl::server::user::User user) {
	m_user = user;
}

const std::string &bl::server::user::SessionIdentifier::getIp() const {
	return m_ip;
}

void bl::server::user::SessionIdentifier::setIp(const std::string &ip) {
	m_ip = ip;
}
