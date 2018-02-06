//
// Created by Guillaume on 28/12/2017.
//

#include <boost/asio/ip/udp.hpp>
#include "SessionIdentifier.hh"

const bl::server::user::User &bl::server::user::SessionIdentifier::getUser() const {
	return *m_user;
}

bl::server::user::User &bl::server::user::SessionIdentifier::getUser() {
	return *m_user;
}

void bl::server::user::SessionIdentifier::setUser(std::shared_ptr<User> user) {
	m_user = user;
}

const std::string &bl::server::user::SessionIdentifier::getIp() const {
	return m_ip;
}

void bl::server::user::SessionIdentifier::setIp(const std::string &ip) {
	m_ip = ip;
}

const boost::asio::ip::udp::endpoint &bl::server::user::SessionIdentifier::getEndpoint() const {
	return m_endpoint;
}

void bl::server::user::SessionIdentifier::setEndpoint(const boost::asio::ip::udp::endpoint &endpoint) {
	this->m_endpoint = endpoint;
}
