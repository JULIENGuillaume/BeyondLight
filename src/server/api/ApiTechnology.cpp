//
// Created by Guillaume on 29/12/2017.
//

#include "../ServerCore.hh"
#include "ApiTechnology.hh"
#include "Api.hh"

bl::server::api::ApiTechnology::ApiTechnology(bl::server::api::Api &basicApi) : basicApi(basicApi) {}

bl::network::server::ServerMessage  bl::server::api::ApiTechnology::execute(bl::network::client::ClientMessage &message) {
	return bl::network::server::ServerMessage{};
}
