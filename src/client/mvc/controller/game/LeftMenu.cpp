//
// Created by diguie_t on 12/10/2017.
//

#include "LeftMenu.hh"

namespace bl {
	namespace mvc {
		const std::string LeftMenu::noRoute = std::string();
		const std::unordered_map<std::string, std::string> LeftMenu::m_requestToControllerRoute = {
				{"route-buildings", "/buildings"},
				{"route-technologies", "/technologies"},
				{"route-ships", "/ships"},
				{"route-overview", "/overview"},
				{"route-chat", "/chat"}
		};

		const std::string &LeftMenu::getRequestControllerRouter(const std::string &requestRoute) {
			const auto result = LeftMenu::m_requestToControllerRoute.find(requestRoute);
			if (result == LeftMenu::m_requestToControllerRoute.end()) {
				return (LeftMenu::noRoute);
			}
			return (result->second);
		}
	}
}
