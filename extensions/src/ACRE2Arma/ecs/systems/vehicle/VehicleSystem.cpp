#include "VehicleSystem.h"

#include "../../components/Position.h"
#include "../../components/Vehicle.h"
#include "../../components/UniqueId.h"
#include "../../components/Intercom.h"

#include "../rack/RackSystem.h"

acre::vehicle::System::System() {}

acre::vehicle::System::~System() {}

entt::entity acre::vehicle::System::create(const std::string id_, const Position initialPos_, entt::registry &registry_) {
    entt::entity entity = registry_.create();
    registry_.assign<Position>(entity, initialPos_.pos, initialPos_.dir);
    registry_.assign<Vehicle>(entity);

    registry_.assign<UniqueId>(entity, id_);

    return entity;
}

entt::entity acre::vehicle::System::getById(const std::string &id_, entt::registry &registry_) {
    auto view = registry_.view<UniqueId, Vehicle>();

    auto it = std::find_if(view.begin(), view.end(), [view, id_](const auto &x) {return view.get<UniqueId>(x).id == id_;});

    return *it;
}

void acre::vehicle::System::destroy(const std::string &id_, entt::registry &registry_) {
    entt::entity vehicle = getById(id_, registry_);

    destroy(vehicle, registry_);
}

void acre::vehicle::System::destroy(entt::entity &vehicle_, entt::registry &registry_) {
    if (registry_.has<Intercom>(vehicle_)) {
        auto vehicleIntercoms = registry_.get<Intercom>(vehicle_);

        // Remove intercom racks
        for (auto intIdx : vehicleIntercoms.intercoms) {
            for (auto rackIdx : intIdx.racks) {
                rack::System::get().destroy(rackIdx, registry_);
            }
        }
    }

    // Remove now racks not connected to intercom
    auto vehicleInfo = registry_.get<Vehicle>(vehicle_);
    for (auto rackIdx : vehicleInfo.rackList) {
        rack::System::get().destroy(rackIdx, registry_);
    }

    // Delete the vehicle
    registry_.destroy(vehicle_);
}
