#ifndef SRC_COMPONENTS_RACK_H_
#define SRC_COMPONENTS_RACK_H_

#include "../Types.h"
#include <string>

struct Rack {
    acre::rack::RackType type;
    entt::entity          mountedRadio;
    Rack(const acre::rack::RackType rackType = acre::rack::RackType::generic, entt::entity radio_ = entt::null) : type(rackType), mountedRadio(radio_) {};
};

#endif /* SRC_COMPONENTS_UNIQUEID_H_ */
