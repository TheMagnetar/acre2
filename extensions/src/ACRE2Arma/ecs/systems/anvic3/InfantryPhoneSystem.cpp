#include "InfantryPhoneSystem.h"

acre::intercom::anvic3::InfantryPhoneSystem::InfantryPhoneSystem() {}
acre::intercom::anvic3::InfantryPhoneSystem::~InfantryPhoneSystem() {}

void acre::intercom::anvic3::InfantryPhoneSystem::create(ANVIC3 &vic3_, const vector3_t position_, const std::vector<std::string> intercoms_) {
    vic3_.infPhone.position = position_;
    vic3_.infPhone.connectedIntercoms = intercoms_;

    vic3_.infPhone.activeIntercom = 0;
    vic3_.infPhone.ringing = false;
    vic3_.infPhone.player = entt::null;
}

void acre::intercom::anvic3::InfantryPhoneSystem::updatePlayer(ANVIC3 &vic3_, entt::entity &player_) {
    vic3_.mcs.player = player_;
}