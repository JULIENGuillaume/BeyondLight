//
// Created by Guillaume Julien on 22/12/2017.
//

#ifndef BEYONDLIGHT_ANETWORKHANDLER_HH
#define BEYONDLIGHT_ANETWORKHANDLER_HH

#include <string>
#include <future>
#include <map>
#include <queue>
#include "INetworkHandler.hh"

namespace bl {
	namespace network {
		namespace socket {

			class ANetworkHandler : public INetworkHandler {
			public:
				ANetworkHandler();
				virtual ~ANetworkHandler() = default;
			public:
				std::future<std::string> asyncGetLine() override;
				void asyncSend(std::string const &cmd) override;
			public:
				void addWatcher(
						EWatcherType type,
						std::string const &name,
						std::function<void(std::string const &)>
				) override;
				void notifyWatchers(EWatcherType type) override;
			protected:
				std::multimap<EWatcherType, std::pair<std::string, std::function<void(std::string const &)>>> m_watchers{};
				std::map<EWatcherType, std::function<void(ANetworkHandler * )>> m_privateWatchers{};
				std::queue<std::string> m_lines;
			};
		}
	}
}
#endif //BEYONDLIGHT_ANETWORKHANDLER_HH
