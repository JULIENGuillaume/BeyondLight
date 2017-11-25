//
// Created by diguie_t on 11/23/2017.
//

#include <functional>
#include <future>
#include <thread>
#include <iostream>
#include "NetworkHandler.hh"
#include "BeyondLightClient.hh"

network::client::NetworkHandler::NetworkHandler(std::string const &ip, unsigned short port) : m_networkClient(std::make_shared<BeyondLightClient>(this)) {
	if (!m_networkClient->connectTo(ip, port)) {
		throw std::runtime_error("Can't launch network client");
	}
	this->m_privateWatchers.emplace(EWatcherType::WATCH_ALL_WATCHER_READ_DONE, &NetworkHandler::retrieveLine);
	this->m_networkThread = m_networkClient->asyncLaunch();
	//this->addWatcher(EWatcherType::WATCH_ALL_WATCHER_READ_DONE, "Final line retriever", &NetworkHandler::retrieveLine);
}

network::client::NetworkHandler::~NetworkHandler() {
	this->m_networkClient->disconnect();
	this->m_networkThread->join();
}

std::string network::client::NetworkHandler::getLine() {
	while (this->m_lines.empty()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	auto line = this->m_lines.front();
	this->m_lines.pop();
	return line;
}

void network::client::NetworkHandler::send(std::string const &cmd) {
	(std::dynamic_pointer_cast<BeyondLightClient>(this->m_networkClient))->addToSend(cmd);
}

void network::client::NetworkHandler::retrieveLine() {
	auto str = (std::dynamic_pointer_cast<BeyondLightClient>(this->m_networkClient))->getAndEraseLine();
	this->m_lines.push(str);
}

std::future<std::string> network::client::NetworkHandler::asyncGetLine() {
	std::future<std::string> future = std::async(&NetworkHandler::getLine, this);
	return future;
}

void network::client::NetworkHandler::asyncSend(std::string const &cmd) {
	this->send(cmd);
}

void network::client::NetworkHandler::addWatcher(network::client::EWatcherType type, std::string const &name, std::function<void(std::string const &)> fct) {
	this->m_watchers.emplace(type, std::make_pair(name, fct));
}

void network::client::NetworkHandler::notifyWatchers(network::client::EWatcherType type) {
	std::vector<std::thread> threads;
	if (m_watchers.find(type) != m_watchers.end()) {
		for (auto it = m_watchers.equal_range(type).first; it != m_watchers.equal_range(type).second; ++it) {
			threads.emplace_back(it->second.second, it->second.first);
		}
	} else if (m_privateWatchers.find(type) != m_privateWatchers.end()) {
		m_privateWatchers[type](this);
	}
	for (auto &thread : threads) {
		thread.join();
	}
}

