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

		private:
			unsigned long int m_id;
			std::string m_login;
			char m_nonce[32];
		};
	}
}

#endif //BEYONDLIGHT_USER_HH
