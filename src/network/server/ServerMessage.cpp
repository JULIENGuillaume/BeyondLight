//
// Created by Guillaume Julien on 20/12/2017.
//

#include "ServerMessage.hh"
#include "../../common/Toolbox.hh"

std::pair<size_t, char*> bl::network::server::ServerMessage::getBinaryData() {
	size_t size = sizeof(ServerMessageBody) + this->m_body.messageSize;
	return std::make_pair(size, common::Toolbox::forceCast<ServerMessageBody *, char *>(&this->m_body));
}

bl::common::pattern::IBinarizable *bl::network::server::ServerMessage::loadFromBinaryData(std::pair<size_t, char*> const &data) {
	this->m_body = *(common::Toolbox::forceCast<char *, ServerMessageBody *>(data.second));
	return this;
}
