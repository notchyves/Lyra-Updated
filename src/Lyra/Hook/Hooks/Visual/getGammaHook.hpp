 #pragma once

#include "../Hook.hpp"
#include "../../../Module/Modules/Fullbright.hpp"

class getGammaHook : public Hook {
private:

    static float getGammaCallback(uintptr_t a1) {

        if (Settings::getSettingByName<bool>("Fullbright", "enabled")->value)
            return 25;

        return funcOriginal(a1);
    }

public:
    typedef float(__thiscall *getGammaOriginal)(uintptr_t);

    static inline getGammaOriginal funcOriginal = nullptr;

    getGammaHook() : Hook("getGammaHook",
                          "48 83 EC 28 80 B9 80 17 00 00 00 48 8D 54 24 30 48 8B 01 48 8B 40 60 74 38 41 B8 19") {}

    void enableHook() override {
        this->autoHook((void *) getGammaCallback, (void **) &funcOriginal);
    }
};