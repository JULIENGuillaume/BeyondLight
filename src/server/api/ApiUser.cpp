//
// Created by Guillaume on 29/12/2017.
//

#include "../ServerCore.hh"
#include "ApiUser.hh"
#include "Api.hh"

bl::server::api::ApiUser::ApiUser(bl::server::api::Api &basicApi) : basicApi(basicApi) {}

bl::network::server::ServerMessage  bl::server::api::ApiUser::execute(bl::network::client::ClientMessage &message) {
	return bl::network::server::ServerMessage{};
}
