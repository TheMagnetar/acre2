#include "MCSSystem.h"

acre::intercom::anvic3::MCSSystem::MCSSystem() {}

acre::intercom::anvic3::MCSSystem::~MCSSystem() {}

void acre::intercom::anvic3::MCSSystem::create(ANVIC3 &vic3_, const std::string accessStation_, const bool accent_, const bool lines_) {
    auto stationPos = vic3_.ffcs.find(accessStation_);
    if (stationPos != vic3_.ffcs.end()) {
        return;
    }

    vic3_.mcs.accessStation = accessStation_;
    vic3_.mcs.accentActive = accent_;
    vic3_.mcs.linesActive = lines_;

    vic3_.mcs.player = entt::null;
}

void acre::intercom::anvic3::MCSSystem::updatePlayer(ANVIC3 &vic3_, entt::entity &player_) {
    vic3_.mcs.player = player_;
}