/*
** User.hh for BeyondLight in /home/guillaume/delivery/BeyondLight/User.hh
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Thu Nov 09 17:56:28 2017 Guillaume Julien
** Last update Thu Nov 09 17:56:28 2017 Guillaume Julien
*/

#ifndef BEYONDLIGHT_USER_HH
#define BEYONDLIGHT_USER_HH

#include <string>

namespace server {
	namespace user {
		class User {
		public:
			User(unsigned long m_id, const std::string &m_login);

            unsigned long int getId() const;
			std::string getLogin() const;
			std::string getFirstName() const;
			std::string getLastName() const;
			std::string getEmail() const;
			std::string getPassword() const;

            void setId(const unsigned long int &);
            void setLogin(const std::string &);
            void setFirstName(const std::string &);
            void setLastName(const std::string &);
            void setEmail(const std::string &);
            void setPassword(const std::string &);

		private:
			unsigned long int m_id;
			std::string m_login;
			std::string m_firstName;
			std::string m_lastName;
			std::string m_email;
			std::string m_password;
			char m_nonce[32];
		};
	}
}

#endif //BEYONDLIGHT_USER_HH
