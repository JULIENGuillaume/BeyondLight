//
// Created by Guillaume Julien on 14/12/2017.
//

#ifndef BEYONDLIGHT_UNIQUEOBJECT_HH
#define BEYONDLIGHT_UNIQUEOBJECT_HH

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace bl {
	namespace server {
		class UniqueObject {
		public:
			UniqueObject();
			UniqueObject(UniqueObject const&);
		public:
			boost::uuids::uuid const& getUuid() const;

		protected:
			boost::uuids::uuid m_uuid;
		};
	}
}

#endif //BEYONDLIGHT_UNIQUEOBJECT_HH
