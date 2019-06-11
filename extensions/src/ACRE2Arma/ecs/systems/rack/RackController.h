#ifndef SRC_SYSTEMS_RACK_CONTROLLER_H_
#define SRC_SYSTEMS_RACK_CONTROLLER_H_

#include "RackSystem.h"
#include "dispatch.hpp"

namespace acre {
    namespace rack {
        class Controller : controller_module {
            Controller();
            ~Controller();

            bool registerRack(const arguments &args_, std::string &result_);
            bool deleteRack(const arguments &args_, std::string &result_);
        };
    } /* namespace vehicle */
} /* namespace acre */

#endif /* SRC_SYSTEMS_RACK_CONTROLLER_H_ */
