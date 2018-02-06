//
// Created by Guillaume on 29/12/2017.
//

#include "../ServerCore.hh"
#include "ApiPlanet.hh"
#include "Api.hh"

bl::server::api::ApiPlanet::ApiPlanet(bl::server::api::Api &basicApi) : basicApi(basicApi) {}

bl::network::server::ServerMessage  bl::server::api::ApiPlanet::execute(bl::network::client::ClientMessage &message) {
	return bl::network::server::ServerMessage{};
}
