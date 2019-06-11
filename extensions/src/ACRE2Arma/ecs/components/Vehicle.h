#ifndef SRC_COMPONENTS_VEHICLE_H_
#define SRC_COMPONENTS_VEHICLE_H_

#include "../entt/entt.hpp"

#include <vector>

struct Vehicle {
    std::vector<entt::entity> rackList;
};

#endif /* SRC_COMPONENTS_VEHICLE_H_ */
