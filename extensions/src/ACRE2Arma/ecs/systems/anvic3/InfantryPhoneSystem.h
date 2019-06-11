#ifndef SRC_SYSTEMS_ANVIC3_INFANTRYPHONESYSTEM_H_
#define SRC_SYSTEMS_ANVIC3_INFANTRYPHONESYSTEM_H_

#include "../../components/Intercom.h"
#include "../../entt/entt.hpp"

#include <string>

namespace acre {
    namespace intercom {
        namespace anvic3 {
            class InfantryPhoneSystem {
            public:
                InfantryPhoneSystem();
                ~InfantryPhoneSystem();

                void create(ANVIC3 &vic3_, const vector3_t position_, const std::vector<std::string> intercoms_);
                void updatePlayer(ANVIC3 &vic3_, entt::entity &player);
            };
        } /* namespace anvic3 */
    } /* namespace intercom */
} /* namespace acre */


#endif /* SRC_SYSTEMS_ANVIC3_INFANTRYPHONESYSTEM_H_ */