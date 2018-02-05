//
// Created by Guillaume Julien on 20/12/2017.
//

#ifndef BEYONDLIGHT_CLIENTMESSAGE_HH
#define BEYONDLIGHT_CLIENTMESSAGE_HH

#include <cereal/types/string.hpp>
#include <string>
#include "../../server/api/Api.hh"

namespace bl {
	namespace network {
		namespace client {
			enum ClientMessageType {
				CLIENT_MESSAGE_TYPE_NONE = 0,
				CLIENT_MESSAGE_TYPE_ANSWER_OK = 1,
				CLIENT_MESSAGE_TYPE_ANSWER_KO = 2,
				CLIENT_MESSAGE_TYPE_REQUEST = 3,
				CLIENT_MESSAGE_TYPE_ERROR = 4,
				CLIENT_MESSAGE_TYPE_CRITICAL = 5
			};

			#pragma pack(push, 1)
			struct ClientMessageBody {
			public:
				template<class Archive>
				void serialize(Archive &archive) {
					archive((int)msgType,
					        (int)apiType,
							code,
					        sessionId,
							messageSize,
							message); // serialize things by passing them to the archive
				}

			public:
				ClientMessageType msgType = CLIENT_MESSAGE_TYPE_NONE;
				::bl::server::api::EApiType apiType;
				uint64_t code = 0;
				std::string sessionId = "";
				size_t messageSize = 0;
				std::string message = "";
			};
			#pragma pack(pop)

			class ClientMessage {
			public:
				template<class Archive>
				void serialize(Archive &archive) {
					archive(m_body); // serialize things by passing them to the archive
				}

				const ClientMessageBody &getBody() const;
				ClientMessageBody &getBody();
			private:
				ClientMessageBody m_body;
			};
		}
	}
}

std::ostream& operator<<(std::ostream& os, const bl::network::client::ClientMessage& dt);
std::ostream& operator<<(std::ostream& os, const bl::network::client::ClientMessageBody& dt);

#endif //BEYONDLIGHT_CLIENTMESSAGE_HH
