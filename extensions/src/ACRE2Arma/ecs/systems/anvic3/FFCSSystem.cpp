#include "FFCSSystem.h"
#include "../../Types.h"

#include <iostream>

static const acre::float64_t volumeToKnob = 100 / 12.5;

acre::intercom::anvic3::FFCSSystem::FFCSSystem() {};
acre::intercom::anvic3::FFCSSystem::~FFCSSystem() {};

void acre::intercom::anvic3::FFCSSystem::createStation(ANVIC3 &vic3_, const std::string station_, const bool allowTurnedOut_, const bool connected_, const bool limited_) {

    // TODO: Switch to contains in C++20
    auto stationPos = vic3_.ffcs.find(station_);
    if (stationPos != vic3_.ffcs.end()) {
        return;
    }

    // Knobs
    vic3_.ffcs[station_].intercomKnob = limited_ ? FFCSIntercomKnob::ptt : FFCSIntercomKnob::live;
    vic3_.ffcs[station_].monitorKnob = 0;
    vic3_.ffcs[station_].workKnob = 0;
    vic3_.ffcs[station_].volumeKnob = connected_ ? static_cast<uint8_t>(volumeToKnob) : 0;

    vic3_.ffcs[station_].allowTurnedOut = allowTurnedOut_;
    vic3_.ffcs[station_].status = connected_ ? IntercomStatus::receiveTransmit : IntercomStatus::off;

    for (auto rack : vic3_.ffcs[station_].radioConfig) {
        rack = RadioConfig::noAccess;
    }

    // Initialise the player as null entity
    vic3_.ffcs[station_].player = entt::null;

    if (vic3_.ffcs.size() >= maxNumFFCS) {
        std::cerr << "Too many FFCS stations are added" << std::endl;
    }
}

void acre::intercom::anvic3::FFCSSystem::updatePlayer(ANVIC3 &vic3_, std::string &oldPosition_, std::string &newPosition_, entt::entity &player_) {

    if (newPosition_ != "") {
        // TODO: Switch to contains in C++20
        auto statioPos = vic3_.ffcs.find(newPosition_);
        if (statioPos == vic3_.ffcs.end()) {
            return;
        }

        vic3_.ffcs[newPosition_].player = player_;
    }

    if (oldPosition_ != "") {
        // TODO: Switch to contains in C++20
        auto statioPos = vic3_.ffcs.find(oldPosition_);
        if (statioPos == vic3_.ffcs.end()) {
            return;
        }

        vic3_.ffcs[oldPosition_].player = entt::null; // Null entity
    }
    
};

bool acre::intercom::anvic3::FFCSSystem::updateIntercomKnob(ANVIC3 &vic3_, const std::string &station_, const FFCSIntercomKnob intercomKnob_) {
    // TODO: Switch to contains in C++20
    auto stationPos = vic3_.ffcs.find(station_);
    if (stationPos == vic3_.ffcs.end()) {
        return false;
    }

    if (intercomKnob_ > FFCSIntercomKnob::override) {
        vic3_.ffcs[station_].intercomKnob = FFCSIntercomKnob::override;
    } else {
        vic3_.ffcs[station_].intercomKnob = intercomKnob_;
    }

    return true;
}

bool acre::intercom::anvic3::FFCSSystem::updateMonitorKnob(ANVIC3 &vic3_, const std::string &station_, const uint8_t monitorKnob_) {
    // TODO: Switch to contains in C++20
    auto stationPos = vic3_.ffcs.find(station_);
    if (stationPos == vic3_.ffcs.end()) {
        return false;
    }

    if (monitorKnob_ > ffcs_maxMonitor) {
        vic3_.ffcs[station_].monitorKnob = ffcs_maxMonitor;
    } else {
        vic3_.ffcs[station_].monitorKnob = monitorKnob_;
    }

    return true;
}

bool acre::intercom::anvic3::FFCSSystem::updateVolumeKnob(ANVIC3 &vic3_, const std::string &station_, const uint8_t volumeKnob_) {
    // TODO: Switch to contains in C++20
    auto stationPos = vic3_.ffcs.find(station_);
    if (stationPos == vic3_.ffcs.end()) {
        return false;
    }

    if (volumeKnob_ > ffcs_maxVolume) {
        vic3_.ffcs[station_].volumeKnob = ffcs_maxVolume;
    } else {
        vic3_.ffcs[station_].volumeKnob = volumeKnob_;
    }

    return true;
}

bool acre::intercom::anvic3::FFCSSystem::updateWorkKnob(ANVIC3 &vic3_, const std::string &station_, const uint8_t workKnob_) {
    // TODO: Switch to contains in C++20
    auto stationPos = vic3_.ffcs.find(station_);
    if (stationPos == vic3_.ffcs.end()) {
        return false;
    }

    if (workKnob_ > ffcs_maxWork) {
        vic3_.ffcs[station_].workKnob = ffcs_maxWork;
    } else {
        vic3_.ffcs[station_].workKnob = workKnob_;
    }

    return true;
}

std::vector<entt::entity> acre::intercom::anvic3::FFCSSystem::returnMonitorRack(ANVIC3 &vic3_, const std::string &station_) {
    std::vector<entt::entity> racks;

    // TODO: Switch to contains in C++20
    auto stationPos = vic3_.ffcs.find(station_);
    if (stationPos == vic3_.ffcs.end()) {
        return racks;
    } else if (vic3_.ffcs[station_].monitorKnob == 0) {
        return racks;
    } else if ((vic3_.ffcs[station_].monitorKnob != ffcs_maxMonitor)
               && canHearRadio(vic3_.ffcs[station_].radioConfig[vic3_.ffcs[station_].monitorKnob - 1])
               && (vic3_.racks[vic3_.ffcs[station_].monitorKnob - 1] != entt::null)) {
        racks.push_back(vic3_.racks[vic3_.ffcs[station_].monitorKnob - 1]);
    } else if ((vic3_.ffcs[station_].monitorKnob == ffcs_maxMonitor)) {
        uint8_t rackIdx = 0;
        for (auto rackIt : vic3_.racks) {
            if (rackIt != entt::null && canHearRadio(vic3_.ffcs[station_].radioConfig[rackIdx])) {
                racks.push_back(rackIt);
            }
            rackIdx++;
        }
    }

    return racks;
}

entt::entity acre::intercom::anvic3::FFCSSystem::returnWorkRack(ANVIC3 &vic3_, const std::string &station_) {
    // TODO: Switch to contains in C++20
    auto stationPos = vic3_.ffcs.find(station_);
    if (stationPos == vic3_.ffcs.end()) {
        return entt::null;
    } else {
        return canTransmitRadio(vic3_.ffcs[station_].radioConfig[vic3_.ffcs[station_].workKnob - 1]) ? vic3_.racks[vic3_.ffcs[station_].workKnob - 1] : entt::null;
    }
}

bool acre::intercom::anvic3::FFCSSystem::canHearRadio(const RadioConfig config_) {
    return (config_ == RadioConfig::receive) || (config_ == RadioConfig::receiveTransmit);
}

bool acre::intercom::anvic3::FFCSSystem::canTransmitRadio(const RadioConfig config_) {
    return (config_ == RadioConfig::transmit) || (config_ == RadioConfig::receiveTransmit);
}