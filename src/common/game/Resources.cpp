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

void bl::common::game::Resources::addIron(uint64_t iron) {
	this->m_iron += iron;
}

void bl::common::game::Resources::addCrystal(uint64_t crystal) {
	this->m_crystal += crystal;
}

void bl::common::game::Resources::addIridium(uint64_t iridium) {
	this->m_iridium += iridium;
}

void bl::common::game::Resources::addAntiMatter(uint64_t antiMatter) {
	this->m_antiMatter += antiMatter;
}

void bl::common::game::Resources::addEnergy(uint64_t energy) {
	this->m_energy += energy;
}

void bl::common::game::Resources::removeIron(uint64_t iron) {
	this->m_iron -= iron > this->m_iron ? this->m_iron : iron;
}

void bl::common::game::Resources::removeCrystal(uint64_t crystal) {
	this->m_crystal -= crystal > this->m_crystal ? this->m_crystal : crystal;
}

void bl::common::game::Resources::removeIridium(uint64_t iridium) {
	this->m_iridium -= iridium > this->m_iridium ? this->m_iridium : iridium;
}

void bl::common::game::Resources::removeAntiMatter(uint64_t antiMatter) {
	this->m_antiMatter -= antiMatter > this->m_antiMatter ? this->m_antiMatter : antiMatter;
}

void bl::common::game::Resources::removeEnergy(uint64_t energy) {
	this->m_energy -= energy > this->m_energy ? this->m_energy : energy;
}

nlohmann::json bl::common::game::Resources::serialize() const {
	nlohmann::json json;
	json["iron"] = this->m_iron;
	json["crystal"] = this->m_crystal;
	json["iridium"] = this->m_iridium;
	json["energy"] = this->m_energy;
	json["antiMatter"] = this->m_antiMatter;
	return json;
}

bl::common::pattern::ISerializable *bl::common::game::Resources::deserialize(nlohmann::json const &json) {
	this->m_iron = json["iron"];
	this->m_crystal = json["crystal"];
	this->m_iridium = json["iridium"];
	this->m_energy = json["energy"];
	this->m_antiMatter = json["antiMatter"];
	return this;
}

//TODO: check if correctly implemented
bool bl::common::game::Resources::operator<(const bl::common::game::Resources &rhs) const {
	if (m_iron < rhs.m_iron) {
		return true;
	}
	if (m_crystal < rhs.m_crystal) {
		return true;
	}
	if (m_iridium < rhs.m_iridium) {
		return true;
	}
	if (m_antiMatter < rhs.m_antiMatter) {
		return true;
	}
	return m_energy < rhs.m_energy;
}

bool bl::common::game::Resources::operator>(const bl::common::game::Resources &rhs) const {
	return rhs < *this;
}

bool bl::common::game::Resources::operator<=(const bl::common::game::Resources &rhs) const {
	return !(rhs < *this);
}

bool bl::common::game::Resources::operator>=(const bl::common::game::Resources &rhs) const {
	return !(*this < rhs);
}

bl::common::game::Resources &bl::common::game::Resources::operator-(const bl::common::game::Resources &rhs) {
	this->addIron(rhs.m_iron);
	this->addEnergy(rhs.m_energy);
	this->addCrystal(rhs.m_crystal);
	this->addAntiMatter(rhs.m_antiMatter);
	this->addIridium(rhs.m_iridium);
	return *this;
}

bl::common::game::Resources &bl::common::game::Resources::operator+(const bl::common::game::Resources &rhs) {
	this->removeIron(rhs.m_iron);
	this->removeEnergy(rhs.m_energy);
	this->removeCrystal(rhs.m_crystal);
	this->removeAntiMatter(rhs.m_antiMatter);
	this->removeIridium(rhs.m_iridium);
	return *this;
}

bl::common::game::Resources &bl::common::game::Resources::operator*(uint64_t fac) {
	/*if (fac == 0) {
		this->m_iron = 0;
		this->m_iridium = 0;
		this->m_antiMatter = 0;
		this->m_crystal = 0;
		this->m_energy = 0;
		return *this;
	}
	fac -= 1;
	this->addIron(this->m_iron * fac);
	this->addEnergy(this->m_energy * fac);
	this->addCrystal(this->m_crystal * fac);
	this->addAntiMatter(this->m_antiMatter * fac);
	this->addIridium(this->m_iridium * fac);
	 TODO: restore if addResource do additional check.
	 */
	this->m_iron *= fac;
	this->m_iridium *= fac;
	this->m_antiMatter *= fac;
	this->m_crystal *= fac;
	this->m_energy *= fac;
	return *this;
}

bl::common::game::Resources &bl::common::game::Resources::operator/(uint64_t fac) {
	this->m_iron /= fac;
	this->m_iridium /= fac;
	this->m_antiMatter /= fac;
	this->m_crystal /= fac;
	this->m_energy /= fac;
	return *this;
}
