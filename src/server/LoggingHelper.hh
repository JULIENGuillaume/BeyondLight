//
// Created by Guillaume on 25/12/2017.
//

#ifndef BEYONDLIGHT_LOGGINGHELPER_HH
#define BEYONDLIGHT_LOGGINGHELPER_HH

#include <memory>
#include <TcpBoostSslSocket.hh>
#include "storage/Database.hh"
#include "LoadedData.hh"

namespace bl {
	namespace server {
		class LoggingHelper {
		public:
			explicit LoggingHelper(const std::shared_ptr<bl::network::socket::TcpBoostSslSocket> &m_socket, ::bl::server::LoadedData &data);
			bool executeCommand(std::string const& cmd);

		private:
			network::server::ServerMessage registerNewUser(std::vector<std::string> const& toks);
			network::server::ServerMessage loginUser(std::vector<std::string> const& toks);

		private:
			std::shared_ptr<network::socket::TcpBoostSslSocket> m_socket;
			bl::server::storage::Database m_db;
			::bl::server::LoadedData &m_data;

		private:
			const size_t m_saltSize = 512;
		};
	}
}


#endif //BEYONDLIGHT_LOGGINGHELPER_HH
