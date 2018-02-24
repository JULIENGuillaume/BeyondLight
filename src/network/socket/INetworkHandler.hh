//
// Created by Guillaume Julien on 22/12/2017.
//

#ifndef BEYONDLIGHT_INETWORKHANDLER_HH
#define BEYONDLIGHT_INETWORKHANDLER_HH

#include <future>
#include <string>
#include <functional>

namespace bl {
	namespace network {
		namespace socket {
			enum EWatcherType {
				WATCH_READ,
				WATCH_SEND,
				WATCH_QUIT,
				WATCH_ALL_WATCHER_READ_DONE,
				WATCH_ALL_WATCHER_SEND_DONE
			};

			class INetworkHandler {
			public:
				virtual ~INetworkHandler() = default;
			public:
				virtual std::string getLine() = 0;
				virtual void send(std::string const &cmd)= 0;
				virtual std::future<std::string> asyncGetLine()= 0;
				virtual void asyncSend(std::string const &cmd)= 0;
				virtual void setTimeout(uint64_t milliseconds) = 0;
			public:
				virtual void addWatcher(
						EWatcherType type,
						std::string const &name,
				std::function<void(std::string const &)>
				) = 0;
				virtual void notifyWatchers(EWatcherType type) = 0;

			protected:
				virtual void retrieveLine() = 0;
			};
		}
	}
}

#endif //BEYONDLIGHT_INETWORKHANDLER_HH
