//
// Created by Guillaume on 29/12/2017.
//

#include "Api.hh"

bl::server::api::Api::Api(bl::server::ServerCore &core) : m_core(core) {}

void bl::server::api::Api::execute(bl::network::client::ClientMessage message) {

}

bl::server::ServerCore &bl::server::api::Api::getCore() {
	return m_core;
}
