#include "RackController.h"
#include "RackSystem.h"

#include "../../components/Position.h"
#include "../../registry.h"

#include "controller.hpp"

#include <functional>

acre::rack::Controller::Controller() {
    acre::controller::get().add("registerRack", std::bind(&Controller::registerRack, this, std::placeholders::_1, std::placeholders::_2));
    acre::controller::get().add("unregisterRack", std::bind(&Controller::deleteRack, this, std::placeholders::_1, std::placeholders::_2));
}

acre::rack::Controller::~Controller() {}

bool acre::rack::Controller::registerRack(const arguments &args_, std::string &result_) {
    const std::string rackId = args_.as_string(0);
    Position position;
    position.pos.x = args_.as_float(1);
    position.pos.y = args_.as_float(2);
    position.pos.z = args_.as_float(3);

    position.dir = args_.as_float(4);

    entt::registry &registry = acre::Registry::get().getRegistry();
    entt::entity rack = acre::rack::System::get().create(rackId, position, registry);

    if (rack != entt::null) {
        result_ = "1";
        return true;
    } else {
        result_ = "0";
        return false;
    }
}

bool acre::rack::Controller::deleteRack(const arguments &args_, std::string &result_) {

    entt::registry &registry = acre::Registry::get().getRegistry();
    const std::string rackId = args_.as_string(0);

    acre::rack::System::get().destroy(rackId, registry);

    result_ = "1";
    return true;
}
