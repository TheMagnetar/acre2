/*
 * Author: ACRE2Team
 * Checks if a radio is shared to other players
 *
 * Arguments:
 * 0: Unique radio identity <STRING>
 *
 * Return Value:
 * Radio is shared and ready for external use <BOOL>
 *
 * Example:
 * ["ACRE_PRC343_ID_1"] call acre_sys_external_isRadioShared
 *
 * Public: No
 */
 #include "script_component.hpp"

params ["_radioId"];

private _isShared = ([_radioId] call FUNC(getExternalUseStatus)) select 0;

_isShared
