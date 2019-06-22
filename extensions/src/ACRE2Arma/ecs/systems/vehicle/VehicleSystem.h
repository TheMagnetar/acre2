#ifndef SRC_SYSTEMS_VEHICLE_VEHICLESYSTEM_H_
#define SRC_SYSTEMS_VEHICLE_VEHICLESYSTEM_H_

#include "../internal/Object.h"
#include "singleton.hpp"

namespace acre {
    namespace vehicle {
        class System : Object, public singleton<System> {
        public:
            System();
            ~System();

            entt::entity create(const std::string id_, const Position initialPos_, entt::registry &registry_) final;
            entt::entity getById(const std::string &id_, entt::registry &registry_) final;
            void destroy(const std::string &id_, entt::registry &registry_) final;
            void destroy(entt::entity &id_, entt::registry &registry_) final;
        };
    } /* namespace vehicle */
} /* namespace acre */

#endif /* SRC_SYSTEMS_VEHICLE_VEHICLESYSTEM_H_ */
