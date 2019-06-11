#ifndef SRC_COMPONENTS_INTERCOM_H_
#define SRC_COMPONENTS_INTERCOM_H_

#include "intercom/ANVIC3.h"

struct Intercom {
    std::vector<acre::intercom::BaseIntercom> intercoms; // List of intercom systems
};

#endif /* SRC_COMPONENTS_INTERCOM_H_ */
