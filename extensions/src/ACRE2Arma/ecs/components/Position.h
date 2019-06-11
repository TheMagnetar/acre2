#ifndef SRC_COMPONENTS_POSITION_H_
#define SRC_COMPONENTS_POSITION_H_

#include "../entt/entt.hpp"
#include "../Types.h"

struct Position {
    acre::vector3_t pos;
    acre::float32_t dir;
};

#endif /* SRC_COMPONENTS_POSITION_H_ */
