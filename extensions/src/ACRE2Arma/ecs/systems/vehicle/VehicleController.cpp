#include "VehicleController.h"
#include "VehicleSystem.h"

#include "../../components/Position.h"
#include "../../registry.h"

#include "controller.hpp"

#include <functional>

acre::vehicle::Controller::Controller() {
    acre::controller::get().add("registerVehicle", std::bind(&Controller::registerVehicle, this, std::placeholders::_1, std::placeholders::_2));
    acre::controller::get().add("unregisterVehicle", std::bind(&Controller::deleteVehicle, this, std::placeholders::_1, std::placeholders::_2));
}

acre::vehicle::Controller::~Controller() {}

bool acre::vehicle::Controller::registerVehicle(const arguments &args_, std::string &result_) {
    const std::string vehicleId = args_.as_string(0);
    Position position;
    position.pos.x = args_.as_float(1);
    position.pos.y = args_.as_float(2);
    position.pos.z = args_.as_float(3);

    position.dir = args_.as_float(4);

    std::shared_ptr<entt::registry> registry = acre::Registry::get().getRegistry();
    entt::entity vehicle = acre::vehicle::System::get().create(vehicleId, position, *registry);

    if (vehicle != entt::null) {
        result_ = "1";
        return true;
    } else {
        result_ = "0";
        return false;
    }

    return false;
}

bool acre::vehicle::Controller::deleteVehicle(const arguments &args_, std::string &result_) {

    std::shared_ptr<entt::registry> registry = acre::Registry::get().getRegistry();
    const std::string vehicleId = args_.as_string(0);

    acre::vehicle::System::get().destroy(vehicleId, *registry);

    result_ = "1";

    return true;
}
