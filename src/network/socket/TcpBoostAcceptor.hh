//
// Created by Guillaume on 02/10/2017.
//

#ifndef KEYLOGGER_TCPBOOSTACCEPTOR_HH
#define KEYLOGGER_TCPBOOSTACCEPTOR_HH

#include <boost/asio.hpp>
#include "IAcceptor.hh"

namespace bl {
	namespace network {
		namespace socket {
			class TcpBoostAcceptor : public IAcceptor {
			public:
				explicit TcpBoostAcceptor(unsigned short port);
				~TcpBoostAcceptor() override = default;

			public:
				void accept(ISocket &socket) override;

			private:
				boost::asio::io_service m_ios;
				boost::asio::ip::tcp::acceptor m_acceptor;
			};
		}
	}
}

#endif //KEYLOGGER_TCPBOOSTACCEPTOR_HH
