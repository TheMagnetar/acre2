#ifndef SRC_COMPONENTS_INTERCOM_ANVIC3_H_
#define SRC_COMPONENTS_INTERCOM_ANVIC3_H_

#include "BaseIntercom.h"
#include "../../Types.h"

#include <string>
#include <unordered_map>
#include <array>

namespace acre {
    namespace intercom {
        namespace anvic3 {

            enum class FFCSIntercomKnob : uint8_t {
                ptt,
                live,
                vox,
                override
            };

            static const uint8_t maxNumFFCS = 6;
            static const uint8_t maxNumRacks = 6;

            struct FFCS { // Full-Functional-Crew-Station
                FFCSIntercomKnob           intercomKnob;
                uint8_t                    monitorKnob;
                uint8_t                    volumeKnob;
                uint8_t                    workKnob;

                bool                       allowTurnedOut;
                IntercomStatus             status;
                std::array<RadioConfig, maxNumFFCS> radioConfig;
                entt::entity               player;
            };

            struct MCS {  // Master Control Station
                bool         accentActive;
                bool         linesActive;
                std::string  accessStation;
                entt::entity player;
            };

            struct Speaker {
                vector3_t  position;
            };

            struct InfantryPhone {
                vector3_t                position;
                entt::entity             player;
                uint8_t                  activeIntercom;
                bool                     ringing;
                std::vector<std::string> connectedIntercoms;
            };

            struct ANVIC3 : BaseIntercom {
                std::unordered_map<std::string, struct FFCS> ffcs;
                struct MCS                  mcs;
                std::vector<struct Speaker> speaker;
                struct InfantryPhone        infPhone;
            };
        } /* namespace anvic3 */
    } /* namespace intercom */
} /* namespace acre */


#endif /* SRC_COMPONENTS_INTERCOM_ANVIC3_H_ */