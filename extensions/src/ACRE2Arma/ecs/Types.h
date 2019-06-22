#ifndef SRC_TYPES_H_
#define SRC_TYPES_H_

#include <cstdint>
#include <cmath>
#include <map>

namespace acre {
    /*
     * Basic type definitions
     */
    typedef float_t  float32_t;
    typedef double_t float64_t;

    typedef struct {
        float32_t x;
        float32_t y;
        float32_t z;
    } vector3_t;

    namespace intercom {
        enum class IntercomType : uint8_t {
            acreGeneric,
            anvic3
        };

        enum class IntercomStatus : uint8_t {
            off,
            receive,
            transmit,
            receiveTransmit
        };

        enum class RadioConfig : uint8_t {
            noAccess,
            receive,
            transmit,
            receiveTransmit
        };
    } /* namespace intercom */

    namespace radio {
        enum class Modulation : uint8_t {
            am,
            fm
        };

        enum class SelectiveCalling : uint8_t {
            none,
            cdcss,
            ctcss,
            selCall,
            xtcss
        };

        enum class TransmittingMode : uint8_t {
            plain,
            encrypted,
            sincgars,
            sem70AKW
        };

        enum class Waveform : uint8_t {
            vulos,
            havequick,
            sincgars,
            hpw,
            p25
        };

        enum class CryptoMode : uint8_t {
            none,
            kg84,
            andvt,
            aes,
            fascinator,
            vinson,
            satellite,
            des
        };

        enum class KeyType : uint8_t {
            tek,
            kek,
            Hopset,
            Lockout,
            tsk,
            tek3
        };

        enum class RadioType : uint8_t {
            generic,
            anprc77,
            anprc117f,
            anprc148,
            anprc152,
            anprc343,
            sem52sl,
            sem70
        };

        static const std::map<RadioType, std::string> RadioType2Name = {
            {RadioType::generic,   "ACRE Radio" },
            {RadioType::anprc77,   "AN/PRC-77"  },
            {RadioType::anprc117f, "AN/PRC-117f"},
            {RadioType::anprc148,  "AN/PRC-158" },
            {RadioType::anprc152,  "AN/PRC-152" },
            {RadioType::sem52sl,   "SEM 52 SL"  },
            {RadioType::sem70,     "SEM 70"     }
        };
    } /* namespace radio */

    namespace rack {
        enum class RackType : uint8_t {
            generic,
            anvrc64,
            anvrc103,
            anvrc110,
            anvrc111,
            sem90
        };

        static const std::map<RackType, std::string> RackType2Name = {
            {RackType::generic,  "ACRE Rack" },
            {RackType::anvrc64,  "AN/VRC-64" },
            {RackType::anvrc103, "AN/VRC-103"},
            {RackType::anvrc110, "AN/VRC-110"},
            {RackType::anvrc111, "AN/VRC-111"},
            {RackType::sem90,    "SEM 90"    }
        };
    } /* namespace rack */
} /* namespace acre */

#endif /* SRC_TYPES_H_ */
