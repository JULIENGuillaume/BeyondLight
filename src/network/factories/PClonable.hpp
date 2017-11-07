//
// Created by Guillaume on 02/10/2017.
//

#ifndef KEYLOGGER_ICLONABLE_HPP
#define KEYLOGGER_ICLONABLE_HPP

#include <memory>

namespace pattern {
	template <class T>
	class PClonable {
	public:
		virtual ~PClonable() = default;

	public:
		virtual std::shared_ptr<T> clone() const = 0;
	};
}

#endif //KEYLOGGER_ICLONABLE_HPP
