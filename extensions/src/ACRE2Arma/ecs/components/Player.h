#ifndef SRC_COMPONENTS_PLAYER_H_
#define SRC_COMPONENTS_PLAYER_H_

#include "../entt/entt.hpp"

#include <vector>

struct Player {
    std::vector<entt::entity> radioList;
};


#endif /* SRC_COMPONENTS_PLAYER_H_ */
