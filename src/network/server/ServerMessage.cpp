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
	os << "{TYPE:" << static_cast<int32_t>(dt.type) << "|CODE:" << dt.code << "|MESSAGE:[" << dt.message << "]}";
	return os;
}

std::string bl::network::server::ServerMessage::serialize() {
	std::stringstream ss;
	cereal::PortableBinaryOutputArchive outArchive(ss);
	outArchive(*this);
	return ss.str();
}

void bl::network::server::ServerMessage::deserialize(std::string const &s) {
	std::stringstream ss(s);
	cereal::PortableBinaryInputArchive inArchive(ss);
	inArchive(*this);
}

/*
 *

				std::string serialize() {
					std::stringstream ss;
					cereal::PortableBinaryOutputArchive outArchive(ss);
					outArchive(*this);
					return ss.str();
				}

				void deserialize(std::string const& s) {
					std::stringstream ss(s);
					cereal::PortableBinaryInputArchive inArchive(ss);
					inArchive(*this);
				}
 */