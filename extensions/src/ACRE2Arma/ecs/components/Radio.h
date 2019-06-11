#ifndef SRC_COMPONENTS_RADIO_H_
#define SRC_COMPONENTS_RADIO_H_

#include "radio/ANPRC77.h"
#include "radio/ANPRC117F.h"
#include "radio/ANPRC148.h"
#include "radio/ANPRC152.h"
#include "radio/ANPRC343.h"
#include "radio/SEM52SL.h"
#include "radio/SEM70.h"

struct Radio {
    acre::radio::RadioType type;
    Radio(const acre::radio::RadioType radioType = acre::radio::RadioType::generic) : type(radioType){};
};

#endif /* SRC_COMPONENTS_RADIO_H_ */
