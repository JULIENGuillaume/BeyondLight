//
// Created by Guillaume Julien on 20/12/2017.
//

#include "ClientMessage.hh"

const bl::network::client::ClientMessageBody &bl::network::client::ClientMessage::getBody() const {
	return this->m_body;
}

bl::network::client::ClientMessageBody &bl::network::client::ClientMessage::getBody() {
	return this->m_body;
}

std::ostream& operator<<(std::ostream& os, const bl::network::client::ClientMessage& dt)
{
	os << dt.getBody();
	return os;
}

std::ostream& operator<<(std::ostream& os, const bl::network::client::ClientMessageBody& dt)
{
	os << "{TYPE:" << static_cast<int>(dt.msgType) << "|CODE:" << dt.code << "|MESSAGE:[" << dt.message << "]}";
	return os;
}

std::string bl::network::client::ClientMessage::serialize() {
	std::stringstream ss;
	cereal::PortableBinaryOutputArchive outArchive(ss);
	outArchive(*this);
	return ss.str();
}

void bl::network::client::ClientMessage::deserialize(std::string const &s) {
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