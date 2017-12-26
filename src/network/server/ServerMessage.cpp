//
// Created by Guillaume Julien on 20/12/2017.
//

#include "ServerMessage.hh"

const bl::network::server::ServerMessageBody &bl::network::server::ServerMessage::getBody() const {
	return m_body;
}

bl::network::server::ServerMessageBody &bl::network::server::ServerMessage::getBody() {
	return m_body;
}

std::ostream& operator<<(std::ostream& os, const bl::network::server::ServerMessage& dt)
{
	os << dt.getBody();
	return os;
}

std::ostream& operator<<(std::ostream& os, const bl::network::server::ServerMessageBody& dt)
{
	os << "{TYPE:" << dt.type << "|CODE:" << dt.code << "|MESSAGE:[" << dt.message << "]}";
	return os;
}  