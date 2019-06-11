#include "script_component.hpp"
/*
 * Author: ACRE2Team
 * Unregisters a unit in the ECS system.
 *
 * Arguments:
 * 0: Unit <OBJECT>
 *
 * Return Value:
 * None
 *
 * Example:
 * [] call acre_sys_ecs_fnc_unregisterUnit
 *
 * Public: No
 */

params ["_unit"];

private _uniqueId = 0;
private _action = "";
if (_unit isKindOf "CAManBase") then {
    if (isPlayer _unit) then {
        _action = "unregisterUnit";
    };
} else {
    _action = "unregisterVehicle";
};

private _uniqueId = _unit getVariable [QGVAR(uniqueId), -1];
private _value = format ["%1:%2", _action, _uniqueId];

_value call FUNC(callExtension);
