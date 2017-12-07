//
// Created by diguie_t on 11/26/2017.
//

#ifndef MVC_TEST_ICONTROLLERFACTORY_HH
#define MVC_TEST_ICONTROLLERFACTORY_HH

#include <memory>
#include "IBaseController.hh"
#include "../../WebCore.hh"

namespace bl {
	namespace mvc {
		class IControllerFactory {
		public:
			virtual ~IControllerFactory() {
			}

			virtual std::shared_ptr<IBaseController> build(WebCore *webCore) = 0;
		};
	}
}
#endif //MVC_TEST_ICONTROLLERFACTORY_HH
