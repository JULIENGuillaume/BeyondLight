//
// Created by diguie_t on 12/14/2017.
//

#ifndef BEYONDLIGHT_BUILDINGMODEL_HH
#define BEYONDLIGHT_BUILDINGMODEL_HH

#include "ABaseModel.hh"

namespace bl {
	namespace mvc {
		class BuildingModel : public ABaseModel {
		public:
			BuildingModel(std::shared_ptr<network::client::NetworkHandler> networkHandler, unsigned int id);
			void markForUpdate() override;
			bool needUpdate() override;
			void markToCommitChange() override;
			bool hasChange() override;
			unsigned int getId() const;
			const std::string &getName() const;
			unsigned int getLevel() const;
			unsigned int getIronNeeded() const;
			unsigned int getCrystalNeeded() const;
			unsigned int getIridiumNeeded() const;
			unsigned int getEnergyNeeded() const;
			bool incrLevel();
		private:
			void update();
			bool m_hasChange;
			bool m_needUpdate;
			unsigned int m_id;
			std::string m_name;
			unsigned int m_level;
			unsigned int m_ironNeeded;
			unsigned int m_crystalNeeded;
			unsigned int m_iridiumNeeded;
			unsigned int m_energyNeeded;
		};
	}
}

#endif //BEYONDLIGHT_BUILDINGMODEL_HH
