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

server::user::User::User(unsigned long id, const std::string &login) : m_id(id), m_login(login) {}

unsigned long int server::user::User::getId() const {
    return m_id;
}

std::string server::user::User::getLogin() const {
    return m_login;
}

std::string server::user::User::getFirstName() const {
    return m_firstName;
}

std::string server::user::User::getLastName() const {
    return m_lastName;
}

std::string server::user::User::getEmail() const {
    return m_email;
}

std::string server::user::User::getPassword() const {
    return m_password;
}
