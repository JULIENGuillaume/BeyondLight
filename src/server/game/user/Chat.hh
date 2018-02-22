//
// Created by Guillaume Julien on 22/02/2018.
//

#ifndef BEYONDLIGHT_CHAT_HH
#define BEYONDLIGHT_CHAT_HH

#include <string>
#include <vector>

namespace bl {
	namespace server {
		namespace game {
			namespace user {
				class Chat {
				public:
					Chat() = default;
					virtual ~Chat() = default;
				public:
					void addMsg(std::string const& user, std::string const& msg);
					std::vector<std::pair<std::string, std::string>> getNLastMessages(uint32_t nbMsg);
				private:
					std::vector<std::pair<std::string, std::string>> m_messages;
				};
			}
		}
	}
}

#endif //BEYONDLIGHT_CHAT_HH
