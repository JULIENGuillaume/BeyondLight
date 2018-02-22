//
// Created by Guillaume Julien on 13/02/2018.
//

#ifndef BEYONDLIGHT_LAUNCHERCLIENT_HH
#define BEYONDLIGHT_LAUNCHERCLIENT_HH

#include "AClientTcp.hh"

namespace bl {
	namespace network {
		namespace client {
			class LauncherClient : public AClientTcp {
			public:
				explicit LauncherClient();
			protected:
				void mainLoop() override;
			private:
				std::string getLine();
				std::string readSize(size_t size);
			private:
				std::string m_data;
				const std::string newLineDelim = "\r\n";
				const std::string msgStartHeader = "#$BL-->";
			};
		}
	}
}

#endif //BEYONDLIGHT_LAUNCHERCLIENT_HH
