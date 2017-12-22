//
// Created by Guillaume Julien on 20/12/2017.
//

#include "ServerMessage.hh"

const bl::network::server::ServerMessageBody &bl::network::server::ServerMessage::getBody() const {
	return m_body;
}
