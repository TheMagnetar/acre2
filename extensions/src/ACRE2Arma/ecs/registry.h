#ifndef SRC_REGISTRY_H_
#define SRC_REGISTRY_H_

#include "singleton.hpp"

#include "entt/entt.hpp"

namespace acre {
    class Registry : public singleton<Registry> {
    public:
        Registry();
        ~Registry();

        entt::registry& getRegistry() { return this->registry; };
    protected:
        entt::registry registry;
    };
} /* namespace acre */

#endif /* SRC_CONTROLLER_H_ */
