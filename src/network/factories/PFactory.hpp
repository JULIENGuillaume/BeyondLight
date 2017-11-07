//
// Created by Guillaume on 02/10/2017.
//

#ifndef KEYLOGGER_PFACTORY_HPP
#define KEYLOGGER_PFACTORY_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

namespace pattern {
	template <class T, class K = std::string>
	class PFactory {
	public:
		PFactory() = default;
		virtual ~PFactory() = default;

	public:
		virtual void registerModel(K key, std::shared_ptr<T> obj) {
			m_objMap[key] = obj;
		}

		virtual std::shared_ptr<T> create(K key) {
			auto it = m_objMap.find(key);
			if (it != m_objMap.end()) {
				return (*it->second).clone();
			}
			return nullptr;
		}

	protected:
		std::unordered_map<K, std::shared_ptr<T>> m_objMap;
	};
}

#endif //KEYLOGGER_PFACTORY_HPP
