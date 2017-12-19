//
// Created by diguie_t on 12/19/2017.
//

#ifndef BEYONDLIGHT_RESOURCESMODEL_HH
#define BEYONDLIGHT_RESOURCESMODEL_HH

#include "boost/uuid/uuid_io.hpp"
#include "../../../common/game/Resources.hh"
#include "ABaseModel.hh"

namespace bl {
	namespace mvc {
		class ResourcesModel : public ABaseModel  {
		public:
			ResourcesModel(std::shared_ptr<network::client::NetworkHandler> networkHandler, const boost::uuids::uuid &uuid);
			void update() override;
			const common::game::Resources &getResources() const;
		private:
			common::game::Resources m_resources;
			boost::uuids::uuid m_uuid;
		};
	}
}

#endif //BEYONDLIGHT_RESOURCESMODEL_HH
