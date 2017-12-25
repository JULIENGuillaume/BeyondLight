//
// Created by Guillaume on 25/12/2017.
//

#ifndef BEYONDLIGHT_LOGGINGHELPER_HH
#define BEYONDLIGHT_LOGGINGHELPER_HH

#include <memory>
#include <TcpBoostSslSocket.hh>

namespace bl {
	namespace server {
		class LoggingHelper {
		public:
			explicit LoggingHelper(const std::shared_ptr<network::socket::TcpBoostSslSocket> &m_socket);
			bool executeCommand(std::string const& cmd);

		private:
			std::shared_ptr<network::socket::TcpBoostSslSocket> m_socket;
		};
	}
}


#endif //BEYONDLIGHT_LOGGINGHELPER_HH
