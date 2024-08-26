#pragma once
#include "../Module.hpp"

extern bool shouldFreelook;

class FreeLook : public Module {
public:
    FreeLook();
	std::string getModuleName() override;
    void onEnable() override;
    void onDisable() override;
    void InitModuleSettings() override;
    void onKey(KeyEvent& event) override;
    void onTick(const TickEvent& event) override;
    void patch() const;
    void unpatch() const;

private:
    static inline uintptr_t yaw1;
    static inline uintptr_t yaw2;
    static inline uintptr_t pitch;
    static inline uintptr_t movement;

    static inline uint8_t nop[4] = { 0x90, 0x90, 0x90, 0x90 };

    static inline std::array<std::byte, 4> originalYaw1;
    static inline std::array<std::byte, 4> originalYaw2;
    static inline std::array<std::byte, 4> originalPitch;
    static inline std::array<std::byte, 4> originalMovement;
};