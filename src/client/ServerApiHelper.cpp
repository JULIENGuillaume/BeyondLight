//
// Created by Guillaume on 29/12/2017.
//

#include "ServerApiHelper.hh"

bl::client::ServerApiHelper::ServerApiHelper() {
	/*
	 * Request for login / logout procedure (priority request, doesn't go through the api system)
	 */
	this->registerRequest(this->REQUEST_VALIDATE_NETWORK, network::client::CLIENT_MESSAGE_TYPE_REQUEST, server::api::API_TYPE_USER, 0, "");
	this->registerRequest(this->REQUEST_LOGIN, network::client::CLIENT_MESSAGE_TYPE_REQUEST, server::api::API_TYPE_USER, 42, "");
	this->registerRequest(this->REQUEST_REGISTER, network::client::CLIENT_MESSAGE_TYPE_REQUEST, server::api::API_TYPE_USER, 43, "");
	this->registerRequest(this->REQUEST_LOGOUT, network::client::CLIENT_MESSAGE_TYPE_REQUEST, server::api::API_TYPE_USER, 1337, "");

	/*
	 * Info on the current state of buildings / planets
	 */
	this->registerRequest(this->REQUEST_BUILDING_INFO, network::client::CLIENT_MESSAGE_TYPE_REQUEST, server::api::API_TYPE_BUILDING, 4242, "");
	this->registerRequest(this->REQUEST_BUILDING_UPGRADE, network::client::CLIENT_MESSAGE_TYPE_REQUEST, server::api::API_TYPE_BUILDING, 421356, "");
	this->registerRequest(this->REQUEST_CURRENT_RESOURCES, network::client::CLIENT_MESSAGE_TYPE_REQUEST, server::api::API_TYPE_PLANET, 3242, "");

	/*
	 * Info on technologies
	 */
	this->registerRequest(this->REQUEST_TECHNOLOGY_INFO, network::client::CLIENT_MESSAGE_TYPE_REQUEST, server::api::API_TYPE_TECHNOLOGY, 154, "");
}

bl::network::client::ClientMessage bl::client::ServerApiHelper::buildNewApiRequest(std::string const &requestName) {
	std::cout << "Looking for [" << requestName << "]" << std::endl;
	if (this->m_requestModel.find(requestName) == this->m_requestModel.end())
		return bl::network::client::ClientMessage();
	std::cout << "Found" << std::endl;
	return this->m_requestModel.find(requestName)->second;
}

bl::network::client::ClientMessage bl::client::ServerApiHelper::buildNewApiRequest(std::string const &requestName, std::string const &arg) {
	auto baseRequest = buildNewApiRequest(requestName);
	if (baseRequest.getBody().msgType == network::client::CLIENT_MESSAGE_TYPE_NONE)
		return baseRequest;
	baseRequest.getBody().message += "?" + arg;
	return baseRequest;
}

bl::network::client::ClientMessage bl::client::ServerApiHelper::buildNewApiRequest(std::string const &requestName, std::vector<std::string> const &args) {
	std::string finalArg;
	for (size_t i = 0; i < args.size(); ++i) {
		if (i != 0) {
			finalArg += "&";
		}
		finalArg += args[i];
	}
	return buildNewApiRequest(requestName, finalArg);
}

bl::network::client::ClientMessage bl::client::ServerApiHelper::buildNewApiRequest(std::string const &requestName, std::unordered_map<std::string, std::string> const &args) {
	std::vector<std::string> finalArgs;
	finalArgs.reserve(args.size());
	for (auto arg : args)
		finalArgs.push_back(arg.first + "=" + arg.second);
	return buildNewApiRequest(requestName, finalArgs);
}

void bl::client::ServerApiHelper::registerRequest(std::string const &requestName, network::client::ClientMessageType type, server::api::EApiType requestType, uint64_t code, std::string const &message) {
	bl::network::client::ClientMessage request;
	request.getBody().message = message;
	request.getBody().code = code;
	request.getBody().msgType = type;
	request.getBody().apiType = requestType;
	this->m_requestModel.emplace(requestName, request);
}
