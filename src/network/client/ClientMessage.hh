//
// Created by Guillaume Julien on 20/12/2017.
//

#ifndef BEYONDLIGHT_CLIENTMESSAGE_HH
#define BEYONDLIGHT_CLIENTMESSAGE_HH

#include <cereal/types/string.hpp>
#include <string>

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

			struct ClientMessageBody {
			public:
				template<class Archive>
				void serialize(Archive &archive) {
					archive((int)type,
							code,
							messageSize,
							message); // serialize things by passing them to the archive
				}

			public:
				//char header[4] = {66, 76, 67, 76};
				ClientMessageType type;
				uint64_t code;
				size_t messageSize;
				std::string message;
			};

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

#endif //BEYONDLIGHT_CLIENTMESSAGE_HH
