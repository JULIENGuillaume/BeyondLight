//
// Created by diguie_t on 2/22/2018.
//

#ifndef BEYONDLIGHT_CHATMODEL_HH
#define BEYONDLIGHT_CHATMODEL_HH

#include <deque>
#include <utility>
#include "ABaseModel.hh"

namespace bl {
	namespace mvc {
		class ChatModel : public ABaseModel {
		public:
			ChatModel(std::shared_ptr<network::client::ClientNetworkHandler>networkHandler);
			void update() override;
			const std::deque<std::pair<std::string, std::string>> &getMessages() const;
		private:
			std::deque<std::pair<std::string, std::string>> m_messages;
			void addMessage(const std::string &username, const std::string &content);
		};
	}
}

#endif //BEYONDLIGHT_CHATMODEL_HH
