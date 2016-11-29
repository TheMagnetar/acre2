/*
 * Author: ACRE2Team
 * SHORT DESCRIPTION
 *
 * Arguments:
 * 0: ARGUMENT ONE <TYPE>
 * 1: ARGUMENT TWO <TYPE>
 *
 * Return Value:
 * RETURN VALUE <TYPE>
 *
 * Example:
 * [ARGUMENTS] call acre_sys_prc77_fnc_onpenGui;
 *
 * Public: No
 */
#include "script_component.hpp"

TRACE_1("OPENING GUI", _this);

disableSerialization;
GVAR(currentRadioId) = _this select 0;
createDialog "PRC77_RadioDialog";

true
