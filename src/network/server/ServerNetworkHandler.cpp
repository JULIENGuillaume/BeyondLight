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
#include "../../server/LoadedData.hh"

bl::network::server::ServerNetworkHandler::ServerNetworkHandler(unsigned short port, ::bl::server::LoadedData &data) : m_networkServer(std::make_shared<BeyondLightServer>(port, this, data)),
                                                                                                                       m_data(data) {
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

std::pair<boost::asio::ip::udp::endpoint, std::string> bl::network::server::ServerNetworkHandler::getLineFrom() {
	while (this->m_linesFrom.empty()) {
		if (!this->m_networkServer->isRunning()) {
			throw std::runtime_error("Failed to get line: network isn't connected.");
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	auto line = this->m_linesFrom.front();
	this->m_linesFrom.pop();
	return line;
}

std::pair<boost::asio::ip::udp::endpoint, bl::network::client::ClientMessage> bl::network::server::ServerNetworkHandler::getMessage() {
	auto strFrom = this->getLineFrom();
	auto str = strFrom.second;
	std::stringstream ss(str);
	cereal::PortableBinaryInputArchive inArchive(ss);
	client::ClientMessage message;
	inArchive(message);
	return std::make_pair(strFrom.first, message);
}

void bl::network::server::ServerNetworkHandler::send(std::string const &cmd) {
	std::cerr << "Can't do a classic send here" << std::endl;
}

void bl::network::server::ServerNetworkHandler::send(
	bl::network::server::ServerMessageType type,
	uint64_t code,
	std::string const &msg,
	boost::asio::ip::udp::endpoint const& endpoint
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
	const std::string &strRepresentation = ss.str();
	std::vector<char> fullData(strRepresentation.begin(), strRepresentation.end());
	(std::dynamic_pointer_cast<BeyondLightServer>(this->m_networkServer))->addToSend(std::string(fullData.begin(), fullData.end()), endpoint);
	//this->send(std::string(fullData.begin(), fullData.end())); // Copy the data to be send to a string
}

void bl::network::server::ServerNetworkHandler::retrieveLine() {
	auto str = (std::dynamic_pointer_cast<BeyondLightServer>(this->m_networkServer))->getAndEraseLine();
	this->m_linesFrom.push(str);
}

std::unordered_map<std::string, boost::asio::ip::udp::endpoint>& bl::network::server::ServerNetworkHandler::getListClient() {
	return this->m_networkServer->getClients();
}

void bl::network::server::ServerNetworkHandler::send(const bl::network::server::ServerMessage &msg,
													 boost::asio::ip::udp::endpoint const &endpoint) {
	this->send(msg.getBody().type, msg.getBody().code, msg.getBody().message, endpoint);
}
