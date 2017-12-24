//
// Created by Guillaume on 02/10/2017.
//

#include <iostream>
#include "TcpBoostAcceptor.hh"
#include "TcpBoostSslSocket.hh"

bl::network::socket::TcpBoostAcceptor::TcpBoostAcceptor(unsigned short port) : m_acceptor(m_ios,
                                                                                      boost::asio::ip::tcp::endpoint(
		                                                                                      boost::asio::ip::tcp::v4(),
		                                                                                      port)) {}

void bl::network::socket::TcpBoostAcceptor::accept(network::socket::ISocket &socket) {
	try {
		m_acceptor.accept(dynamic_cast<TcpBoostSslSocket &>(socket).getBoostSocket());
	} catch (std::bad_cast const& e) {
		std::cerr << "Fatal error: trying to use boost acceptor with non boost socket" << std::endl;
		exit(1); //TODO: add socket exceptions
	}
}
