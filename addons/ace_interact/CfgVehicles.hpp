class CfgVehicles {
    class Man;
    class CAManBase: Man {
        class ACE_SelfActions {
            class ACRE_Interact {
                displayName = CSTRING(radios);
                condition = QUOTE(_player call EFUNC(api,hasRadio));
                exceptions[] = {"isNotInside", "isNotSitting"};
                statement = "true";
                insertChildren = QUOTE(_this call FUNC(radioListChildrenActions));
                priority = 0.1;
                icon = "\a3\Ui_f\data\GUI\Cfg\CommunicationMenu\call_ca.paa";
            };
        };
    };
};
