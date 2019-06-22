#ifndef SRC_SYSTEMS_VEHICLE_CONTROLLER_H_
#define SRC_SYSTEMS_VEHICLE_CONTROLLER_H_

#include "VehicleSystem.h"
#include "dispatch.hpp"

namespace acre {
    namespace vehicle {
        class Controller : public controller_module {
        public:
            Controller();
            ~Controller();

            bool registerVehicle(const arguments &args_, std::string &result_);
            bool deleteVehicle(const arguments &args_, std::string &result_);
        };
    } /* namespace vehicle */
} /* namespace acre */

#endif /* SRC_SYSTEMS_VEHICLE_CONTROLLER_H_ */
