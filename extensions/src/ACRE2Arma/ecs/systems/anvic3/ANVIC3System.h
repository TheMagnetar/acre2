#ifndef SRC_SYSTEMS_ANVIC3_ANVIC3SYSTEM_H_
#define SRC_SYSTEMS_ANVIC3_ANVIC3SYSTEM_H_

#include "../../components/Intercom.h"
#include "../../entt/entt.hpp"

#include "FFCSSystem.h"
#include "InfantryPhoneSystem.h"
#include "MCSSystem.h"

#include <string>
#include <vector>

namespace acre {
    namespace intercom {
        namespace anvic3 {
            class ANVIC3System {
            public:
                ANVIC3System();
                ~ANVIC3System();

                void create(ANVIC3 &vic3_, const std::string name, const IntercomType type_ = IntercomType::acreGeneric);
                void destroy(entt::registry &registry_, ANVIC3 &vic3_);

                std::vector<entt::entity> getIntercomSpeakers(const ANVIC3 &vic3_, entt::entity &player_);
                std::vector<std::string> getIntercomSpeakersId(entt::registry &registry_, const ANVIC3 &vic3_, entt::entity &player_);

                FFCSSystem          ffcs;
                MCSSystem           mcs;
                InfantryPhoneSystem infPhone;
            };
        } /* namespace anvic3 */
    } /* namespace intercom */
} /* namespace acre */


#endif /* SRC_SYSTEMS_ANVIC3_ANVIC3SYSTEM_H_ */

