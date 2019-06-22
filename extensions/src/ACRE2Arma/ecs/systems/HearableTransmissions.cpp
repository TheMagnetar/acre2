#include "HearableTransmissions.h"
#include "../components/Player.h"

acre::radio::HearableTransmissions::HearableTransmissions() {
    // TODO Auto-generated constructor stub

}

acre::radio::HearableTransmissions::~HearableTransmissions() {
    // TODO Auto-generated destructor stub
}

void acre::radio::HearableTransmissions::update(entt::registry &registry_, const entt::entity &unit_, const std::vector<entt::entity> &txRadios_) {

    Player player(registry_.get<Player>(unit_));

    for (auto rxRadio : player.radioList) {
        Radio currentRxRadio(registry_.get<Radio>(rxRadio));

        for (auto txRadio : txRadios_) {
            if (rxRadio == rxRadio) { // Do not consider the same radio
                break;
            }

            Radio currentTxRadio(registry_.get<Radio>(txRadio));

            if ((currentRxRadio.type == RadioType::anprc343) && (currentTxRadio.type == RadioType::anprc343)) {
                updatePrc343(registry_, rxRadio, txRadio);
            } else {

            }
        }
    }
}

void acre::radio::HearableTransmissions::updatePrc343(entt::registry &registry_, const entt::entity &rxRadioEntity_, const entt::entity &txRadioEntity_) {
    ANPRC343 rxRadio(registry_.get<ANPRC343>(rxRadioEntity_));
    ANPRC343 txRadio(registry_.get<ANPRC343>(txRadioEntity_));

    uint16_t rxChannel = rxRadio.currentChannel;
    uint16_t txChannel = txRadio.currentChannel;

    if (txRadio.channelData.at(txChannel).frequencyTx == rxRadio.channelData.at(rxChannel).frequencyRx) {
        // This is a hearable transmission
    }
}
