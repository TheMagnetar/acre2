#include "Object.h"

#include "../../components/Position.h"
#include "../../components/UniqueId.h"

#include <algorithm>

acre::Object::Object() {}
acre::Object::~Object() {}

entt::entity acre::Object::create(const std::string id_, const Position initialPos_, entt::registry &registry_) {
    auto entity = registry_.create();

    registry_.assign<Position>(entity, initialPos_.pos, initialPos_.dir);
    registry_.assign<UniqueId>(entity, id_);

    return entity;
}

entt::entity acre::Object::getById(const std::string &id_, entt::registry &registry_) {
    auto view = registry_.view<UniqueId>();

    auto it = std::find_if(view.begin(), view.end(), [view, id_](const auto &x) {return view.get(x).id == id_;});

    return *it;
}

void acre::Object::updatePosition(const Position pos_, entt::registry &registry_, const entt::entity &objectEntity_) {
    Position pos(registry_.get<Position>(objectEntity_));
    pos = pos_;
}

void acre::Object::updatePosition(const ACRE_VECTOR pos_, const ACRE_VECTOR dir_, entt::registry &registry_, const entt::entity &objectEntity_) {
    Position posInfo(registry_.get<Position>(objectEntity_));

    posInfo.pos.x = pos_.x;
    posInfo.pos.y = pos_.y;
    posInfo.pos.z = pos_.z;



}

void acre::Object::destroy(const std::string &id_, entt::registry &registry_) {
    auto object = getById(id_, registry_);
    registry_.destroy(object);
}

void acre::Object::destroy(entt::entity &object_, entt::registry &registry_) {
    registry_.destroy(object_);
}
