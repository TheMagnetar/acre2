#ifndef SRC_SYSTEMS_UNIT_UNITSYSTEM_H_
#define SRC_SYSTEMS_UNIT_UNITSYSTEM_H_

#include "../internal/Object.h"
#include "singleton.hpp"

namespace acre {
    namespace unit {
        class System : Object, public singleton<System> {
        public:
            System();
            ~System();

            entt::entity create(const std::string id_, const Position initialPos_, entt::registry &registry_) override;
            entt::entity getById(const std::string &id_, entt::registry &registry_) override;
            void destroy(const std::string &id_, entt::registry &registry_) override;
            void destroy(entt::entity &id_, entt::registry &registry_) override;
        };
    } /* namespace unit */
} /*  namespace acre */

#endif /* SRC_SYSTEMS_UNIT_UNITSYSTEM_H_ */
