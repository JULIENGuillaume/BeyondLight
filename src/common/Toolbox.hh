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
#include "UnionCast.hh"

namespace bl {
	namespace common {
		class Toolbox {
		public:
			static std::vector<std::string> split(
					const std::string &str,
					const std::string &separator
			);
			static std::vector<std::string> splitAtMax(
					const std::string &str,
					const std::string &separator,
					int max
			);
			static std::string getApplicationDir();
			static std::u16string to16string(const std::string &str);
			static std::u16string to16string(const std::wstring &str);
			static std::wstring toWstring(const std::u16string &str);
			static std::wstring toWstring(const std::string &str);
			static std::string toString(const std::wstring &str);
			static std::string sha512This(const std::string &str);
			static std::string generateSalt(size_t size);
			static const std::u16string &escapeChar(
					std::u16string &str,
					const std::vector<char> &toEscape,
					char16_t eschapeChar
			);
			template <class T, class V> static V forceCast(T data) {
				UnionCast<T, V> unionCast;
				unionCast.inputType = data;
				return unionCast.outputType;
			};
		};
	}
}

#endif //BEYONDLIGHT_TOOLBOX_HH
