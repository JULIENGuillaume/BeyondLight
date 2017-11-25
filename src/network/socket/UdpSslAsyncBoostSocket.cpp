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
#include "UdpSslAsyncBoostSocket.hh"

network::socket::UdpSslAsyncBoostSocket::UdpSslAsyncBoostSocket() : m_socket(std::make_shared<boost::asio::ip::udp::socket>(m_ios)) {
}

void network::socket::UdpSslAsyncBoostSocket::close() {
	m_socket->close();
}

bool network::socket::UdpSslAsyncBoostSocket::connect(std::string const &address, unsigned short port) {
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

bool network::socket::UdpSslAsyncBoostSocket::openConnection(unsigned short port) {
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

void network::socket::UdpSslAsyncBoostSocket::send(char const *msg) {
	m_socket->send_to(boost::asio::buffer(std::string(msg) + "\r\n"), m_targetEndpoint);
}

void network::socket::UdpSslAsyncBoostSocket::send(std::string const &msg) {
	m_socket->send_to(boost::asio::buffer(msg + "\r\n"), m_targetEndpoint);
}

char *network::socket::UdpSslAsyncBoostSocket::receive(char *buf, size_t bufSize) {
	auto received = receive();
	std::strncpy(buf, received.data(), bufSize > received.size() ? received.size() : bufSize);
	return buf;
}

std::string network::socket::UdpSslAsyncBoostSocket::receive() {
	boost::array<char, m_bufferSize> recv_buf{};
	boost::asio::ip::udp::endpoint sender_endpoint;
	m_socket->receive_from(boost::asio::buffer(recv_buf), m_lastSenderEndpoint, 0);
	return std::string(recv_buf.data());
}

void network::socket::UdpSslAsyncBoostSocket::setAutoDataEncrypt(bool encrypt) {
	m_autoEncrypt = encrypt;
}

void network::socket::UdpSslAsyncBoostSocket::setAutoDataDecrypt(bool decrypt) {
	m_autoDecrypt = decrypt;
}

std::shared_ptr<network::socket::ISocket> network::socket::UdpSslAsyncBoostSocket::clone() const {
	std::shared_ptr<ISocket> ret(new UdpSslAsyncBoostSocket());
	ret->setAutoDataDecrypt(m_autoDecrypt);
	ret->setAutoDataEncrypt(m_autoEncrypt);
	return ret;
}

boost::asio::ip::udp::endpoint network::socket::UdpSslAsyncBoostSocket::getLastSenderEndpoint() {
	return m_lastSenderEndpoint;
}

void network::socket::UdpSslAsyncBoostSocket::updateTargetEndpoint(boost::asio::ip::udp::endpoint endpoint) {
	m_targetEndpoint = std::move(endpoint);
}
