#ifndef SRC_SYSTEMS_ANVIC3_FFCSSYSTEM_H_
#define SRC_SYSTEMS_ANVIC3_FFCSSYSTEM_H_

#include "../../components/Intercom.h"
#include "../../entt/entt.hpp"

namespace acre {
    namespace intercom {
        namespace anvic3 {
            class FFCSSystem {
            public:
                FFCSSystem();
                ~FFCSSystem();

                // Maximum positions
                static const uint8_t ffcs_maxMonitor = 6;
                static const uint8_t ffcs_maxVolume = 10;
                static const uint8_t ffcs_maxWork = 7;

                // Creation
                void createStation(ANVIC3 &vic3_, const std::string station_, const bool allowTurnedOut_ = true, const bool connected_ = true, const bool limited_ = false);
                void updatePlayer(ANVIC3 &vic3_, std::string &oldPosition_, std::string &newPosition_, entt::entity &player_);

                // Knobs
                bool updateIntercomKnob(ANVIC3 &vic3, const std::string &station, const FFCSIntercomKnob _newPos);
                bool updateMonitorKnob(ANVIC3 &vic3, const std::string &station, const uint8_t _newPos);
                bool updateVolumeKnob(ANVIC3 &vic3, const std::string &station, const uint8_t _newPos);
                bool updateWorkKnob(ANVIC3 &vic3, const std::string &station, const uint8_t _newPos);

                // Racks
                std::vector<entt::entity> returnMonitorRack(ANVIC3 &vic3, const std::string &station);
                entt::entity returnWorkRack(ANVIC3 &vic3, const std::string &station);

            private:
                bool canHearRadio(const RadioConfig config_);
                bool canTransmitRadio(const RadioConfig config_);
            };
        } /* namespace anvic3 */
    } /* namespace intercom */
} /* namespace acre */


#endif /* SRC_SYSTEMS_ANVIC3_FFCSSYSTEM_H_ */

