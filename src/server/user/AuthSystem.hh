/*
** AuthSystem.hh for BeyondLight in /home/guillaume/delivery/BeyondLight/AuthSystem.hh
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Thu Nov 09 17:59:05 2017 Guillaume Julien
** Last update Thu Nov 09 17:59:05 2017 Guillaume Julien
*/

#ifndef BEYONDLIGHT_AUTHSYSTEM_HH
#define BEYONDLIGHT_AUTHSYSTEM_HH

#include <string>
#include <ISocket.hh>

namespace server {
	namespace user {
		class AuthSystem {
		public:
			AuthSystem();
			virtual ~AuthSystem();

		public:
			bool tryToAuthenticate();
			void setClientSocket(std::shared_ptr<network::socket::ISocket> &clientSocket);

		private:
			std::shared_ptr<network::socket::ISocket> m_clientSocket;
		};
	}
}

#endif //BEYONDLIGHT_AUTHSYSTEM_HH
