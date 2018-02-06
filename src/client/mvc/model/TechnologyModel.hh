//
// Created by diguie_t on 12/14/2017.
//

#ifndef BEYONDLIGHT_TECHNOLOGYMODEL_HH
#define BEYONDLIGHT_TECHNOLOGYMODEL_HH

#include "ABaseModel.hh"
#include "../../../common/game/Resources.hh"
#include "../../../network/client/ClientNetworkHandler.hh"

namespace bl {
	namespace mvc {
		class TechnologyModel : public ABaseModel {
		public:
			TechnologyModel(std::shared_ptr<network::client::ClientNetworkHandler> networkHandler, unsigned int id);
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

#endif //BEYONDLIGHT_TECHNOLOGYMODEL_HH
