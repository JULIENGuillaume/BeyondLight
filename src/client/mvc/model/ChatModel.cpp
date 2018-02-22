//
// Created by diguie_t on 2/22/2018.
//

#include "ChatModel.hh"
#include "../controller/game/ChatController.hh"

namespace bl {
	namespace mvc {
		ChatModel::ChatModel(std::shared_ptr<network::client::ClientNetworkHandler> networkHandler) :
				ABaseModel(networkHandler) {
		}

		void ChatModel::update() {
			addMessage("login", "bonjour");
			// todo
		}

		void ChatModel::addMessage(
				const std::string &username,
				const std::string &content
		) {
			this->m_messages.push_front(std::make_pair(username, content));
			if (this->m_messages.size() >= ChatController::MAX_MESSAGES) {
				this->m_messages.pop_back();
			}
		}

		const std::deque<std::pair<std::string, std::string>> &ChatModel::getMessages() const {
			return m_messages;
		}
	}
}