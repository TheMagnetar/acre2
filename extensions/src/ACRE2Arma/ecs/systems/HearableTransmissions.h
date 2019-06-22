#ifndef SRC_SYSTEMS_HEARABLETRANSMISSIONS_H_
#define SRC_SYSTEMS_HEARABLETRANSMISSIONS_H_

#include "../components/Radio.h"
#include "../entt/entt.hpp"
#include "../Types.h"

namespace acre {
    namespace radio {
        class HearableTransmissions {
        public:
            HearableTransmissions();
            virtual ~HearableTransmissions();

            void update(entt::registry &registry_, const entt::entity &unit_, const std::vector<entt::entity> &txRadios_);
        private:
            void updatePrc343(entt::registry &registry_, const entt::entity &rxRadioEntity_, const entt::entity &txRadioEntity_);
        };
    } /* namespace radio */
} /* namespace acre */

#endif /* SRC_SYSTEMS_HEARABLETRANSMISSIONS_H_ */
