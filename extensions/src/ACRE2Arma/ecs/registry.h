#ifndef SRC_REGISTRY_H_
#define SRC_REGISTRY_H_

#include "singleton.hpp"
#include "entt/entt.hpp"

#include <memory>

namespace acre {
    class Registry : public singleton<Registry> {
    public:
        Registry() {
            this->registry = std::make_shared<entt::registry>();
        };
        ~Registry();

        std::shared_ptr<entt::registry> getRegistry() { return this->registry; };
    protected:
        std::shared_ptr<entt::registry> registry;
    };
} /* namespace acre */

#endif /* SRC_CONTROLLER_H_ */
