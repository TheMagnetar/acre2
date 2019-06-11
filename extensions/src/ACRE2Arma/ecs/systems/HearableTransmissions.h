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

            void update(entt::registry &registry, const entt::entity &radioEntity);
        private:
            void updatePrc343(entt::registry &registry);
        };
    } /* namespace radio */
} /* namespace acre */

#endif /* SRC_SYSTEMS_HEARABLETRANSMISSIONS_H_ */
