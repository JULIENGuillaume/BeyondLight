//
// Created by Guillaume on 02/10/2017.
//

#ifndef KEYLOGGER_ICLIENT_HH
#define KEYLOGGER_ICLIENT_HH

#include <string>

namespace network {
	namespace client {
		class IClient {
		public:
			virtual ~IClient() = default;

		public:
			virtual bool connectTo(const std::string &address, unsigned short port) = 0;
			virtual void disconnect() = 0;

		protected:
			virtual void mainLoop() = 0;
		};
	}
}

#endif //KEYLOGGER_ICLIENT_HH
