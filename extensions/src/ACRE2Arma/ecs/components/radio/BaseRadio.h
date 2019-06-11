#ifndef SRC_COMPONENTS_RADIO_BASERADIO_H_
#define SRC_COMPONENTS_RADIO_BASERADIO_H_

#include "../../Types.h"

namespace acre {
    namespace radio {
        struct BaseRadio {
            RadioType    radioType;
            uint16_t     currentChannel;
            bool         poweredOn;
            bool         packRadio;
            bool         deployable;

            float32_t    sinad;
            float32_t    minSensitivity_dBm;
            float32_t    maxSensitivity_dBm;

            BaseRadio(const RadioType type, const uint16_t defaultChannel = 0, const bool isOn = false, const bool isPackRadio = false, const bool isDeployable = false,
                    const float32_t sinadRating = 1.0f, const float32_t minSensitivity = -116.0f, const float32_t maxSensitivity = -50.0f) :
                        radioType(type),
                        currentChannel(defaultChannel),
                        poweredOn(isOn),
                        packRadio(isPackRadio),
                        deployable(isDeployable),
                        sinad(sinadRating),
                        minSensitivity_dBm(minSensitivity),
                        maxSensitivity_dBm(maxSensitivity)
            {};
        };
    } /* namespace radio */
} /* namespace acre */



#endif /* SRC_COMPONENTS_RADIO_BASERADIO_H_ */
