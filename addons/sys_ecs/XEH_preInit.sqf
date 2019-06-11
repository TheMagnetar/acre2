#include "script_component.hpp"

ADDON = false;

PREP_RECOMPILE_START;
#include "XEH_PREP.hpp"
PREP_RECOMPILE_END;

GVAR(vehicleId) = 0;
GVAR(unitId) = 0;

ADDON = true;
