//
// Created by Guillaume on 28/12/2017.
//

#ifndef BEYONDLIGHT_LOADEDDATA_HH
#define BEYONDLIGHT_LOADEDDATA_HH

#include <unordered_map>
#include <unordered_set>
#include "user/SessionIdentifier.hh"
#include "game/planet/Planet.hh"

namespace bl {
	namespace server {
		struct LoadedData {
			std::unordered_map<std::string, std::shared_ptr<user::SessionIdentifier>> activeSessions;
			std::unordered_set<std::string> loggedUsers;
			std::unordered_map<std::string, std::shared_ptr<game::planet::Planet>> loadedPlanets;
		};
	}
}

#endif //BEYONDLIGHT_LOADEDDATA_HH
