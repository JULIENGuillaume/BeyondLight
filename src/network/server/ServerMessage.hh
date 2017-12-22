//
// Created by Guillaume Julien on 20/12/2017.
//

#ifndef BEYONDLIGHT_SERVERMESSAGE_HH
#define BEYONDLIGHT_SERVERMESSAGE_HH

#include <boost/asio.hpp>
#include <IBinarizable.hh>

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

			struct ServerMessageBody {
				ServerMessageType type;
				uint64_t code;
				size_t messageSize;
				std::vector<char> message;
			};

			class ServerMessage  : public common::pattern::IBinarizable {
			public:
				std::pair<size_t, char*> getBinaryData() override;
				IBinarizable *loadFromBinaryData(std::pair<size_t, char*> const &data) override;
			private:
				boost::asio::ip::udp::endpoint m_endpoint;
				ServerMessageBody m_body;
			};
		}
	}
}

#endif //BEYONDLIGHT_SERVERMESSAGE_HH
