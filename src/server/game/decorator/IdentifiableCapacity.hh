//
// Created by Guillaume Julien on 05/02/2018.
//

#ifndef BEYONDLIGHT_NUMERICALID_HH
#define BEYONDLIGHT_NUMERICALID_HH

#include <string>
#include <ISerializable.hh>

namespace bl {
	namespace server {
		namespace game {
			namespace decorator {
				class IdentifiableCapacity : public virtual common::pattern::ISerializable {
				public:
					IdentifiableCapacity(
							int id = -1,
							const std::string &name = "",
							const std::string &description = ""
					);
					~IdentifiableCapacity() override = default;
				public:
					int getId() const;
					void setId(int id);
					const std::string &getName() const;
					void setName(const std::string &name);
					const std::string &getDescription() const;
					void setDescription(const std::string &description);
					nlohmann::json serialize() const override;
					ISerializable *deserialize(nlohmann::json const &json) override;
				protected:
					int m_id;
					std::string m_name;
					std::string m_description;
				};
			}
		}
	}
}

#endif //BEYONDLIGHT_NUMERICALID_HH
