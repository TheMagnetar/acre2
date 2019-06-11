#include "UnitSystem.h"

#include "../../components/Position.h"
#include "../../components/Player.h"
#include "../../components/UniqueId.h"
#include "../../components/Intercom.h"

#include "../rack/RackSystem.h"

acre::unit::System::System() {}

acre::unit::System::~System() {}

entt::entity acre::unit::System::create(const std::string id_, const Position initialPos_, entt::registry &registry_) {
    entt::entity entity = registry_.create();
    registry_.assign<Position>(entity, initialPos_.pos, initialPos_.dir);
    registry_.assign<Player>(entity);

    registry_.assign<UniqueId>(entity, id_);

    return entity;
}

entt::entity acre::unit::System::getById(const std::string &id_, entt::registry &registry_) {
    auto view = registry_.view<UniqueId, Player>();

    auto it = std::find_if(view.begin(), view.end(), [view, id_](const auto &x) {return view.get<UniqueId>(x).id == id_; });

    return *it;
}

void acre::unit::System::destroy(const std::string &id_, entt::registry &registry_) {
    entt::entity unit = getById(id_, registry_);

    destroy(unit, registry_);
}

void acre::unit::System::destroy(entt::entity &unit_, entt::registry &registry_) {
    registry_.destroy(unit_);
}
