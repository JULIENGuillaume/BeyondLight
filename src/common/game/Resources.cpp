//
// Created by diguie_t on 12/14/2017.
//

#include "Resources.hh"

bl::common::game::Resources::Resources(
		uint64_t iron,
		uint64_t crystal,
		uint64_t iridium,
		uint64_t antiMatter,
		uint64_t energy
) :
		m_iron(iron),
		m_crystal(crystal),
		m_iridium(iridium),
		m_antiMatter(antiMatter),
		m_energy(energy) {

}

uint64_t bl::common::game::Resources::getIron() const {
	return (this->m_iron);
}

void bl::common::game::Resources::setIron(uint64_t iron) {
	this->m_iron = iron;
}

uint64_t bl::common::game::Resources::getCrystal() const {
	return (this->m_crystal);
}

void bl::common::game::Resources::setCrystal(uint64_t crystal) {
	this->m_crystal = crystal;
}

uint64_t bl::common::game::Resources::getIridium() const {
	return (this->m_iridium);
}

void bl::common::game::Resources::setIridium(uint64_t iridium) {
	this->m_iridium = iridium;
}

uint64_t bl::common::game::Resources::getAntiMatter() const {
	return (this->m_antiMatter);
}

void bl::common::game::Resources::setAntiMatter(uint64_t antiMatter) {
	this->m_antiMatter = antiMatter;
}

uint64_t bl::common::game::Resources::getEnergy() const {
	return (this->m_energy);
}

void bl::common::game::Resources::setEnergy(uint64_t energy) {
	this->m_energy = energy;
}
