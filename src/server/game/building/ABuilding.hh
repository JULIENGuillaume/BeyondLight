//
// Created by Guillaume on 04/12/2017.
//

#ifndef BEYONDLIGHT_ABUILDING_HH
#define BEYONDLIGHT_ABUILDING_HH

#include "IBuilding.hh"

namespace server {
	namespace game {
		namespace building {
			class ABuilding : public IBuilding {
			public:
				ABuilding(int id,
				          std::string const &name,
				          std::string const &desc,
				          std::vector<resource::UpgradeCost> const &upgrades);
				~ABuilding() override = default;

			public:
				nlohmann::json serialize() const override;
				ISerializable *deserialize(nlohmann::json const &json) override;
				const std::string &getName() const override;
				const std::string &getDescription() const override;
				const resource::UpgradeCost &getResources() const override;
				int getId() const override;
				int getLevel() const override;

			protected:
				int m_level = 0;
				int m_id = -1;
				bool m_upgrading = false;
				int m_upgradeTimeLeft = -1;
				std::string m_name = "";
				std::string m_desc = "";
				std::vector<resource::UpgradeCost> m_upgrades = {};
			};
		}
	}
}


#endif //BEYONDLIGHT_ABUILDING_HH
