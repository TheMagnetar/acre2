/*
 * Author: ACRE2Team
 * Generates a list of actions for using a radio in the player's inventory or externally used radios
 *
 * Arguments:
 * 0: Unit with ACRE2 radios <OBJECT>
 * 1: None <TYPE>
 * 2: Array with additional parameters: unique radio ID <ARRAY>
 *
 * Return Value:
 * Array of actions <ARRAY>
 *
 * Example:
 * [acre_player, "", ["ACRE_PRC343_ID_1"]] call acre_ace_interact_fnc_externalRadioChildrenActions
 *
 * Public: No
 */
#include "script_component.hpp"

/* TODO:
* Implemented, to be tested: Option to share and not share radios should not be displayed for external radios.
*/

params ["_target","","_params"];
_params params ["_radio", "", "_pttAssign", "_vehicleRadioList"];

private _actions = [];

private _spatial = [_radio] call EFUNC(api,getRadioSpatial);
private _txt = localize LSTRING(bothEars);
if (_spatial == "LEFT") then {
    _txt = localize LSTRING(leftEar);
};
if (_spatial == "RIGHT") then {
    _txt = localize LSTRING(rightEar);
};

if (!(_radio in _vehicleRadioList)) then {
    private _action = ["acre_spatial_radio", _txt, "", {}, {true}, {_this call FUNC(generateSpatialChildrenActions);}, _params + [_spatial]] call ace_interact_menu_fnc_createAction;
    _actions pushBack [_action, [], _target];
    _action = ["acre_open_radio", localize ELSTRING(sys_list,OpenRadio), "", {[((_this select 2) select 0)] call EFUNC(sys_radio,openRadio)}, {true}, {}, _params] call ace_interact_menu_fnc_createAction;
    _actions pushBack [_action, [], _target];
    _action = ["acre_make_active", localize LSTRING(setAsActive), "", {[(_this select 2) select 0] call EFUNC(api,setCurrentRadio)}, {!((_this select 2) select 1)}, {},_params] call ace_interact_menu_fnc_createAction;
    _actions pushBack [_action, [], _target];

    // External radios. Show only options to share/stop sharing the radio if you are the actual owner and not an external user
    if (!(_radio in ACRE_ACTIVE_EXTERNAL_RADIOS)) then {
        _action = ["acre_share_radio", localize LSTRING(shareRadio), "", {[(_this select 2) select 0, true] call EFUNC(sys_external,allowExternalUse)}, {!([(_this select 2) select 0] call EFUNC(sys_external,isRadioShared))}, {}, _params]  call ace_interact_menu_fnc_createAction;
        _actions pushBack [_action, [], _target];
        _action = ["acre_retrieve_radio", localize LSTRING(retrieveRadio), "", {[(_this select 2) select 0, false] call EFUNC(sys_external,allowExternalUse)}, {[(_this select 2) select 0] call EFUNC(sys_external,isRadioShared)}, {}, _params]  call ace_interact_menu_fnc_createAction;
        _actions pushBack [_action, [], _target];
    };

    private _idx = _pttAssign find _radio;
    _txt = localize LSTRING(bindMultiPushToTalk);;
    if (_idx > -1 and _idx < 3) then {
        _txt = format [localize LSTRING(multiPushToTalk),(_idx+1)];
    };

    _action = ["acre_mptt_assign", _txt, "", {}, {true}, {_this call FUNC(radioPTTChildrenActions);}, _params] call ace_interact_menu_fnc_createAction;
    _actions pushBack [_action, [], _target];
} else {
    // They are only available if the player is the driver or commander of a vehicle
    if (tolower (assignedVehicleRole acre_player select 0) in ["driver","commander"] || (_radio in ACRE_ACTIVE_EXTERNAL_RADIOS)) then {
        if (!([_radio] call EFUNC(sys_external,isExternalRadioUsed))) then {
            // Force first the player to take the headset
            private _action = ["acre_use_externalRadio", localize LSTRING(takeHeadset), "", {[(_this select 2) select 0, vehicle acre_player, acre_player] call EFUNC(sys_external,startUsingExternalRadio)}, {true}, {}, _params] call ace_interact_menu_fnc_createAction;
            _actions pushBack [_action, [], _target];
        } else {
            // Only the player with the headset should be able to manipulate the radio.
            if ([_radio, acre_player] call FUNC(externalRadioCheckListChildrenActions)) then {
                private _action = ["acre_return_externalRadio", localize LSTRING(returnHeadset), "", {[(_this select 2) select 0, vehicle acre_player] call EFUNC(sys_external,stopUsingExternalRadio)}, {true}, {}, _params] call ace_interact_menu_fnc_createAction;
                _actions pushBack [_action, [], _target];
                _action = ["acre_spatial_radio", _txt, "", {}, {true}, {_this call FUNC(generateSpatialChildrenActions);}, _params + [_spatial]] call ace_interact_menu_fnc_createAction;
                _actions pushBack [_action, [], _target];
                _action = ["acre_open_radio", localize ELSTRING(sys_list,OpenRadio), "", {[((_this select 2) select 0)] call EFUNC(sys_radio,openRadio)}, {true}, {}, _params] call ace_interact_menu_fnc_createAction;
                _actions pushBack [_action, [], _target];
                _action = ["acre_make_active", localize LSTRING(setAsActive), "", {[(_this select 2) select 0] call EFUNC(api,setCurrentRadio)}, {!((_this select 2) select 1)}, {},_params] call ace_interact_menu_fnc_createAction;
                _actions pushBack [_action, [], _target];

                // External radios. Show only options to share/stop sharing the radio if you are the actual owner and not an external user
                if (!(_radio in ACRE_ACTIVE_EXTERNAL_RADIOS)) then {
                    _action = ["acre_share_radio", localize LSTRING(shareRadio), "", {[(_this select 2) select 0, true] call EFUNC(sys_external,allowExternalUse)}, {!([(_this select 2) select 0] call EFUNC(sys_external,isRadioShared))}, {}, _params]  call ace_interact_menu_fnc_createAction;
                    _actions pushBack [_action, [], _target];
                    _action = ["acre_retrieve_radio", localize LSTRING(retrieveRadio), "", {[(_this select 2) select 0, false] call EFUNC(sys_external,allowExternalUse)}, {[(_this select 2) select 0] call EFUNC(sys_external,isRadioShared)}, {}, _params]  call ace_interact_menu_fnc_createAction;
                    _actions pushBack [_action, [], _target];
                };

                private _idx = _pttAssign find _radio;
                _txt = localize LSTRING(bindMultiPushToTalk);;
                if (_idx > -1 and _idx < 3) then {
                    _txt = format [localize LSTRING(multiPushToTalk),(_idx+1)];
                };

                _action = ["acre_mptt_assign", _txt, "", {}, {true}, {_this call FUNC(radioPTTChildrenActions);}, _params] call ace_interact_menu_fnc_createAction;
                _actions pushBack [_action, [], _target];
            };
        };
    };
};


_actions
