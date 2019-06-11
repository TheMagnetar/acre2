#include "RadioController.h"
#include "RadioSystem.h"

#include "../../components/Position.h"
#include "../../registry.h"

#include "controller.hpp"

#include <functional>

acre::radio::Controller::Controller() {
    acre::controller::get().add("registerRadio", std::bind(&Controller::registerRadio, this, std::placeholders::_1, std::placeholders::_2));
    acre::controller::get().add("unregisterRadio", std::bind(&Controller::deleteRadio, this, std::placeholders::_1, std::placeholders::_2));
}

acre::radio::Controller::~Controller() {}

bool acre::radio::Controller::registerRadio(const arguments &args_, std::string &result_) {
    const std::string unitId = args_.as_string(0);
    Position position;
    position.pos.x = args_.as_float(1);
    position.pos.y = args_.as_float(2);
    position.pos.z = args_.as_float(3);

    position.dir = args_.as_float(4);

    entt::registry &registry = acre::Registry::get().getRegistry();
    entt::entity radio = acre::radio::System::get().create(unitId, position, registry);

    if (radio != entt::null) {
        result_ = "1";
        return true;
    } else {
        result_ = "0";
        return false;
    }
}

bool acre::radio::Controller::deleteRadio(const arguments &args_, std::string &result_) {

    entt::registry &registry = acre::Registry::get().getRegistry();
    const std::string radioId = args_.as_string(0);

    acre::radio::System::get().destroy(radioId, registry);

    result_ = "1";
    return true;
}
