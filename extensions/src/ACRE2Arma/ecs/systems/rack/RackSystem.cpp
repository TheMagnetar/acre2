#include "RackSystem.h"

#include  "../radio/RadioSystem.h"

#include "../../components/Position.h"
#include "../../components/Rack.h"
#include "../../components/UniqueId.h"


acre::rack::System::System() {}

acre::rack::System::~System() {}

entt::entity acre::rack::System::create(const std::string id_, const Position initialPos_, entt::registry &registry_) {
    entt::entity entity = registry_.create();
    registry_.assign<Position>(entity, initialPos_.pos, initialPos_.dir);
    registry_.assign<Rack>(entity);

    registry_.assign<UniqueId>(entity, id_);

    return entity;
}

entt::entity acre::rack::System::getById(const std::string &id_, entt::registry &registry_) {
    auto view = registry_.view<UniqueId, Rack>();

    auto it = std::find_if(view.begin(), view.end(), [view, id_](const auto &x) {return view.get<UniqueId>(x).id == id_; });

    return *it;
}

void acre::rack::System::destroy(const std::string &id_, entt::registry &registry_) {
    entt::entity rackEntity = getById(id_, registry_);

    destroy(rackEntity, registry_);
}

void acre::rack::System::destroy(entt::entity &rackEntity_, entt::registry &registry_) {

    Rack rack = registry_.get<Rack>(rackEntity_);

    if (rack.mountedRadio != entt::null) {
        radio::System::get().destroy(rack.mountedRadio, registry_);
    }

    registry_.destroy(rackEntity_);
}

bool acre::rack::System::mountRadio(const std::string &rackId_, std::string &radioId_, entt::registry &registry_) {
    return true;
}

bool acre::rack::System::unmountRadio(const std::string &rackId_, entt::registry &registry_) {
    return true;
}

std::string acre::rack::System::getMountedRadioId(const std::string &rackId_, entt::registry &registry_) {
    entt::entity rackEntity = getById(rackId_, registry_);

    Rack rack = registry_.get<Rack>(rackEntity);
    entt::entity radio = rack.mountedRadio;

    if (radio == entt::null) {
        return "";
    }

    return radio::System::get().getRadioId(radio, registry_);
}

entt::entity acre::rack::System::getMountedRadio(const std::string &rackId_, entt::registry &registry_) {
    entt::entity rackEntity = getById(rackId_, registry_);
    
    Rack rack = registry_.get<Rack>(rackEntity);
    return rack.mountedRadio;
}
