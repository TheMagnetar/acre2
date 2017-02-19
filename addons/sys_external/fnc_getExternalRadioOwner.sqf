/*
 * Author: ACRE2Team
 * Retrieves the owner of a radio that is being used externally
 *
 * Arguments:
 * 0: Unique radio identity <STRING>
 *
 * Return Value:
 * Radio owner <OBJECT>. If it is not in external use, it returns nil
 *
 * Example:
 * ["ACRE_PRC343_ID_1"] call acre_sys_external_getExternalRadioOwner
 *
 * Public: No
 */
#include "script_component.hpp"

params ["_radioId"];

private _owner = ([_radioId] call FUNC(getExternalUseStatus)) select 2;

_owner
