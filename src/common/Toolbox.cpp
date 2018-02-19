/*
** Toolbox.cpp for BeyondLight in /home/guillaume/delivery/BeyondLight/Toolbox.cpp
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Fri Nov 10 12:25:33 2017 Guillaume Julien
** Last update Fri Nov 10 12:25:33 2017 Guillaume Julien
*/

#include <cstdio>
#include <cstring>
#include <openssl/sha.h>
#include <random>
#include <functional>
#include <iostream>
#include <algorithm>
#include "Toolbox.hh"

#ifdef WIN32

#include "windows.h"

#endif // WIN32

namespace bl {
	std::vector<std::string> common::Toolbox::split(
		const std::string &str,
		const std::string &sep
	) {
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

	std::vector<std::string> common::Toolbox::splitAtMax(
		const std::string &str,
		const std::string &sep,
		int max
	) {
		std::vector<std::string> tokens;
		std::string s = str;
		size_t pos;
		while (static_cast<int>(tokens.size()) < max && (pos = s.find(sep)) != std::string::npos) {
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
		WCHAR wpath[MAX_PATH];
		GetModuleFileNameW(hModule, wpath, MAX_PATH);
		std::wstring wide(wpath);
		std::string path = common::Toolbox::toString(wide);
		path = path.substr(0, path.find_last_of("\\/"));
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

	const std::u16string &common::Toolbox::escapeChar(
		std::u16string &str,
		const std::vector<char> &toEscape,
		char16_t eschapeChar
	) {
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

	std::string common::Toolbox::sha512This(const std::string &str) {
		std::string ret;
		unsigned char digest[SHA512_DIGEST_LENGTH];

		SHA512(reinterpret_cast<const unsigned char *>(str.c_str()), str.size(), (unsigned char *) &digest);

		char mdString[SHA512_DIGEST_LENGTH * 2 + 1];

		for (int i = 0; i < SHA512_DIGEST_LENGTH; i++)
			sprintf(&mdString[i * 2], "%02x", (unsigned int) digest[i]);

		printf("SHA512 digest: %s\n", mdString);
		ret.resize(SHA512_DIGEST_LENGTH * 2, '\0');
		for (int i = 0; i < SHA512_DIGEST_LENGTH * 2; ++i) {
			ret[i] = mdString[i];
		}

		return ret;
	}

	std::string common::Toolbox::generateSalt(size_t size) {
		typedef std::vector<char> char_array;
		std::function<char(void)> rand_char;

		const auto ch_set = char_array(
			{'0', '1', '2', '3', '4',
			 '5', '6', '7', '8', '9',
			 'A', 'B', 'C', 'D', 'E', 'F',
			 'G', 'H', 'I', 'J', 'K',
			 'L', 'M', 'N', 'O', 'P',
			 'Q', 'R', 'S', 'T', 'U',
			 'V', 'W', 'X', 'Y', 'Z',
			 'a', 'b', 'c', 'd', 'e', 'f',
			 'g', 'h', 'i', 'j', 'k',
			 'l', 'm', 'n', 'o', 'p',
			 'q', 'r', 's', 't', 'u',
			 'v', 'w', 'x', 'y', 'z'
			});

		std::default_random_engine rng(std::random_device{}());
		std::uniform_int_distribution<> dist(0, ch_set.size() - 1);
		rand_char = [ch_set, &dist, &rng]() { return ch_set[dist(rng)]; };
		std::string str(size, 0);
		std::generate_n( str.begin(), size, rand_char );
		std::cout << "Salt is " << str << std::endl;
		return str;
	}
}
