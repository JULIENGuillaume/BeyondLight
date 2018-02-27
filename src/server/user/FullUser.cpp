//
// Created by Guillaume on 28/12/2017.
//

#include <iostream>
#include "FullUser.hh"

nlohmann::json bl::server::user::FullUser::serialize() const {
	nlohmann::json json = User::serialize();

	std::cout << "Full user serialization" << std::endl;
	json["lastName"] = this->m_lastname;
	json["firstName"] = this->m_firstname;
	json["email"] = this->m_email;
	json["password"] = this->m_password;
	json["salt"] = this->m_salt;
	return json;
}

bl::common::pattern::ISerializable *bl::server::user::FullUser::deserialize(nlohmann::json const &json) {
	User::deserialize(json);

	this->m_lastname = json["lastName"];
	this->m_firstname = json["firstName"];
	this->m_email = json["email"];
	this->m_password = json["password"];
	this->m_salt = json["salt"];
	return this;
}

void bl::server::user::FullUser::setLastname(const std::string &name) {
	m_lastname = name;
}

void bl::server::user::FullUser::setFirstname(const std::string &forename) {
	m_firstname = forename;
}

void bl::server::user::FullUser::setEmail(const std::string &email) {
	m_email = email;
}

void bl::server::user::FullUser::setPassword(const std::string &password) {
	m_password = password;
}

void bl::server::user::FullUser::setSalt(const std::string &salt) {
	m_salt = salt;
}

const std::string &bl::server::user::FullUser::getLastame() const {
	return m_lastname;
}

const std::string &bl::server::user::FullUser::getFirstname() const {
	return m_firstname;
}

const std::string &bl::server::user::FullUser::getEmail() const {
	return m_email;
}

const std::string &bl::server::user::FullUser::getPassword() const {
	return m_password;
}

const std::string &bl::server::user::FullUser::getSalt() const {
	return m_salt;
}
