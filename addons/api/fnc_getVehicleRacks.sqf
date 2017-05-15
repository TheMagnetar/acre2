/*
 * Author: ACRE2Team
 * Gets all racks in a vehicle.
 *
 * Arguments:
 * 0: Vehicle <OBJECT>
 *
 * Return Value:
 * List of vehicle racks <ARRAY>
 *
 * Example:
 * [cursorTarget] call acre_api_fnc_getVehicleRacks
 *
 * Public: Yes
 */
#include "script_component.hpp"

params ["_vehicle"];

[_vehicle] call EFUNC(sys_rack,getVehicleRacks)
