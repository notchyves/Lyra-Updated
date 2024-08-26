#include "FreeLook.hpp"
#include "../../SDK/SDK.hpp"
#include "ModMenu.hpp"

bool shouldFreelook = false;

FreeLook::FreeLook() : ModuleCtor(67, "Freelook", "freelook") {
	this->InitModuleSettings();
    
    yaw1 = Memory::findSig("F3 0F 11 ? F3 0F 11 ? ? 48 8B CE");
    yaw2 = Memory::findSig("F3 0F 11 ? F3 0F 11 ? ? 48 8B 4D");
    pitch = Memory::findSig("F3 0F 11 0E 48 89 9C");
    movement = Memory::findSig("F3 0F 11 01 48 8D 56");

    originalYaw1 = std::bit_cast<std::array<std::byte, 4>>(*(std::byte(*)[4])yaw1);
    originalYaw2 = std::bit_cast<std::array<std::byte, 4>>(*(std::byte(*)[4])yaw2);
    originalPitch = std::bit_cast<std::array<std::byte, 4>>(*(std::byte(*)[4])pitch);
    originalMovement = std::bit_cast<std::array<std::byte, 4>>(*(std::byte(*)[4])movement);
}


std::string FreeLook::getModuleName() {
	return "Freelook";
}

void FreeLook::InitModuleSettings() {
	Settings::addSetting<bool>("Freelook", "enabled", false, true);
    Settings::addSetting<int>("Freelook", "KEYBIND", 70, true);

	this->SettingsList["CONTROLS"]["KEYBIND"] = "keybind";
}

void FreeLook::onEnable() {
	Settings::getSettingByName<bool>("Freelook", "enabled")->value = true;
	eventMgr.addListener(this);
}

void FreeLook::onDisable() {
	Settings::getSettingByName<bool>("Freelook", "enabled")->value = false;
	eventMgr.removeListener(this);
}

void FreeLook::onKey(KeyEvent& event) {
	if (event.getKey() == Settings::getSettingByName<int>("Freelook", "KEYBIND")->value and SDK::TopScreen.rfind("hud_screen") != std::string::npos and !Settings::getSettingByName<bool>("Mod Menu", "enabled")->value) {
        shouldFreelook = event.isPressed();
	}
}

void FreeLook::onTick(const TickEvent& event) {
    if(!SDK::clientInstance || !SDK::clientInstance->getLocalPlayer()) return;
	if (shouldFreelook) {
        patch();
    }
    else {unpatch();}


}

void FreeLook::patch() const {
    Memory::patchBytes((void*)yaw1, nop, 4);
    Memory::patchBytes((void*)yaw2, nop, 4);
    Memory::patchBytes((void*)pitch, nop, 4);
    Memory::patchBytes((void*)movement, nop, 4);
}

void FreeLook::unpatch() const {
    Memory::patchBytes((void*)yaw1, originalYaw1.data(), 4);
    Memory::patchBytes((void*)yaw2, originalYaw2.data(), 4);
    Memory::patchBytes((void*)pitch, originalPitch.data(), 4);
    Memory::patchBytes((void*)movement, originalMovement.data(), 4);
}