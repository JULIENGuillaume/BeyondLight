//
// Created by Guillaume Julien on 20/12/2017.
//

#ifndef BEYONDLIGHT_SERVERMESSAGE_HH
#define BEYONDLIGHT_SERVERMESSAGE_HH

#include <cereal/types/string.hpp>
#include <string>

namespace bl {
	namespace network {
		namespace server {
			enum ServerMessageType {
				SERVER_MESSAGE_TYPE_NONE = 0,
				SERVER_MESSAGE_TYPE_ANSWER_OK = 1,
				SERVER_MESSAGE_TYPE_ANSWER_KO = 2,
				SERVER_MESSAGE_TYPE_INFO = 3,
				SERVER_MESSAGE_TYPE_COMMAND = 4,
				SERVER_MESSAGE_TYPE_ERROR = 5,
				SERVER_MESSAGE_TYPE_CRITICAL = 6
			};

			#pragma pack(push, 1)
			struct ServerMessageBody {
			public:
				template<class Archive>
				void serialize(Archive &archive) {
					archive(type, code, messageSize, message); // serialize things by passing them to the archive
				}

			public:
				//char header[4] = {66, 76, 83, 86};
				ServerMessageType type = SERVER_MESSAGE_TYPE_NONE;
				uint64_t code = 0;
				size_t messageSize = 0;
				std::string message = "";
			};
			#pragma pack(pop)

			class ServerMessage {
			public:
				template<class Archive>
				void serialize(Archive &archive) {
					archive(m_body); // serialize things by passing them to the archive
				}

				const ServerMessageBody &getBody() const;
				ServerMessageBody &getBody() ;
			private:
				ServerMessageBody m_body;
			};
		}
	}
}

std::ostream& operator<<(std::ostream& os, const bl::network::server::ServerMessage& dt);
std::ostream& operator<<(std::ostream& os, const bl::network::server::ServerMessageBody& dt);

#endif //BEYONDLIGHT_SERVERMESSAGE_HH
