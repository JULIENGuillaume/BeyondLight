//
// Created by Guillaume Julien on 22/02/2018.
//

#include <iostream>
#include "Chat.hh"

void bl::server::game::user::Chat::addMsg(
		std::string const &user,
		std::string const &msg
) {
	this->m_messages.emplace_back(user, msg);
	std::cout << "Messages are: " << std::endl;
	for (auto const& s : m_messages) {
		std::cout << "\t-" << s.first << ": " << s.second << std::endl;
	}
}

std::vector<std::pair<std::string, std::string>> bl::server::game::user::Chat::getNLastMessages(uint32_t nbMsg) {
	if (this->m_messages.size() <= nbMsg)
		return this->m_messages;
	return std::vector<std::pair<std::string, std::string>>(this->m_messages.end() - nbMsg, this->m_messages.end());
}
