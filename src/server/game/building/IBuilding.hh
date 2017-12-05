//
// Created by Guillaume on 04/12/2017.
//

#ifndef BEYONDLIGHT_IBUILDING_HH
#define BEYONDLIGHT_IBUILDING_HH

#include <string>
#include <map>
#include "../../../common/pattern/ISerializable.hh"
#include "../resource/UpgradeCost.hh"

namespace server {
	namespace game {
		namespace building {
			class IBuilding : public common::pattern::ISerializable {
			public:
				virtual ~IBuilding() = default;

			public:
				virtual std::string const& getName() const = 0;
				virtual std::string const& getDescription() const = 0;
				virtual resource::UpgradeCost const& getResources() const = 0;

			public:
				virtual int getId() const = 0;
				virtual int getLevel() const = 0;

			public:
				virtual bool isUpgrading() const = 0;
				virtual int getFullUpgradeTime() const = 0;
				virtual int getTimeLeft() const = 0;
			};
		}
	}
}


#endif //BEYONDLIGHT_IBUILDING_HH
