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
#include <unordered_set>
#include "../UniqueObject.hh"
#include "../game/technology/ITechnology.hh"

namespace bl {
	namespace server {
		namespace user{
			class User : public UniqueObject {
			public:
				User() = default;
				nlohmann::json serialize() const override;
				ISerializable *deserialize(nlohmann::json const &json) override;
				const std::string &getLogin() const;
				void setLogin(const std::string &login);
				const std::string &getLastPlanetId() const;
				void setLastPlanetId(const std::string &lastPlanetId);
				const std::unordered_set<int> &getTechnologies() const;
				void addTechnology(int techId);
			protected:
				std::string m_login{};
				std::string m_lastPlanetId{};
				std::unordered_set<int> m_technologies;
			};
		}
	}
}

#endif //BEYONDLIGHT_USER_HH
