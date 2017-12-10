//
// Created by diguie_t on 12/10/2017.
//

#ifndef BEYONDLIGHT_LEFTMENU_HH
#define BEYONDLIGHT_LEFTMENU_HH

#include <unordered_map>
#include <string>

namespace bl {
	namespace mvc {
		class LeftMenu {
		public:
			static const std::string noRoute;
			static const std::string &getRequestControllerRouter(const std::string &requestRoute);

		private:
			static const std::unordered_map<std::string, std::string> m_requestToControllerRoute;
		};
	}
}

#endif //BEYONDLIGHT_LEFTMENU_HH
