#ifndef SRC_COMPONENTS_RADIO_ANPRC343_H_
#define SRC_COMPONENTS_RADIO_ANPRC343_H_

#include "../../entt/entt.hpp"
#include "../../Types.h"
#include "BaseRadio.h"
#include "../auxiliary/Connector.h"

#include <vector>

namespace acre {
    namespace radio {
        struct SimpleChannel {
            float32_t frequencyRx;
            float32_t frequencyTx;
        };

        struct ANPRC343 : BaseRadio {
            float32_t power_mW;
            std::vector<SimpleChannel> channelData;

            ANPRC343(const uint8_t preset = 0, const float32_t power = 500.0f) :
                    BaseRadio(RadioType::anprc343), power_mW(power) {

                float32_t baseFrequency = 0.0f;
                switch (preset) {
                    case 0: {
                        baseFrequency = 2400.0f;
                        break;
                    }
                    case 1: {
                        baseFrequency = 2410.0f;
                        break;
                    }
                    case 2: {
                        baseFrequency = 2420.0f;
                        break;
                    }
                    case 3: {
                        baseFrequency = 2430.0f;
                        break;
                    }
                    default: {
                        baseFrequency = 2400.0f;
                    }
                }

                for (uint16_t channel = 0u; channel < 256u; channel++) {
                    const float32_t jumpFrequency = 0.01f;
                    const float32_t frequency = baseFrequency + (jumpFrequency*static_cast<float32_t>(channel));
                    channelData.push_back({frequency, frequency});
                }
            }
        };
    } /* namespace radio */
} /* namespace acre */

#endif /* SRC_COMPONENTS_RADIO_ANPRC343_H_ */
