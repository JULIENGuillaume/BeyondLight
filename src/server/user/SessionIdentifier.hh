//
// Created by Guillaume on 28/12/2017.
//

#ifndef BEYONDLIGHT_SESSIONIDENTIFIER_HH
#define BEYONDLIGHT_SESSIONIDENTIFIER_HH

#include <boost/asio.hpp>
#include "../UniqueObject.hh"
#include "User.hh"

namespace bl {
	namespace server {
		namespace user {
			class SessionIdentifier : public UniqueObject {
			public:
				const User &getUser() const;
				User &getUser();
				void setUser(std::shared_ptr<User> user);
				const std::string &getIp() const;
				void setIp(const std::string &ip);
				const boost::asio::ip::udp::endpoint &getEndpoint() const;
				void setEndpoint(const boost::asio::ip::udp::endpoint &endpoint);
			private:
				std::shared_ptr<User> m_user;
				std::string m_ip;
				boost::asio::ip::udp::endpoint m_endpoint;
			};
		}
	}
}


#endif //BEYONDLIGHT_SESSIONIDENTIFIER_HH
