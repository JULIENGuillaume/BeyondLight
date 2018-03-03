//
// Created by diguie_t on 3/3/2018.
//

#ifndef BEYONDLIGHT_SHIPMODEL_HH
#define BEYONDLIGHT_SHIPMODEL_HH

#include "ABaseModel.hh"
#include "../../../common/game/Resources.hh"

namespace bl {
	namespace mvc {
		class ShipModel : public ABaseModel {
		public:
			ShipModel(std::shared_ptr<network::client::ClientNetworkHandler> networkHandler, unsigned int id);
			void update() override;
			unsigned int getId() const;
			const std::string &getName() const;
			bool isUnlocked() const;
			const common::game::Resources &getResourcesNeeded() const;
			bool buildShip(unsigned int nbToBuild);
			unsigned int getQuantity() const;
			const std::string &getDesc() const;
		private:
			unsigned int m_id;
			std::string m_name;
			std::string m_desc;
			unsigned int m_quantity;
			bool m_unlocked;
			common::game::Resources m_resourcesNeeded;
		};
	}
}

#endif //BEYONDLIGHT_SHIPMODEL_HH
