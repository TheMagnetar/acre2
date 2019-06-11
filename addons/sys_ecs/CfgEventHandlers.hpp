class Extended_PreStart_EventHandlers {
    class ADDON {
        init = QUOTE(call COMPILE_FILE(XEH_preStart));
    };
};

class Extended_PreInit_EventHandlers {
    class ADDON {
        init = QUOTE(call COMPILE_FILE(XEH_preInit));
    };
};

class Extended_PostInit_EventHandlers {
    class ADDON {
        init = QUOTE(call COMPILE_FILE(XEH_postInit));
    };
};

class Extended_Init_EventHandlers {
    class Tank {
        class GVAR(ecsRegister) {
            init = QUOTE(_this call FUNC(register));
        };
    };
};

class Extended_Killed_EventHandlers {
    class Tank {
        GVAR(ecsUnregister) = QUOTE(_this call FUNC(unregister));
    };
};
