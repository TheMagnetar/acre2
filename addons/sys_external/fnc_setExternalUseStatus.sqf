/*
 * Author: ACRE2Team
 * Sets the status of the external use of the given radio
 *
 * Arguments:
 * 0: Unique radio identity <STRING>
 * 1: External use status with the following elements <ARRAY>
 *
 * The array has the following elements: is radio shared <BOOL>, is radio externally used <BOOL>, radio owner <OBJECT> and radio user <OBJECT>.
 *
 * Return Value:
 * Radio is shared and ready for external use <BOOL>
 *
 * Example:
 * ["ACRE_PRC343_ID_1", ture,] call acre_sys_external_setExternalUseStatus
 *
 * Public: No
 */
 #include "script_component.hpp"

params ["_radioID", "_externalStatus"];

HASH_SET(EGVAR(sys_core,externalStatus), _radioId, _externalStatus);
publicVariable QEGVAR(sys_core,externalStatus);
