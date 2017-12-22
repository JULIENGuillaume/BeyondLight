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
