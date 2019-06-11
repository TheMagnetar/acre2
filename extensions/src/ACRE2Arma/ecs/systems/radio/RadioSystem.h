#ifndef SRC_SYSTEMS_RACK_RADIOSYSTEM_H_
#define SRC_SYSTEMS_RACK_RADIOSYSTEM_H_

#include "../internal/Object.h"
#include "singleton.hpp"

namespace acre {
    namespace radio {
        class System : Object, public singleton<System> {
        public:
            System();
            ~System();

            entt::entity create(const std::string id_, const Position initialPos_, entt::registry &registry_) override;
            entt::entity getById(const std::string &id_, entt::registry &registry_) override;
            void destroy(const std::string &id_, entt::registry &registry_) override;
            void destroy(entt::entity &rackEntity_, entt::registry &registry_) override;

            std::string getRadioId(entt::entity &radioEntity_, entt::registry &registry_);
        };
    } /* namespace radio */
} /* namespace acre */

#endif /* SRC_SYSTEMS_RACK_RADIOSYSTEM_H_ */
