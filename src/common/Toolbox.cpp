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
#ifdef WIN32
#include "windows.h"
#endif // WIN32



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

std::vector<std::string> common::Toolbox::splitAtMax(const std::string &str, const std::string &sep, int max) {
	std::vector<std::string> tokens;
	std::string s = str;
	size_t pos;

	while (tokens.size() < max && (pos = s.find(sep)) != std::string::npos) {
		auto token = s.substr(0, pos);
		if (!token.empty())
			tokens.push_back(token);
		s.erase(0, pos + sep.length());
	}
	if (!s.empty())
		tokens.push_back(s);
	return tokens;
}

std::string common::Toolbox::getApplicationDir() {
#ifdef WIN32
	HMODULE hModule = GetModuleHandleW(NULL);
	WCHAR   wpath[MAX_PATH];

	GetModuleFileNameW(hModule, wpath, MAX_PATH);
	std::wstring wide(wpath);

	std::string path = common::Toolbox::toString(wide);
	path = path.substr( 0, path.find_last_of("\\/") );
	return (path);
#else
    return (""); // todo handle other platform
#endif // WIN32

}

std::u16string common::Toolbox::to16string(const std::string &str) {
	return (std::u16string(str.begin(), str.end()));
}

std::u16string common::Toolbox::to16string(const std::wstring &str) {
	return (std::u16string(str.begin(), str.end()));
}

std::wstring common::Toolbox::toWstring(const std::u16string &str) {
	return (std::wstring(str.begin(), str.end()));
}

std::string common::Toolbox::toString(const std::wstring &str) {
	return (std::string(str.begin(), str.end()));
}

const std::u16string &common::Toolbox::escapeChar(std::u16string &str, const std::vector<char> &toEscape, char16_t eschapeChar) {
	bool needEscapeChar = false;
	for (char16_t c : str) {
		for (char escape : toEscape) {
			const char16_t convertedChar = static_cast<char16_t>(escape);
			if (c == convertedChar) {
				needEscapeChar = true;
			}
		}
	}

	if (needEscapeChar) {
		str = eschapeChar + str;
	}

	return (str);
}

std::wstring common::Toolbox::toWstring(const std::string &str) {
	return (std::wstring(str.begin(), str.end()));
}
