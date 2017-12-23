//
// Created by Guillaume on 23/12/2017.
//

#include <cereal/archives/portable_binary.hpp>
#include <functional>
#include <future>
#include <thread>
#include <iostream>
#include <ClientMessage.hh>
#include "ServerNetworkHandler.hh"
#include "BeyondLightServer.hh"

bl::network::server::ServerNetworkHandler::ServerNetworkHandler(unsigned short port) : m_networkServer(std::make_shared<BeyondLightServer>(port, this)) {
	this->m_networkThread = m_networkServer->asyncRun();
}

std::string bl::network::server::ServerNetworkHandler::getLine() {
	while (this->m_lines.empty()) {
		if (!this->m_networkServer->isRunning()) {
			throw std::runtime_error("Failed to get line: network isn't connected.");
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	auto line = this->m_lines.front();
	this->m_lines.pop();
	return line;
}

bl::network::client::ClientMessage bl::network::server::ServerNetworkHandler::getMessage() {
	auto str = this->getLine();
	std::stringstream ss(str);
	cereal::PortableBinaryInputArchive inArchive(ss);
	client::ClientMessage message;
	inArchive(message);

	return message;
}

void bl::network::server::ServerNetworkHandler::send(std::string const &cmd) {
	(std::dynamic_pointer_cast<BeyondLightServer>(this->m_networkServer))->addToSend(cmd);
}

void bl::network::server::ServerNetworkHandler::send(
	bl::network::server::ServerMessageType type,
	uint64_t code,
	std::string const &msg
) {
	//Create the message structure
	ServerMessage message;
	message.getBody().message = msg;
	message.getBody().messageSize = msg.size();
	message.getBody().code = code;
	message.getBody().type = type;

	//Serialize the message
	std::stringstream ss;
	cereal::PortableBinaryOutputArchive outArchive(ss);
	outArchive(message);
	const std::string &strRepresentation = ss.str(); //TODO: check if working to avoid unnecessary copy
	std::vector<char> fullData(strRepresentation.begin(), strRepresentation.end());
	this->send(std::string(fullData.begin(), fullData.end())); // Copy the data to be send to a string
}

void bl::network::server::ServerNetworkHandler::retrieveLine() {
	auto str = (std::dynamic_pointer_cast<BeyondLightServer>(this->m_networkServer))->getAndEraseLine();
	this->m_lines.push(str);
}