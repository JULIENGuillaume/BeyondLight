//
// Created by Guillaume on 02/10/2017.
//

#ifndef KEYLOGGER_PSINGLETON_HPP
#define KEYLOGGER_PSINGLETON_HPP

namespace pattern {
	template <class T>
	class PSingleton {
	protected:
		virtual ~PSingleton() = default;

	public:
		static T *getInstance() {
			static T m_instance;
			return &m_instance;
		}
	};
}

#endif //KEYLOGGER_PSINGLETON_HPP
