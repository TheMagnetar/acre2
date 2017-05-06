/*
 * Author: ACRE2Team
 * Returns if an individual rack is hearable (in intercom) to a specific unit.
 *
 * Arguments:
 * 0: Unque rack ID <STRING>
 * 1: Unit <OBJECT>
 * 2: Vehicle <OBJECT><OPTIONAL>
 *
 * Return Value:
 * Accessible <BOOLEAN>
 *
 * Example:
 * ["acre_vrc110_id_1",acre_player] call acre_sys_rack_fnc_isRackHearable;
 *
 * Public: No
 */
#include "script_component.hpp"

params ["_rackId", "_unit", ["_vehicle", objNull]];

if (isNull _vehicle) then {
    _vehicle = [_rackId] call FUNC(getVehicleFromRack);
};

if (!alive _vehicle) exitWith {false};

private _wiredIntercoms = [_rackId] call FUNC(getWiredIntercoms);

// Infantry phone units are not allowed
if (_unit isEqualTo ((_vehicle getVariable [QEGVAR(sys_intercom,unitInfantryPhone), [objNull, 0]]) select 0)) exitWith {false};

("crew" in _wiredIntercoms && {_unit in ACRE_PLAYER_CREW_INTERCOM}) || ("passenger" in _wiredIntercoms && {_unit in ACRE_PLAYER_PASSENGER_INTERCOM})
