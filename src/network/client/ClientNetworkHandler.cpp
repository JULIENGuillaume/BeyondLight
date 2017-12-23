//
// Created by diguie_t on 11/23/2017.
//

#include <functional>
#include <future>
#include <thread>
#include <iostream>
#include "ClientNetworkHandler.hh"
#include "BeyondLightClient.hh"

bl::network::client::ClientNetworkHandler::ClientNetworkHandler(std::string const &ip, unsigned short port) : m_networkClient(std::make_shared<BeyondLightClient>(this)) {
	if (!m_networkClient->connectTo(ip, port)) {
		throw std::runtime_error("Can't launch network client");
	}
	this->m_networkThread = m_networkClient->asyncLaunch();
}

bl::network::client::ClientNetworkHandler::~ClientNetworkHandler() {
	this->m_networkClient->disconnect();
	this->m_networkThread->join();
}

std::string bl::network::client::ClientNetworkHandler::getLine() {
	while (this->m_lines.empty()) {
		if (!this->m_networkClient->isRunning()) {
			throw std::runtime_error("Failed to get line: network isn't connected.");
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	auto line = this->m_lines.front();
	this->m_lines.pop();
	return line;
}

void bl::network::client::ClientNetworkHandler::send(std::string const &cmd) {
	(std::dynamic_pointer_cast<BeyondLightClient>(this->m_networkClient))->addToSend(cmd);
}

void bl::network::client::ClientNetworkHandler::send(
		bl::network::client::ClientMessageType type,
		uint64_t code,
		std::string const &msg
) {
	//Create the message structure
	ClientMessage message;
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

void bl::network::client::ClientNetworkHandler::retrieveLine() {
	auto str = (std::dynamic_pointer_cast<BeyondLightClient>(this->m_networkClient))->getAndEraseLine();
	this->m_lines.push(str);
}