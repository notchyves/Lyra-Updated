#pragma once
#include "../../../../Utils/Memory/Memory.hpp"
#include "../Actor/LocalPlayer.hpp"
#include "../Block/BlockSource.hpp"
#include "../Render/GuiData.hpp"
#include "MCGame.hpp"
#include "../Level/LevelRender/LevelRender.hpp"
#include "../Network/LoopbackPacketSender.hpp"

class ClientInstance {
public:
	BUILD_ACCESS(this, GuiData*, guiData, 0x558);
	BUILD_ACCESS(this, float*, FovX, 0x6F0);
	BUILD_ACCESS(this, MCGame*, mcgame, 0xC8);
	BUILD_ACCESS(this, float*, FovY, 0x704);

	void grabMouse() {

		static uintptr_t indexRef;

		if (indexRef == 0) {
			indexRef = Memory::findSig("48 8B 80 ? ? ? ? FF 15 ? ? ? ? 90 48 85 DB 74 08 48 8B CB E8 ? ? ? ? 48 8B 8D ? ? ? ? E8");
		}

		int index = *reinterpret_cast<int *>(indexRef + 3) / 8;
		Memory::CallVFuncI<void>(index, this);
	}

	void releaseMouse() {
		static uintptr_t indexRef;

		if (indexRef == 0) {
			indexRef = Memory::findSig("48 8B 80 ? ? ? ? FF 15 ? ? ? ? 90 48 85 DB 74 08 48 8B CB E8 ? ? ? ? 48 8B 8D ? ? ? ? E8");
		}

		int index = *reinterpret_cast<int *>(indexRef + 3) / 8;
		Memory::CallVFuncI<void>(index + 1, this);
	}

	BlockSource* getBlockSource() {
		return Memory::CallVFunc<28, BlockSource*>(this);
	}

	LocalPlayer* getLocalPlayer() {
		static uintptr_t indexRef;

		if (indexRef == 0) {
			indexRef = Memory::findSig("49 8B 00 49 8B C8 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 48 85 C0 0F 84 ? ? ? ? 0F");
		}

		int index = *reinterpret_cast<int*>(indexRef + 9) / 8;

		return Memory::CallVFuncI<LocalPlayer*>(index, this);
	}


	LevelRender* getLevelRenderer() {
		return Memory::direct_access<LevelRender*>(this, 0xE0);
	}

    LoopbackPacketSender *getPacketSender() {
        return *reinterpret_cast<LoopbackPacketSender **>((uintptr_t) this + 0xF0);
    }

    RaknetConnector *getRakNetConnector() {
        if (getPacketSender() == nullptr)
            return nullptr;

        return getPacketSender()->networkSystem->remoteConnectorComposite->rakNetConnector;
    }
};