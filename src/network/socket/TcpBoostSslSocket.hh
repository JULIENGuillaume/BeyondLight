/*
** TcpBoostSslSocket.hh for KeyLogger in /home/guillaume/delivery/KeyLogger/TcpBoostSslSocket.hh
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Thu Nov 02 15:28:38 2017 Guillaume Julien
** Last update Thu Nov 02 15:28:38 2017 Guillaume Julien
*/

#ifndef KEYLOGGER_TCPBOOSTSSLSOCKET_HH
#define KEYLOGGER_TCPBOOSTSSLSOCKET_HH


#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "ISocket.hh"

namespace bl {
	namespace network {
		namespace socket {
			class TcpBoostSslSocket : public ISocket {
			public:
				explicit TcpBoostSslSocket(bool isClient);
				~TcpBoostSslSocket() override = default;

			public:
				bool connect(std::string const &address, unsigned short port) override;

			public:
				void send(char const *msg) override;
				void send(std::string const &msg) override;
				void directSend(std::string const& msg);

			public:
				char *receive(char *buf, size_t b) override;
				std::string receive() override;

			public:
				boost::asio::ip::tcp::socket &getBoostSocket();
				std::shared_ptr<ISocket> clone() const override;

			public:
				void handshake();
				void setAutoDataEncrypt(bool encrypt) override;
				void setAutoDataDecrypt(bool decrypt) override;
				bool openConnection(unsigned short port) override;
				void close() override;
				void send(std::vector<char> const &msg) override;
				void receive(std::vector<char> &buf) override;
				boost::asio::ip::tcp::endpoint getRemoteEndpoint();

			protected:
				bool verify_certificate(bool preverified,
				                        boost::asio::ssl::verify_context &ctx);
				std::string getPassword() const;

			private:
				bool m_connected = false;
				bool m_isClient;
				bool m_autoEncrypt = false;
				bool m_autoDecrypt = false;
				boost::asio::io_service m_ios;
				boost::asio::ssl::context m_sslCtx = boost::asio::ssl::context(boost::asio::ssl::context::sslv23);
				std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> m_socket;
				static const unsigned int m_bufferSize = 8192;
			};
		}
	}
}

#endif //KEYLOGGER_TCPBOOSTSSLSOCKET_HH
