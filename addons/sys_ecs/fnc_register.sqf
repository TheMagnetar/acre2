#include "script_component.hpp"
/*
 * Author: ACRE2Team
 * Registers a unit in the ECS system.
 *
 * Arguments:
 * 0: Unit <OBJECT>
 *
 * Return Value:
 * None
 *
 * Example:
 * [] call acre_sys_ecs_fnc_registerUnit
 *
 * Public: No
 */

params ["_unit"];

private _uniqueId = 0;
private _action = "";
if (_unit isKindOf "CAManBase") then {
    if (isPlayer _unit) then {
        _uniqueId = getPlayerUID _unit;
        _action = "registerUnit";
    };
} else {
    _uniqueId = GVAR(vehicleId);
    GVAR(vehicleId) = GVAR(vehicleId) + 1;
    _action = "registerVehicle";
};

_unit setVariable [QGVAR(uniqueId), _uniqueId, true];
private _pos = getPosASL _unit;
private _dir = getDir _unit;

private _value = format ["%1:%2,%3,%4,%5,%6", _action, _uniqueId, _pos select 0, _pos select 1, _pos select 2, _dir];

_value call FUNC(callExtension);
