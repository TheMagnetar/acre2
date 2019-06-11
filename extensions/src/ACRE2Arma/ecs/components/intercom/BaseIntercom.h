#ifndef SRC_COMPONENTS_INTERCOM_BASEINTERCOM_H_
#define SRC_COMPONENTS_INTERCOM_BASEINTERCOM_H_

#include "../../Types.h"
#include "../../entt/entt.hpp"

#include <vector>

namespace acre {
    namespace intercom {
        struct BaseIntercom {
            IntercomType              type;                // Intercom type
            std::string               name;                // Unique name
            std::vector<entt::entity> racks;               // Connected racks
            std::vector<std::string>  connectedIntercoms;  // Interconnected intercoms

            BaseIntercom(const std::string intercomName, IntercomType intercomType = IntercomType::acreGeneric) :
                type(intercomType),
                name(intercomName){};
        };
    } /* namespace intercom */
} /* namespace acre */



#endif /* SRC_COMPONENTS_INTERCOM_BASEINTERCOM_H_ */
