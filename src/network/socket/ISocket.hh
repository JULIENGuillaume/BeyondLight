//
// Created by Guillaume on 02/10/2017.
//

#ifndef KEYLOGGER_ISOCKET_HH
#define KEYLOGGER_ISOCKET_HH

#include <string>
#include "PClonable.hpp"

namespace network {
	namespace socket {
		class ISocket : public pattern::PClonable<ISocket> {
		public:
			~ISocket() override = default;

		public:
			virtual bool connect(std::string const &address, unsigned short port) = 0;
			virtual bool openConnection(unsigned short port) = 0;

		public:
			virtual void send(char const* msg) = 0;
			virtual void send(std::string const& msg) = 0;

		public:
			virtual char* receive(char *buf, size_t bufSize) = 0;
			virtual std::string receive() = 0;

		public:
			virtual void setAutoDataEncrypt(bool encrypt) = 0;
			virtual void setAutoDataDecrypt(bool decrypt) = 0;
		};
	}
}

#endif //KEYLOGGER_ISOCKET_HH
