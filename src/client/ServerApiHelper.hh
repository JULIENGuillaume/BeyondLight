//
// Created by Guillaume on 29/12/2017.
//

#ifndef BEYONDLIGHT_SERVERAPIHELPER_HH
#define BEYONDLIGHT_SERVERAPIHELPER_HH

#include <ClientMessage.hh>

namespace bl {
	namespace client {
		class ServerApiHelper {
		public:
			const std::string REQUEST_ = "";
			const std::string REQUEST_LOGIN = "login";
			const std::string REQUEST_REGISTER = "register";
			const std::string REQUEST_VALIDATE_NETWORK = "network_connection_validation";
			const std::string REQUEST_CURRENT_RESOURCES = "current_resources";
			const std::string REQUEST_BUILDING_INFO = "building_info";
			const std::string REQUEST_BUILDING_UPGRADE = "building_upgrade";
			const std::string REQUEST_TECHNOLOGY_INFO = "technology_info";
			const std::string REQUEST_TECHNOLOGY_UPGRADE = "technology_upgrade";
			const std::string REQUEST_LOGOUT = "logout";
			const std::string REQUEST_SEND_CHAT_MESSAGE = "user_send_chat_message";
			const std::string REQUEST_GET_CHAT_MESSAGES = "user_get_chat_messages";
			const std::string REQUEST_GET_LAST_42_CHAT_MESSAGES = "user_get_last_42_chat_messages";

		public:
			ServerApiHelper();
			network::client::ClientMessage buildNewApiRequest(std::string const& requestName);
			network::client::ClientMessage buildNewApiRequest(std::string const& requestName, std::string const& arg);
			network::client::ClientMessage buildNewApiRequest(std::string const& requestName, std::vector<std::string> const& args);
			network::client::ClientMessage buildNewApiRequest(std::string const& requestName, std::unordered_map<std::string, std::string> const& args);

		protected:
			void registerRequest(std::string const &requestName, network::client::ClientMessageType type, server::api::EApiType requestType, uint64_t code, std::string const &message);

		private:
			std::unordered_map<std::string, network::client::ClientMessage> m_requestModel;
		};
	}
}



#endif //BEYONDLIGHT_SERVERAPIHELPER_HH
