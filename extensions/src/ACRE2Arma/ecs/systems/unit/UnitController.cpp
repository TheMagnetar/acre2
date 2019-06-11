#include "UnitController.h"
#include "UnitSystem.h"

#include "../../components/Position.h"
#include "../../registry.h"

#include "controller.hpp"

#include <functional>

acre::unit::Controller::Controller() {
    acre::controller::get().add("registerUnit", std::bind(&Controller::registerUnit, this, std::placeholders::_1, std::placeholders::_2));
    acre::controller::get().add("unregisterUnit", std::bind(&Controller::deleteUnit, this, std::placeholders::_1, std::placeholders::_2));
}

acre::unit::Controller::~Controller() {}

bool acre::unit::Controller::registerUnit(const arguments &args_, std::string &result_) {
    const std::string unitId = args_.as_string(0);
    Position position;
    position.pos.x = args_.as_float(1);
    position.pos.y = args_.as_float(2);
    position.pos.z = args_.as_float(3);

    position.dir = args_.as_float(4);

    entt::registry &registry = acre::Registry::get().getRegistry();
    entt::entity unit = acre::unit::System::get().create(unitId, position, registry);

    if (unit != entt::null) {
        result_ = "1";
        return true;
    } else {
        result_ = "0";
        return false;
    }
}

bool acre::unit::Controller::deleteUnit(const arguments &args_, std::string &result_) {

    entt::registry &registry = acre::Registry::get().getRegistry();
    const std::string unitId = args_.as_string(0);

    acre::unit::System::get().destroy(unitId, registry);

    result_ = "1";
    return true;
}
