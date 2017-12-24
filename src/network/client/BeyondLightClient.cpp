/*
** BeyondLightClient.cpp for BeyondLight in /home/guillaume/delivery/BeyondLight/BeyondLightClient.cpp
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Tue Nov 07 14:43:06 2017 Guillaume Julien
** Last update Tue Nov 07 14:43:06 2017 Guillaume Julien
*/

#include <chrono>
#include "SocketFactory.hh"
#include "BeyondLightClient.hh"
#include "../../client/MainHandler.hh"

bl::network::client::BeyondLightClient::BeyondLightClient(ClientNetworkHandler *handler) : AClientUdp(socket::clientKeyUdpSslAsyncBoostSocket), m_handler(handler) {}

void bl::network::client::BeyondLightClient::mainLoop() {
	this->m_activeThreads.emplace_back(&bl::network::client::BeyondLightClient::readingThread, this);
	this->m_activeThreads.emplace_back(&bl::network::client::BeyondLightClient::sendingThread, this);

	while (this->m_running) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void bl::network::client::BeyondLightClient::disconnect() {
	AClientUdp::disconnect();
	this->m_socket->close();
	for (auto &thread : this->m_activeThreads) {
		thread.join();
	}
	this->m_handler->notifyWatchers(socket::EWatcherType::WATCH_QUIT);
}

void bl::network::client::BeyondLightClient::readingThread() {
	std::string data;
	bool isOpen = true;

	while (isOpen && m_running) {
		try {
			data += this->m_socket->receive();
			while (data.find(newLineDelim) != data.npos) {
				auto line = data.substr(0, data.find(newLineDelim));
				data.erase(0, data.find(newLineDelim) + newLineDelim.length());
				if (line.find(this->msgStartHeader) != line.npos) {
					line = line.substr(line.find(this->msgStartHeader) + this->msgStartHeader.size());
				}
				this->m_lines.push(line);
				this->m_handler->notifyWatchers(socket::EWatcherType::WATCH_READ);
				this->m_handler->notifyWatchers(socket::EWatcherType::WATCH_ALL_WATCHER_READ_DONE);
			}
		} catch (std::exception const &) {
			isOpen = false;
			std::cerr << "Exception in reading thread, quitting" << std::endl;
			this->m_handler->notifyWatchers(socket::EWatcherType::WATCH_QUIT);
			this->m_running = false;
		}
	}
}

void bl::network::client::BeyondLightClient::sendingThread() {
	bool isOpen = true;

	while (isOpen && m_running) {
		try {
			while (!this->m_toSend.empty()) {
				this->m_socket->send(this->m_toSend.front());
				this->m_toSend.pop();
				this->m_handler->notifyWatchers(socket::EWatcherType::WATCH_SEND);
				this->m_handler->notifyWatchers(socket::EWatcherType::WATCH_ALL_WATCHER_SEND_DONE);
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		} catch (std::exception const &) {
			isOpen = false;
			std::cerr << "Exception in sending thread, quitting" << std::endl;
			this->m_handler->notifyWatchers(socket::EWatcherType::WATCH_QUIT);
			this->m_running = false;
		}
	}
}

std::string const &bl::network::client::BeyondLightClient::getLine() const {
	return this->m_lines.front();
}

void bl::network::client::BeyondLightClient::addToSend(std::string const &cmd) {
	this->m_toSend.push(cmd);
}

void bl::network::client::BeyondLightClient::setLineToRead() {
	this->m_lines.pop();
}

std::string bl::network::client::BeyondLightClient::getAndEraseLine() {
	std::string line = this->getLine();
	this->setLineToRead();
	while (line.empty()) {
		line = this->getLine();
		this->setLineToRead();
	}
	return line;
}
