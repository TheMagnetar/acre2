#ifndef SRC_COMPONENTS_AUXILIARY_CONNECTOR_H_
#define SRC_COMPONENTS_AUXILIARY_CONNECTOR_H_

#include "../../entt/entt.hpp"

#include <cstdint>
#include <string>
#include <memory>

namespace acre {
    namespace radio {
        enum class ConnectorType : uint8_t {
            bnc,
            c3_8,
            c18Pin, // 18pin for the 148 Side connector (Rack)
            c26Pin, // Harris 26 AIC pin - 117F to VRC103 (Rack)
            c32Pin, // Harris 152 side connector (Rack)
            c57Pin, // 57pin is the SEM70/80/90 interconnecting connector (Rack)
            mc2127,
            tnc,
            u283
        };

        struct Connector {

            ConnectorType type;
            std::string   description;
            std::shared_ptr<void *> component;
        };
    } /* namespace radio */
} /* namespace acre */



#endif /* SRC_COMPONENTS_AUXILIARY_CONNECTOR_H_ */
