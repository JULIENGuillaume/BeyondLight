//
// Created by diguie_t on 11/23/2017.
//

#ifndef BEYONDLIGHT_NETWORKHANDLER_HH
#define BEYONDLIGHT_NETWORKHANDLER_HH

#include <future>
#include <string>
#include <map>
#include <queue>
#include "IClient.hh"

namespace bl {
	namespace network {
		namespace client {
			enum EWatcherType {
				WATCH_READ,
				WATCH_SEND,
				WATCH_QUIT,
				WATCH_ALL_WATCHER_READ_DONE,
				WATCH_ALL_WATCHER_SEND_DONE
			};

			class NetworkHandler {
			public:
				explicit NetworkHandler(
						std::string const &ip = "127.0.0.1",
						unsigned short port = 4224
				);
				virtual ~NetworkHandler();
			public:
				std::string getLine();
				void send(std::string const &cmd);
				std::future<std::string> asyncGetLine();
				void asyncSend(std::string const &cmd);
			public:
				void addWatcher(
						EWatcherType type,
						std::string const &name,
						std::function<void(std::string const &)>
				);
				void notifyWatchers(EWatcherType type);
			private:
				void retrieveLine();
			private:
				std::shared_ptr<IClient> m_networkClient;
				std::shared_ptr<std::thread> m_networkThread;
			private:
				std::multimap<EWatcherType, std::pair<std::string, std::function<void(std::string const &)>>> m_watchers;
				std::map<EWatcherType, std::function<void(NetworkHandler *)>> m_privateWatchers;
				std::queue<std::string> m_lines;
			};
		}
	}
}

#endif //BEYONDLIGHT_NETWORKHANDLER_HH
