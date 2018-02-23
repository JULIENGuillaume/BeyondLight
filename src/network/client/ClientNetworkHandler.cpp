//
// Created by diguie_t on 11/23/2017.
//

#include <functional>
#include <future>
#include <iostream>
#include <chrono>
#include "ClientNetworkHandler.hh"
#include "BeyondLightClient.hh"

bl::network::client::ClientNetworkHandler::ClientNetworkHandler(
		std::string const &ip,
		unsigned short port
) :
		m_networkClient(std::make_shared<BeyondLightClient>(this)),
		m_apiHelper(new bl::client::ServerApiHelper),
		m_destIp(ip),
		m_destPort(port) {
	std::cerr << "Creating network handler" << std::endl;
	/*if (!m_networkClient->connectTo(ip, port)) {
		throw std::runtime_error("Can't launch network client");
	}
	this->m_networkThread = m_networkClient->asyncLaunch();*/
}

bl::network::client::ClientNetworkHandler::~ClientNetworkHandler() {
	std::cerr << "Destroying network handler" << std::endl;
	if (m_connected) {
		try {
			this->directSend(ClientMessageType::CLIENT_MESSAGE_TYPE_REQUEST, 1337, "");
			this->m_networkClient->disconnect();
			this->m_networkThread->join();
		} catch (...) {
		}
	}
}

bool bl::network::client::ClientNetworkHandler::tryToConnect() {
	std::cerr << "Trying to connect to " << m_destIp << ":" << m_destPort << std::endl;
	m_connected = m_networkClient->connectTo(m_destIp, m_destPort);
	this->m_networkThread = m_networkClient->asyncLaunch();
	std::cerr << "Connected" << std::endl;
	return m_connected;
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

bl::network::server::ServerMessage bl::network::client::ClientNetworkHandler::getMessage() {
	auto futureMsg = this->asyncGetMessage();
	using namespace std::chrono_literals;
	futureMsg.wait_for(1s);
	return futureMsg.get();
}

void bl::network::client::ClientNetworkHandler::send(std::string const &cmd) {
	std::cout << "Send [" << cmd << "] (" << cmd.size() << ")" << std::endl;
	/*for (int i = 0; i < cmd.size(); i++) {
		std::cout << (int)cmd[i] << std::endl;
	}*/
	(std::dynamic_pointer_cast<BeyondLightClient>(this->m_networkClient))->addToSend(cmd);
}

void bl::network::client::ClientNetworkHandler::send(
		bl::network::client::ClientMessageType type,
		bl::server::api::EApiType apiRequestType,
		uint64_t code,
		std::string const &msg
) {
	//Create the message structure
	ClientMessage message;
	message.getBody().message = msg;
	message.getBody().sessionId = this->m_sessionId;
	message.getBody().messageSize = msg.size();
	message.getBody().code = code;
	message.getBody().msgType = type;
	message.getBody().apiType = apiRequestType;
	
	std::cout << "Sending " << message << std::endl;

	//Serialize the message
	/*std::stringstream ss;
	cereal::JSONOutputArchive outArchive(ss);
	outArchive(message);
	const std::string &strRepresentation = ss.str();
	std::vector<char> fullData(strRepresentation.begin(), strRepresentation.end());
	this->send(std::string(fullData.begin(), fullData.end()));*/ // Copy the data to be send to a string
	this->send(message.serialize());
}

void bl::network::client::ClientNetworkHandler::send(const bl::network::client::ClientMessage &msg) {
	this->send(msg.getBody().msgType, msg.getBody().apiType, msg.getBody().code, msg.getBody().message);
}

void bl::network::client::ClientNetworkHandler::directSend(std::string const &cmd) {
	if (m_connected) {
		(std::dynamic_pointer_cast<BeyondLightClient>(this->m_networkClient))->directSend(cmd);
	}
}

void bl::network::client::ClientNetworkHandler::directSend(
		bl::network::client::ClientMessageType type,
		uint64_t code,
		std::string const &msg
) {
	if (!m_connected) {
		return;
	}
	ClientMessage message;
	message.getBody().message = msg;
	message.getBody().sessionId = this->m_sessionId;
	message.getBody().messageSize = msg.size();
	message.getBody().code = code;
	message.getBody().msgType = type;

	//Serialize the message
	/*std::stringstream ss;
	cereal::JSONOutputArchive outArchive(ss);
	outArchive(message);
	const std::string &strRepresentation = ss.str();
	std::vector<char> fullData(strRepresentation.begin(), strRepresentation.end());
	this->directSend(std::string(fullData.begin(), fullData.end()));*/
	this->directSend(message.serialize());
}

void bl::network::client::ClientNetworkHandler::retrieveLine() {
	auto str = (std::dynamic_pointer_cast<BeyondLightClient>(this->m_networkClient))->getAndEraseLine();
	this->m_lines.push(str);
}

void bl::network::client::ClientNetworkHandler::swapToUdp(unsigned short port) {
	try {
		this->m_networkClient->disconnect();
	} catch (std::exception const &e) {
		std::cerr << "Disconnect failed: " << e.what() << std::endl;
	}
	this->m_networkThread->join();
	this->m_networkThread = std::dynamic_pointer_cast<AClientTcpUdp>(this->m_networkClient)->switchToUdp(this->m_networkClient->getConnectedServer(), port);
}

void bl::network::client::ClientNetworkHandler::setSessionId(std::string const &sessionId) {
	this->m_sessionId = sessionId;
}

const std::shared_ptr<bl::client::ServerApiHelper> &bl::network::client::ClientNetworkHandler::getApiHelper() const {
	return m_apiHelper;
}

std::future<bl::network::server::ServerMessage> bl::network::client::ClientNetworkHandler::asyncGetMessage() {
	return std::async(&bl::network::client::ClientNetworkHandler::syncGetMessage, this);
}

bl::network::server::ServerMessage bl::network::client::ClientNetworkHandler::syncGetMessage() {
	auto str = this->getLine();
	server::ServerMessage message;
	message.deserialize(str);
	return message;
}
