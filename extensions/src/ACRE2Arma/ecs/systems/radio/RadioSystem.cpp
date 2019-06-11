#include "RadioSystem.h"

#include "../../components/Position.h"
#include "../../components/Radio.h"
#include "../../components/UniqueId.h"

acre::radio::System::System() {}

acre::radio::System::~System() {}

entt::entity acre::radio::System::create(const std::string id_, const Position initialPos_, entt::registry &registry_) {
    entt::entity entity = registry_.create();
    registry_.assign<Position>(entity, initialPos_.pos, initialPos_.dir);
    registry_.assign<Radio>(entity);

    registry_.assign<UniqueId>(entity, id_);

    return entity;
}

entt::entity acre::radio::System::getById(const std::string &id_, entt::registry &registry_) {
    auto view = registry_.view<UniqueId, Radio>();

    auto it = std::find_if(view.begin(), view.end(), [view, id_](const auto &x) {return view.get<UniqueId>(x).id == id_; });

    return *it;
}

void acre::radio::System::destroy(const std::string &id_, entt::registry &registry_) {
    entt::entity radioEntity = getById(id_, registry_);

    destroy(radioEntity, registry_);
}

void acre::radio::System::destroy(entt::entity &radioEntity_, entt::registry &registry_) {

    registry_.destroy(radioEntity_);
}

std::string acre::radio::System::getRadioId(entt::entity &radioEntity_, entt::registry &registry_) {
    UniqueId radioId = registry_.get<UniqueId>(radioEntity_);

    return radioId.id;
}
