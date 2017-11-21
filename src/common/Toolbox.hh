/*
** Toolbox.hh for BeyondLight in /home/guillaume/delivery/BeyondLight/Toolbox.hh
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Fri Nov 10 12:25:33 2017 Guillaume Julien
** Last update Fri Nov 10 12:25:33 2017 Guillaume Julien
*/

#ifndef BEYONDLIGHT_TOOLBOX_HH
#define BEYONDLIGHT_TOOLBOX_HH

#include <string>
#include <vector>

namespace common {
	class Toolbox {
	public:
		static std::vector<std::string> split(const std::string &str, const std::string &separator);
	};
}

#endif //BEYONDLIGHT_TOOLBOX_HH
