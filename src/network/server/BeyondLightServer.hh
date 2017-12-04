/*
** BeyondLightServer.hh for BeyondLight in /home/guillaume/delivery/BeyondLight/BeyondLightServer.hh
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Tue Nov 07 14:42:17 2017 Guillaume Julien
** Last update Tue Nov 07 14:42:17 2017 Guillaume Julien
*/

#ifndef BEYONDLIGHT_BEYONDLIGHTSERVER_HH
#define BEYONDLIGHT_BEYONDLIGHTSERVER_HH

#include "AServerUdp.hh"

namespace network {
	namespace server {
		class BeyondLightServer : public AServerUdp {
		public:
			BeyondLightServer(unsigned short port);
		protected:
			void mainLoop(std::shared_ptr<socket::ISocket> socket) override;

		private:
			bool m_running = true;
		};
	}
}

#endif //BEYONDLIGHT_BEYONDLIGHTSERVER_HH
