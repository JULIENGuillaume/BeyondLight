/*
** BeyondLightClient.hh for BeyondLight in /home/guillaume/delivery/BeyondLight/BeyondLightClient.hh
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Tue Nov 07 14:43:06 2017 Guillaume Julien
** Last update Tue Nov 07 14:43:06 2017 Guillaume Julien
*/

#ifndef BEYONDLIGHT_BEYONDLIGHTCLIENT_HH
#define BEYONDLIGHT_BEYONDLIGHTCLIENT_HH

#include "AClientUdp.hh"

namespace network {
	namespace client {
		class BeyondLightClient : public AClientUdp {
		public:
			BeyondLightClient();
		protected:
			void mainLoop() override;
		};
	}
}


#endif //BEYONDLIGHT_BEYONDLIGHTCLIENT_HH
