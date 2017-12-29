/*
** User.hh for BeyondLight in /home/guillaume/delivery/BeyondLight/User.hh
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Thu Nov 09 17:56:28 2017 Guillaume Julien
** Last update Thu Nov 09 17:56:28 2017 Guillaume Julien
*/

#ifndef BEYONDLIGHT_USER_HH
#define BEYONDLIGHT_USER_HH

#include <string>
#include <ISerializable.hh>
#include "../UniqueObject.hh"

namespace bl {
	namespace server {
		namespace user{
			class User : protected UniqueObject {
			public:
				User() = default;
				nlohmann::json serialize() const override;
				ISerializable *deserialize(nlohmann::json const &json) override;
				const std::string &getLogin() const;
				void setLogin(const std::string &login);
				const std::string &getLastPlanetId() const;
				void setLastPlanetId(const std::string &lastPlanetId);

			protected:
				std::string m_login{};
				std::string m_lastPlanetId{};
			};
		}
	}
}

#endif //BEYONDLIGHT_USER_HH
