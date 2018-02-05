/*
** RegisteredUsers.hh for BeyondLight in /home/guillaume/delivery/BeyondLight/RegisteredUsers.hh
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Thu Nov 09 18:37:08 2017 Guillaume Julien
** Last update Thu Nov 09 18:37:08 2017 Guillaume Julien
*/

#ifndef BEYONDLIGHT_REGISTEREDUSERS_HH
#define BEYONDLIGHT_REGISTEREDUSERS_HH

#include <PSingleton.hpp>
#include <unordered_map>

namespace bl {
	namespace server {
		namespace user {
			struct RegisteredUsers : public bl::common::pattern::PSingleton<RegisteredUsers> {
				std::unordered_map<std::string, std::string> users = {std::make_pair("root", "root")};
			};

		}
	}
}

#endif //BEYONDLIGHT_REGISTEREDUSERS_HH
