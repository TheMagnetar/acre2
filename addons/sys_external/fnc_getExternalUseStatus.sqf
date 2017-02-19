/*
 * Author: ACRE2Team
 * Retrieves the external use status of a radio
 *
 * Arguments:
 * 0: Unique radio identity <STRING>
 *
 * Return Value:
 * Array with information if a radio is shared, is in external use, the owner and the end user <ARRAY>
 *
 * Example:
 * ["ACRE_PRC343_ID_1"] call acre_sys_external_getExternalUseStatus
 *
 * Public: No
 */
#include "script_component.hpp"

params ["_radioId"];

_externalStatus = HASH_GET(EGVAR(sys_core,externalStatus),_radioId);

_externalStatus
