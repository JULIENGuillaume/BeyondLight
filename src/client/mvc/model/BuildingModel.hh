//
// Created by diguie_t on 12/14/2017.
//

#ifndef BEYONDLIGHT_BUILDINGMODEL_HH
#define BEYONDLIGHT_BUILDINGMODEL_HH

#include "ABaseModel.hh"
#include "../../../common/game/Resources.hh"

namespace bl {
	namespace mvc {
		class BuildingModel : public ABaseModel {
		public:
			BuildingModel(std::shared_ptr<network::client::NetworkHandler> networkHandler, unsigned int id);
			void update() override;
			unsigned int getId() const;
			const std::string &getName() const;
			unsigned int getLevel() const;
			const common::game::Resources &getResourcesNeeded() const;
			bool incrLevel();
			const std::string &getDesc() const;
		private:
			unsigned int m_id;
			std::string m_name;
			std::string m_desc;
			unsigned int m_level;
			common::game::Resources m_resourcesNeeded;
		};
	}
}

#endif //BEYONDLIGHT_BUILDINGMODEL_HH
