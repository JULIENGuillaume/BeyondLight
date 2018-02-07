//
// Created by Guillaume on 06/02/2018.
//

#ifndef BEYONDLIGHT_ATECHNOLOGY_HH
#define BEYONDLIGHT_ATECHNOLOGY_HH

#include <string>
#include <unordered_set>
#include "ITechnology.hh"

namespace bl {
	namespace server {
		namespace game {
			namespace technology {
				class ATechnology : public ITechnology{
				public:
					ATechnology(
							int id,
							std::string const &name,
							std::string const &desc,
							const std::unordered_set<int> &researchDependencies,
							const std::unordered_map<int, int> &buildingsDependencies,
							uint64_t researchTime
					);
					~ATechnology() override = default;
				public:
					uint64_t getResearchTime() override;
					nlohmann::json serialize() const override;
					ISerializable *deserialize(nlohmann::json const &json) override;
					bool isUnlockedByPlayer(user::User const &user) const override;
				protected:
					uint64_t m_researchTime = 0;
				};
			}
		}
	}
}

#endif //BEYONDLIGHT_ATECHNOLOGY_HH
