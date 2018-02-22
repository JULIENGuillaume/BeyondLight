//
// Created by Guillaume Julien on 13/02/2018.
//

#ifndef BEYONDLIGHT_UPDATERSERVER_HH
#define BEYONDLIGHT_UPDATERSERVER_HH

#include "AServerTcp.hh"

namespace bl {
	namespace network {
		namespace server {
			class UpdaterServer : public AServerTcp {
			public:
				explicit UpdaterServer(unsigned short port);
			protected:
				void mainLoop(std::shared_ptr<socket::ISocket> socket) override;
			};
		}
	}
}

#endif //BEYONDLIGHT_UPDATERSERVER_HH
