//
// Created by diguie_t on 11/26/2017.
//

#ifndef MVC_TEST_MODELHANDLER_HH
#define MVC_TEST_MODELHANDLER_HH

#include <unordered_map>
#include <memory>
#include <ClientNetworkHandler.hh>
#include "../DataHandler.hpp"
#include "ABaseModel.hh"

namespace bl {
	namespace mvc {
		class ModelHandler
				: public DataHandler<std::string, std::shared_ptr<ABaseModel>> {
		public:
			ModelHandler(std::shared_ptr<network::client::ClientNetworkHandler> networkHandler);

			template<typename Model>
			std::shared_ptr<Model> getModel(const std::string &name) {
				auto pair = this->getData(name);
				if (pair.first) {
					return (std::dynamic_pointer_cast<Model>(pair.second));
				}
				return (std::shared_ptr<Model>(nullptr));
			}

			template<typename IdType, typename ModelType>
			void addModel(const std::string &modelName, const IdType &id) {
				this->m_data.insert({modelName, std::shared_ptr<ABaseModel>(new ModelType(this->m_networkHandler, id))});
			}

		private:
			std::shared_ptr<network::client::ClientNetworkHandler> m_networkHandler;
		};
	}
}
#endif //MVC_TEST_MODELHANDLER_HH
