//
// Created by Guillaume on 11/11/2017.
//

#ifndef BEYONDLIGHT_SOCKETMESSAGE_HH
#define BEYONDLIGHT_SOCKETMESSAGE_HH

namespace network {
	namespace socket {

		namespace message {
			enum EMessageType {
				NONE,
				COMMAND,
				ANSWER,
				INFO,
				ERROR
			};
		}

		namespace command {
			enum ECommandCode {
				NONE,

			};
		}

		namespace answer {
			enum EAnswerCode {
				NONE,

			};
		}

		namespace info {
			enum InfoCode {
				NONE,
			};
		}

		namespace error {
			enum ErrorCode {
				NONE,

			};
		}

		class SocketMessage {
		public:

		};
	}
}


#endif //BEYONDLIGHT_SOCKETMESSAGE_HH
