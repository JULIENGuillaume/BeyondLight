//
// Created by Guillaume Julien on 14/12/2017.
//

#ifndef BEYONDLIGHT_UNIQUEOBJECT_HH
#define BEYONDLIGHT_UNIQUEOBJECT_HH

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_serialize.hpp>
#include <boost/lexical_cast.hpp>
#include <ISerializable.hh>

namespace bl {
	namespace server {
		class UniqueObject : virtual public common::pattern::ISerializable {
		public:
			UniqueObject();
			UniqueObject(UniqueObject const&);
		public:
			boost::uuids::uuid const& getUuid() const;
			std::string getUuidAsString() const;
			nlohmann::json serialize() const override;
			ISerializable *deserialize(nlohmann::json const &json) override;

		protected:
			boost::uuids::uuid m_uuid;
		};
	}
}

#endif //BEYONDLIGHT_UNIQUEOBJECT_HH
