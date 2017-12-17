//
// Created by Guillaume on 04/12/2017.
//

#ifndef BEYONDLIGHT_UPGRADECOST_HH
#define BEYONDLIGHT_UPGRADECOST_HH

#include "../../../common/pattern/ISerializable.hh"
#include "../../../common/game/Resources.hh"

namespace bl {
	namespace server {
		namespace game {
			namespace resource {
				class UpgradeCost : public common::pattern::ISerializable {
				public:
					explicit UpgradeCost(bool valid);
					explicit UpgradeCost(
								const bl::common::game::Resources &resources,
								uint64_t upgradeTime
						);
					virtual ~UpgradeCost() = default;
				public:
					bool isValid() const;
					bool launchUpgrade(bl::common::game::Resources &stock) const;
				public:
					nlohmann::json serialize() const override;
					common::pattern::ISerializable *deserialize(nlohmann::json const &json) override;
				private:
					bool m_validity;
					common::game::Resources m_resources;
					uint64_t m_upgradeTime;
				};
			}
		}
	}
}

#endif //BEYONDLIGHT_UPGRADECOST_HH
