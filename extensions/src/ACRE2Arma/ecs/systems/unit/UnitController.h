#ifndef SRC_SYSTEMS_UNIT_CONTROLLER_H_
#define SRC_SYSTEMS_UNIT_CONTROLLER_H_

#include "UnitSystem.h"
#include "dispatch.hpp"

namespace acre {
    namespace unit {
        class Controller : public controller_module {
        public:
            Controller();
            ~Controller();

            bool registerUnit(const arguments &args_, std::string &result_);
            bool deleteUnit(const arguments &args_, std::string &result_);
        };
    } /* namespace vehicle */
} /* namespace acre */

#endif /* SRC_SYSTEMS_UNIT_CONTROLLER_H_ */
