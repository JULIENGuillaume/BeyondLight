//
// Created by Guillaume Julien on 22/12/2017.
//

#include "ANetworkHandler.hh"

bl::network::socket::ANetworkHandler::ANetworkHandler() {
	this->m_privateWatchers.emplace(socket::EWatcherType::WATCH_ALL_WATCHER_READ_DONE, &socket::ANetworkHandler::retrieveLine);
}

std::future<std::string> bl::network::socket::ANetworkHandler::asyncGetLine() {
	std::future<std::string> future = std::async(&ANetworkHandler::getLine, this);
	return future;
}

void bl::network::socket::ANetworkHandler::asyncSend(std::string const &cmd) {
	this->send(cmd);
}

void bl::network::socket::ANetworkHandler::addWatcher(bl::network::socket::EWatcherType type, std::string const &name, std::function<void(std::string const &)> fct) {
	this->m_watchers.emplace(type, std::make_pair(name, fct));
}

void bl::network::socket::ANetworkHandler::notifyWatchers(bl::network::socket::EWatcherType type) {
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