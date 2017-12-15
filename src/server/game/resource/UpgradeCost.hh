//
// Created by Guillaume on 04/12/2017.
//

#ifndef BEYONDLIGHT_UPGRADECOST_HH
#define BEYONDLIGHT_UPGRADECOST_HH

#include "../../../common/pattern/ISerializable.hh"

namespace bl {
	namespace server {
		namespace game {
			namespace resource {
				class UpgradeCost : public common::pattern::ISerializable {
				public:
					explicit UpgradeCost(bool valid);
					virtual ~UpgradeCost() = default;
				public:
					bool isValid() const;
					bool launchUpgrade() const;
				public:
					nlohmann::json serialize() const override;
					common::pattern::ISerializable *deserialize(nlohmann::json const &json) override;
				private:
					bool m_validity;
				};
			}
		}
	}
}

#endif //BEYONDLIGHT_UPGRADECOST_HH
