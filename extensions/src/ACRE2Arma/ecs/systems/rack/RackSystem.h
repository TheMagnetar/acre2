#ifndef SRC_SYSTEMS_RACK_RACKSYSTEM_H_
#define SRC_SYSTEMS_RACK_RACKSYSTEM_H_

#include "../internal/Object.h"
#include "singleton.hpp"

namespace acre {
    namespace rack {
        class System : Object, public singleton<System> {
        public:
            System();
            ~System();

            entt::entity create(const std::string id_, const Position initialPos_, entt::registry &registry_) override;
            entt::entity getById(const std::string &id_, entt::registry &registry_) override;
            void destroy(const std::string &id_, entt::registry &registry_) override;
            void destroy(entt::entity &rackEntity_, entt::registry &registry_) override;

            bool mountRadio(const std::string &rackId, std::string &radioId_, entt::registry &registry_);

            bool unmountRadio(const std::string &rackId, entt::registry &registry_);

            std::string getMountedRadioId(const std::string &rackId, entt::registry &registry_);
            entt::entity getMountedRadio(const std::string &rackId, entt::registry &registry_);
        };
    } /* namespace rack */
} /* namespace acre */

#endif /* SRC_SYSTEMS_RACK_RACKSYSTEM_H_ */
