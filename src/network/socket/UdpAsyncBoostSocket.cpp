/*
** UdpAsyncBoostSocket.cpp for BeyondLight in /home/guillaume/delivery/BeyondLight/UdpAsyncBoostSocket.cpp
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Tue Nov 07 14:32:16 2017 Guillaume Julien
** Last update Tue Nov 07 14:32:16 2017 Guillaume Julien
*/

#include <iostream>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <utility>
#include "UdpAsyncBoostSocket.hh"

bl::network::socket::UdpAsyncBoostSocket::UdpAsyncBoostSocket() : m_socket(std::make_shared<boost::asio::ip::udp::socket>(m_ios)) {
}

void bl::network::socket::UdpAsyncBoostSocket::close() {
	m_socket->close();
}

bool bl::network::socket::UdpAsyncBoostSocket::connect(std::string const &address, unsigned short port) {
	try {
		if (m_socket->is_open()) {
			m_socket->close();
		}

		m_socket->open(boost::asio::ip::udp::v4());
		m_targetEndpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(address), port);
		boost::array<char, 1> send_buf = {0};
		m_socket->send_to(boost::asio::buffer(send_buf), m_targetEndpoint);
	} catch (boost::system::system_error &e) {
		std::cerr << "Can't connect: " << e.what() << std::endl;
		return false;
	}
	return true;
}

bool bl::network::socket::UdpAsyncBoostSocket::openConnection(unsigned short port) {
	try {
		if (m_socket->is_open()) {
			m_socket->close();
		}
		m_socket->open(boost::asio::ip::udp::v4());
		m_socket->bind(boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port));
	} catch (boost::system::system_error &e) {
		std::cerr << "Can't open connection: " << e.what() << std::endl;
		return false;
	}
	return true;
}

void bl::network::socket::UdpAsyncBoostSocket::send(char const *msg) {
	m_socket->send_to(boost::asio::buffer(std::string(msg) + "\r\n"), m_targetEndpoint);
}

void bl::network::socket::UdpAsyncBoostSocket::send(std::string const &msg) {
	m_socket->send_to(boost::asio::buffer(msg + "\r\n"), m_targetEndpoint);
}

char *bl::network::socket::UdpAsyncBoostSocket::receive(char *buf, size_t bufSize) {
	auto received = receive();
	std::strncpy(buf, received.data(), bufSize > received.size() ? received.size() : bufSize);
	return buf;
}

std::string bl::network::socket::UdpAsyncBoostSocket::receive() {
	boost::array<char, m_bufferSize> recv_buf{};
	boost::asio::ip::udp::endpoint sender_endpoint;
	m_socket->receive_from(boost::asio::buffer(recv_buf), m_lastSenderEndpoint, 0);
	return std::string(recv_buf.data());
}

void bl::network::socket::UdpAsyncBoostSocket::setAutoDataEncrypt(bool encrypt) {
	m_autoEncrypt = encrypt;
}

void bl::network::socket::UdpAsyncBoostSocket::setAutoDataDecrypt(bool decrypt) {
	m_autoDecrypt = decrypt;
}

std::shared_ptr<bl::network::socket::ISocket> bl::network::socket::UdpAsyncBoostSocket::clone() const {
	std::shared_ptr<ISocket> ret(new UdpAsyncBoostSocket());
	ret->setAutoDataDecrypt(m_autoDecrypt);
	ret->setAutoDataEncrypt(m_autoEncrypt);
	return ret;
}

boost::asio::ip::udp::endpoint bl::network::socket::UdpAsyncBoostSocket::getLastSenderEndpoint() {
	return m_lastSenderEndpoint;
}

void bl::network::socket::UdpAsyncBoostSocket::updateTargetEndpoint(boost::asio::ip::udp::endpoint endpoint) {
	m_targetEndpoint = std::move(endpoint);
}
