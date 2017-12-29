//
// Created by Guillaume on 28/12/2017.
//

#ifndef BEYONDLIGHT_FULLUSER_HH
#define BEYONDLIGHT_FULLUSER_HH

#include "User.hh"

namespace bl {
	namespace server {
		namespace user {
			class FullUser : public User {
			public:
				nlohmann::json serialize() const override;
				ISerializable *deserialize(nlohmann::json const &json) override;
				const std::string &getLastame() const;
				const std::string &getFirstname() const;
				const std::string &getEmail() const;
				const std::string &getPassword() const;
				void setLastname(const std::string &name);
				void setFirstname(const std::string &forename);
				void setEmail(const std::string &email);
				void setPassword(const std::string &password);
			protected:
				std::string m_firstname;
				std::string m_lastname;
				std::string m_email;
				std::string m_password;
			};
		}
	}
}


#endif //BEYONDLIGHT_FULLUSER_HH
