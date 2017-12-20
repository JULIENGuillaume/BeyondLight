//
// Created by diguie_t on 12/14/2017.
//

#ifndef BEYONDLIGHT_RESOURCES_HH
#define BEYONDLIGHT_RESOURCES_HH

#include "../pattern/ISerializable.hh"

namespace bl {
	namespace common {
		namespace game {
			class Resources : public bl::common::pattern::ISerializable {
			public:
				explicit Resources(
						uint64_t iron = 0,
						uint64_t crystal = 0,
						uint64_t iridium = 0,
						uint64_t antiMatter = 0,
						uint64_t energy = 0
				);
			public:
				uint64_t getIron() const;
				void setIron(uint64_t iron);
				void addIron(uint64_t iron);
				void removeIron(uint64_t iron);
				uint64_t getCrystal() const;
				void setCrystal(uint64_t crystal);
				void addCrystal(uint64_t crystal);
				void removeCrystal(uint64_t crystal);
				uint64_t getIridium() const;
				void setIridium(uint64_t iridium);
				void addIridium(uint64_t iridium);
				void removeIridium(uint64_t iridium);
				uint64_t getAntiMatter() const;
				void setAntiMatter(uint64_t antiMatter);
				void addAntiMatter(uint64_t antiMatter);
				void removeAntiMatter(uint64_t antiMatter);
				uint64_t getEnergy() const;
				void setEnergy(uint64_t energy);
				void addEnergy(uint64_t energy);
				void removeEnergy(uint64_t energy);
			public:
				nlohmann::json serialize() const override;
				ISerializable *deserialize(nlohmann::json const &json) override;
			public:
				bool operator<(const Resources &rhs) const;
				bool operator>(const Resources &rhs) const;
				bool operator<=(const Resources &rhs) const;
				bool operator>=(const Resources &rhs) const;
			public:
				Resources& operator-(const Resources &rhs);
				Resources& operator+(const Resources &rhs);
				Resources& operator*(uint64_t fac);
				Resources& operator/(uint64_t fac);
			private:
				uint64_t m_iron;
				uint64_t m_crystal;
				uint64_t m_iridium;
				uint64_t m_antiMatter;
				uint64_t m_energy;
			};
		}
	}
}
#endif //BEYONDLIGHT_RESOURCES_HH
