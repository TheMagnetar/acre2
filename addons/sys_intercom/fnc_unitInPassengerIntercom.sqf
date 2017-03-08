/*
 * Author: ACRE2Team
 * Checks if a unit is in the passenger intercom of a vehicle
 *
 * Arguments:
 * 0: Vehicle with a passenger intercom action <OBJECT>
 * 1: Unit to be checked <OBJECT>
 *
 * Return Value:
 * None
 *
 * Example:
 * [cursorTarget, acre_player] call acre_sys_intercom_unitInPassengerIntercom
 *
 * Public: No
 */
#include "script_component.hpp"

params ["_vehicle", "_unit"];

private _inPassengerIntercom = false;

if (_unit in (_vehicle getVariable [QGVAR(unitsPassengerIntercom), []])) then {
    _inPassengerIntercom = true;
};

_inPassengerIntercom
