#include "ANVIC3System.h"

#include "../rack/RackSystem.h"

#include "../../components/UniqueId.h"

acre::intercom::anvic3::ANVIC3System::ANVIC3System() {}


acre::intercom::anvic3::ANVIC3System::~ANVIC3System() {}

void acre::intercom::anvic3::ANVIC3System::create(ANVIC3 &vic3_, const std::string name_, const IntercomType type_) {
    vic3_.type = type_;
    vic3_.name = name_;

    for (uint8_t rackIdx = 0; rackIdx < maxNumRacks; rackIdx++) {
        vic3_.racks.push_back(entt::null);
    }
}

void acre::intercom::anvic3::ANVIC3System::destroy(entt::registry &registry_, ANVIC3 &vic3_) {
    // Delete all rack entities
    for (auto rack : vic3_.racks) {
        // acre::RackSystem::destroy(rack, registry_);
        registry_.destroy(rack);
    }
}

std::vector<entt::entity> acre::intercom::anvic3::ANVIC3System::getIntercomSpeakers(const ANVIC3 &vic3_, entt::entity &player_) {
    std::vector<entt::entity> speakers;

    auto playerPos = std::find_if(vic3_.ffcs.begin(), vic3_.ffcs.end(), [player_](const auto &station) { return station.second.player == player_;});
    if (playerPos == vic3_.ffcs.end()) {
        // Player not in intercom
        return speakers;
    } else if ((playerPos->second.volumeKnob == 0) || ((playerPos->second.status == IntercomStatus::off) || (playerPos->second.status == IntercomStatus::transmit))) {
        // Player with intercom disconnected
        return speakers;
    }

    for (auto station : vic3_.ffcs) {
        if ((station.second.player != entt::null) && (station.second.player != player_) &&
            ((station.second.status == IntercomStatus::transmit) || (station.second.status == IntercomStatus::receiveTransmit))) {
            speakers.push_back(station.second.player);
        }
    }

    if ((vic3_.infPhone.player != entt::null) && (vic3_.infPhone.connectedIntercoms[vic3_.infPhone.activeIntercom] == vic3_.name)) {
        speakers.push_back(vic3_.infPhone.player);
    }

    return speakers;
}

std::vector<std::string> acre::intercom::anvic3::ANVIC3System::getIntercomSpeakersId(entt::registry &registry_, const ANVIC3 &vic3_, entt::entity &player_) {
    const std::vector<entt::entity> speakers = getIntercomSpeakers(vic3_, player_);
    std::vector<std::string> speakersId;

    for (auto speaker : speakers) {
        UniqueId uid = registry_.get<UniqueId>(speaker);
        speakersId.push_back(uid.id);
    }
    
    return speakersId;
}