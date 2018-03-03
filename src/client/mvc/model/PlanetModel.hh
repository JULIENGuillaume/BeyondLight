//
// Created by diguie_t on 3/3/2018.
//

#ifndef BEYONDLIGHT_PLANETMODEL_HH
#define BEYONDLIGHT_PLANETMODEL_HH

#include "../../../common/game/Resources.hh"

namespace bl {
	namespace mvc {
		class PlanetModel : public ABaseModel {
		public:
			PlanetModel(std::shared_ptr<network::client::ClientNetworkHandler> networkHandler, unsigned int id);
			void update() override;
			unsigned int getPosition() const;
			const std::string &getOwnerUserName() const;
			bool isAttackable() const;
			const common::game::Resources &getResources() const;
		private:
			unsigned int m_position;
			std::string m_ownerUserName; // todo add user model ?
			bool m_attackable;
			common::game::Resources m_resources;
		};
	}
}

#endif //BEYONDLIGHT_PLANETMODEL_HH
