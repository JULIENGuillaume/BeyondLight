//
// Created by Guillaume Julien on 05/02/2018.
//

#ifndef BEYONDLIGHT_UPGRADABLECAPACITY_HH
#define BEYONDLIGHT_UPGRADABLECAPACITY_HH

#include <ISerializable.hh>
#include "../resource/UpgradeCost.hh"

namespace bl {
	namespace server {
		namespace game {
			namespace decorator {
				class UpgradableCapacity : public virtual common::pattern::ISerializable{
				public:
					UpgradableCapacity(const std::vector<resource::UpgradeCost> &upgrades = {});
					virtual ~UpgradableCapacity() = default;
				public:
					int getLevel() const;
					void setLevel(int level);
					bool isUpgrading() const;
					void setUpgrading(bool upgrading);
					int getUpgradeTimeLeft() const;
					void setUpgradeTimeLeft(int upgradeTimeLeft);
				public:
					resource::UpgradeCost getUpgradeCost() const;
					virtual bool upgrade(common::game::Resources &stock);
					nlohmann::json serialize() const override;
					ISerializable *deserialize(nlohmann::json const &json) override;
				protected:
					int m_level = 0;
					bool m_upgrading = false;
					int m_upgradeTimeLeft = -1;
					std::vector<resource::UpgradeCost> m_upgrades = {};
				};
			}
		}
	}
}

#endif //BEYONDLIGHT_UPGRADABLECAPACITY_HH
