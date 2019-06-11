#include "HearableTransmissions.h"

acre::radio::HearableTransmissions::HearableTransmissions() {
    // TODO Auto-generated constructor stub

}

acre::radio::HearableTransmissions::~HearableTransmissions() {
    // TODO Auto-generated destructor stub
}

void acre::radio::HearableTransmissions::update(entt::registry &registry, const entt::entity &radioEntity) {

    ANPRC343 currentRadio(registry.get<ANPRC343>(radioEntity));

    auto view = registry.view<Radio, ANPRC343>();
    for (auto remoteRadioEntity: view) {
        if (remoteRadioEntity != radioEntity) { // Do not consider the same radio
            ANPRC343 remoteRadio(view.get<ANPRC343>(remoteRadioEntity));
            uint16_t rxChannel = currentRadio.currentChannel;
            uint16_t txChannel = remoteRadio.currentChannel;

            if (remoteRadio.channelData.at(txChannel).frequencyTx == currentRadio.channelData.at(rxChannel).frequencyRx) {
                // This is a hearable transmission
            }
        }
    }
}
