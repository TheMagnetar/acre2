#ifndef SRC_SYSTEMS_OBJECT_H_
#define SRC_SYSTEMS_OBJECT_H_

#include "../../Types.h"
#include "../../entt/entt.hpp"

#include "../../components/Position.h"

namespace acre {
    class Object {
    public:
        Object();
        ~Object();

        void updatePosition(const Position pos_, entt::registry &registry_, const entt::entity &objectEntity_);

        virtual entt::entity create(const std::string id_, const Position initialPos_, entt::registry &registry_);
        virtual entt::entity getById(const std::string &id_, entt::registry &registry_);
        virtual void destroy(const std::string &id_, entt::registry &registry_);
        virtual void destroy(entt::entity &entity_, entt::registry &registry_);
    };
} /* namespace acre */

#endif /* SRC_SYSTEMS_OBJECT_H_ */
