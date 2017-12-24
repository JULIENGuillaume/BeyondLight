/*
** UdpAsyncBoostSocket.hh for BeyondLight in /home/guillaume/delivery/BeyondLight/UdpAsyncBoostSocket.hh
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Tue Nov 07 14:32:16 2017 Guillaume Julien
** Last update Tue Nov 07 14:32:16 2017 Guillaume Julien
*/

#ifndef BEYONDLIGHT_UDPASYNCBOOSTSOCKET_HH
#define BEYONDLIGHT_UDPASYNCBOOSTSOCKET_HH

#include <boost/asio.hpp>
#include "ISocket.hh"

namespace bl {
	namespace network {
		namespace socket {
			class UdpAsyncBoostSocket : public ISocket {
			public:
				explicit UdpAsyncBoostSocket();
				~UdpAsyncBoostSocket() override = default;
			public:
				std::shared_ptr<ISocket> clone() const override;
				bool connect(
						std::string const &address,
						unsigned short port
				) override;
				void send(char const *msg) override;
				void send(std::string const &msg) override;
				void sendTo(std::string const &msg, boost::asio::ip::udp::endpoint const& endpoint);
				void send(std::vector<char> const &msg) override;
				char *receive(
						char *buf,
						size_t bufSize
				) override;
				std::string receive() override;
				void setAutoDataEncrypt(bool encrypt) override;
				void setAutoDataDecrypt(bool decrypt) override;
				bool openConnection(unsigned short port) override;
				boost::asio::ip::udp::endpoint getLastSenderEndpoint();
				void updateTargetEndpoint(boost::asio::ip::udp::endpoint endpoint);
				void close() override;
				void receive(std::vector<char> &buf) override;
			private:
				bool m_connected = false;
				bool m_autoEncrypt = false;
				bool m_autoDecrypt = false;
				boost::asio::io_service m_ios;
				std::shared_ptr<boost::asio::ip::udp::socket> m_socket;
				boost::asio::ip::udp::endpoint m_targetEndpoint;
				boost::asio::ip::udp::endpoint m_lastSenderEndpoint;
			private:
				static const unsigned int m_bufferSize = 8192;
			};
		}
	}
}

#endif //BEYONDLIGHT_UDPASYNCBOOSTSOCKET_HH
