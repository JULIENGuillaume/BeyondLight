//
// Created by Guillaume Julien on 16/12/2017.
//

#include "Chrono.hh"

using clock_type = std::chrono::steady_clock;

bl::common::event::Chrono::Chrono() : m_chrono(clock_type::now()) {}

void bl::common::event::Chrono::reset() {
	this->m_chrono = clock_type::now();
}

uint64_t bl::common::event::Chrono::getElapsedHours() const {
	auto now = clock_type::now();
	return std::chrono::duration_cast<std::chrono::hours>(now - m_chrono).count();
}

uint64_t bl::common::event::Chrono::getElapsedMinutes() const {
	auto now = clock_type::now();
	return std::chrono::duration_cast<std::chrono::minutes>(now - m_chrono).count();
}

uint64_t bl::common::event::Chrono::getElapsedSeconds() const {
	auto now = clock_type::now();
	return std::chrono::duration_cast<std::chrono::seconds>(now - m_chrono).count();
}

uint64_t bl::common::event::Chrono::getElapsedMilliseconds() const {
	auto now = clock_type::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(now - m_chrono).count();
}

uint64_t bl::common::event::Chrono::getElapsedMicroseconds() const {
	auto now = clock_type::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(now - m_chrono).count();
}

uint64_t bl::common::event::Chrono::getElapsedNanoseconds() const {
	auto now = clock_type::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(now - m_chrono).count();
}
