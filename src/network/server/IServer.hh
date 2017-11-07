//
// Created by Guillaume on 02/10/2017.
//

#ifndef KEYLOGGER_ISERVER_HH
#define KEYLOGGER_ISERVER_HH

namespace network {
	namespace server {
		class IServer {
		public:
			virtual ~IServer() = default;

		public:
			virtual void run() = 0;
			virtual void stop() = 0;
			virtual void restart() = 0;

		protected:
			virtual void mainLoop(std::shared_ptr<socket::ISocket> socket) = 0;
		};
	}
}

#endif //KEYLOGGER_ISERVER_HH
