//
// Created by diguie_t on 12/14/2017.
//

#include "json.hpp"
#include "TechnologyModel.hh"
#include "../../../common/Toolbox.hh"
#include "../../../common/game/Resources.hh"

namespace bl {
	namespace mvc {
		TechnologyModel::TechnologyModel(
				std::shared_ptr<network::client::ClientNetworkHandler> networkHandler,
				unsigned int id
		) :
				ABaseModel::ABaseModel(networkHandler),
				m_id(id) {
			//this->update();
		}

		unsigned int TechnologyModel::getId() const {
			return m_id;
		}

		const std::string &TechnologyModel::getName() const {
			return m_name;
		}

		unsigned int TechnologyModel::getLevel() const {
			return m_level;
		}

		void TechnologyModel::update() {
			/*if (this->m_networkHandler.get()) {
				try {
					m_networkHandler->send(m_networkHandler->getApiHelper()->buildNewApiRequest(m_networkHandler->getApiHelper()->REQUEST_TECHNOLOGY_INFO,
																								std::to_string(m_id)));
					auto msg = this->m_networkHandler->getMessage();
					nlohmann::json building = nlohmann::json::parse(msg.getBody().message);
					std::cerr << "Technology: " << msg.getBody().message << std::endl;
					m_level = building["level"];
					m_name = building["name"];
					m_desc = building["description"];
					this->m_resourcesNeeded.deserialize(building["resourcesRequired"]["resources"]);
				} catch (std::exception &e) {
					std::cerr << "json parse error building " << e.what() << std::endl;
					return;
				}
			}*/
		}

		bool TechnologyModel::incrLevel() {
			std::cout << "Incr tech level" << std::endl;
			/*m_networkHandler->send(
					m_networkHandler->getApiHelper()->buildNewApiRequest(m_networkHandler->getApiHelper()->REQUEST_TECHNOLOGY_UPGRADE, std::to_string(m_id)));
			auto msg = this->m_networkHandler->getMessage();
			auto answers = bl::common::Toolbox::split(msg.getBody().message, ":");
			if (msg.getBody().type == network::server::SERVER_MESSAGE_TYPE_ANSWER_OK && answers[0] == std::to_string(this->m_id)) {
				this->m_level = static_cast<unsigned int>(std::stoi(answers[1]));
				return (true);
			} else {
				return (false);
			}**/
			return (true);
		}

		const common::game::Resources &TechnologyModel::getResourcesNeeded() const {
			return (this->m_resourcesNeeded);
		}

		const std::string &TechnologyModel::getDesc() const {
			return (this->m_desc);
		}
	}
}