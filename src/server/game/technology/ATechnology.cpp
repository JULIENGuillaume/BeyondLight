//
// Created by Guillaume on 06/02/2018.
//

#include <unordered_set>
#include <unordered_map>
#include "ATechnology.hh"

bl::server::game::technology::ATechnology::ATechnology(
		int id,
		std::string const &name,
		std::string const &desc,
		std::unordered_set<int> const &researchDependencies,
		const std::unordered_map<int, int> &buildingsDependencies,
		uint64_t researchTime
) {
	this->m_id = id;
	this->m_name = name;
	this->m_description = desc;
	this->m_researchTime = researchTime;
	this->m_researchDependencies = researchDependencies;
	this->m_buildingDependencies = buildingsDependencies;
}

uint64_t bl::server::game::technology::ATechnology::getResearchTime() {
	return this->m_researchTime;
}

nlohmann::json bl::server::game::technology::ATechnology::serialize() const {
	return decorator::IdentifiableCapacity::serialize();
}

bl::common::pattern::ISerializable *bl::server::game::technology::ATechnology::deserialize(nlohmann::json const &json) {
	return decorator::IdentifiableCapacity::deserialize(json);
}
