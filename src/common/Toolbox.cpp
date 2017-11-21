/*
** Toolbox.cpp for BeyondLight in /home/guillaume/delivery/BeyondLight/Toolbox.cpp
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Fri Nov 10 12:25:33 2017 Guillaume Julien
** Last update Fri Nov 10 12:25:33 2017 Guillaume Julien
*/

#include "Toolbox.hh"

std::vector<std::string> common::Toolbox::split(const std::string &str, const std::string &sep) {
	std::vector<std::string> tokens;
	std::string s = str;
	size_t pos;

	while ((pos = s.find(sep)) != std::string::npos) {
		auto token = s.substr(0, pos);
		if (!token.empty())
			tokens.push_back(token);
		s.erase(0, pos + sep.length());
	}
	if (!s.empty())
		tokens.push_back(s);
	return tokens;
}