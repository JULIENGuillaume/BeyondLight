//
// Created by Guillaume on 28/12/2017.
//

#ifndef BEYONDLIGHT_SESSIONIDENTIFIER_HH
#define BEYONDLIGHT_SESSIONIDENTIFIER_HH

#include "../UniqueObject.hh"
#include "User.hh"

namespace bl {
	namespace server {
		namespace user {
			class SessionIdentifier : public UniqueObject {
			public:
				const User &getUser() const;
				void setUser(std::shared_ptr<User> user);
				const std::string &getIp() const;
				void setIp(const std::string &ip);
			private:
				std::shared_ptr<User> m_user;
				std::string m_ip;
			};
		}
	}
}


#endif //BEYONDLIGHT_SESSIONIDENTIFIER_HH
