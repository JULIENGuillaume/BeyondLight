//
// Created by diguie_t on 2/22/2018.
//

#include "ChatModel.hh"
#include "../controller/game/ChatController.hh"
#include "../../../common/Toolbox.hh"

namespace bl {
	namespace mvc {
		ChatModel::ChatModel(std::shared_ptr<network::client::ClientNetworkHandler> networkHandler) :
				ABaseModel(networkHandler) {
		}

		void ChatModel::update() {
			static uint64_t maxRetry = 3;
			m_networkHandler->send(m_networkHandler->getApiHelper()->buildNewApiRequest(m_networkHandler->getApiHelper()->REQUEST_GET_LAST_42_CHAT_MESSAGES));
			for (uint64_t j = 0; j < maxRetry; j++) {
				auto answer = m_networkHandler->getMessage();
				if (answer.getBody().type != bl::network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK || answer.getBody().code != 235)
					continue;
				this->m_messages.clear();
				auto data = common::Toolbox::split(answer.getBody().message, "\\:");
				for (int i = 0;
					 i + 1 < data.size();
					 i += 2) {
					addMessage(data[i], data[i + 1]);
					std::cout << data[i] << ": " << data[i + 1] << std::endl;
				}
				return;
			}
		}

		void ChatModel::addMessage(
				const std::string &username,
				const std::string &content
		) {
			this->m_messages.push_back(std::make_pair(username, content));
			if (this->m_messages.size() >= ChatController::MAX_MESSAGES) {
				this->m_messages.pop_front();
			}
		}

		const std::deque<std::pair<std::string, std::string>> &ChatModel::getMessages() const {
			return m_messages;
		}
	}
}