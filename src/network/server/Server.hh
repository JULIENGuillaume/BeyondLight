/*
** Server.hh for BeyondLight in /home/guillaume/delivery/BeyondLight/Server.hh
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Fri Oct 27 18:22:22 2017 Guillaume Julien
** Last update Fri Oct 27 18:22:22 2017 Guillaume Julien
*/

#ifndef BEYONDLIGHT_SERVER_HH
#define BEYONDLIGHT_SERVER_HH

namespace bl {
	namespace network {
		class Server {
		public:
			Server();
			Server(unsigned short port);

		private:
			unsigned short m_port;		};
	}
}

#endif //BEYONDLIGHT_SERVER_HH
