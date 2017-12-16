//
// Created by Guillaume Julien on 16/12/2017.
//

#ifndef BEYONDLIGHT_CHRONO_HH
#define BEYONDLIGHT_CHRONO_HH

#include <chrono>

namespace bl {
	namespace common {
		namespace event {
			class Chrono {
			public:
				Chrono();
				~Chrono() = default;

			public:
				void reset();
				uint64_t getElapsedHours() const;
				uint64_t getElapsedMinutes() const;
				uint64_t getElapsedSeconds() const;
				uint64_t getElapsedMilliseconds() const;
				uint64_t getElapsedMicroseconds() const;
				uint64_t getElapsedNanoseconds() const;

			private:
				std::chrono::time_point<std::chrono::steady_clock> m_chrono;
			};
		}
	}
}
#endif //BEYONDLIGHT_CHRONO_HH
