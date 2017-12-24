//
// Created by Guillaume on 02/10/2017.
//

#ifndef KEYLOGGER_IACCEPTOR_HH
#define KEYLOGGER_IACCEPTOR_HH

#include "ISocket.hh"

namespace bl {
	namespace network {
		namespace socket {
			class IAcceptor {
			public:
				virtual ~IAcceptor() = default;

			public:
				virtual void accept(ISocket &socket) = 0;
			};
		}
	}
}

#endif //KEYLOGGER_IACCEPTOR_HH
