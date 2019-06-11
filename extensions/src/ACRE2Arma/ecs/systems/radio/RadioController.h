#ifndef SRC_SYSTEMS_RADIO_CONTROLLER_H_
#define SRC_SYSTEMS_RADIO_CONTROLLER_H_

#include "RadioSystem.h"
#include "dispatch.hpp"

namespace acre {
    namespace radio {
        class Controller : controller_module {
            Controller();
            ~Controller();

            bool registerRadio(const arguments &args_, std::string &result_);
            bool deleteRadio(const arguments &args_, std::string &result_);
        };
    } /* namespace vehicle */
} /* namespace acre */

#endif /* SRC_SYSTEMS_RADIO_CONTROLLER_H_ */
