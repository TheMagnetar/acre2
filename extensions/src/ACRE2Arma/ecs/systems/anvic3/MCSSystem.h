#ifndef SRC_SYSTEMS_ANVIC3_MCSSYSTEM_H_
#define SRC_SYSTEMS_ANVIC3_MCSSYSTEM_H_

#include "../../components/Intercom.h"
#include "../../entt/entt.hpp"

#include <string>

namespace acre {
    namespace intercom {
        namespace anvic3 {
            class MCSSystem {
            public:
                MCSSystem();
                ~MCSSystem();

                void create(ANVIC3 &vic3_, const std::string accessStation_, const bool accent_ = true, const bool lines_ = true);
                void updatePlayer(ANVIC3 &vic3_, entt::entity &player);
            };
        } /* namespace anvic3 */
    } /* namespace intercom */
} /* namespace acre */


#endif /* SRC_SYSTEMS_ANVIC3_MCSSYSTEM_H_ */