#include <Windows.h>
#include <TlHelp32.h>
#include <cstdint>
#include <string_view>
#include <chrono>
#include <thread>
#include <iostream>

#include "../memory/memory.h"
#include "../offsets/offsets.h"
#include "../offsets/keys.h"

Memory mem{ "cs2.exe" };
const auto ModuleClientDLL = mem.GetModuleAddress("client.dll");

bool triggerBotEnabled = false;

int main() {
    std::cout << "Welcome to SynapseShot!\n\n";

    std::cout << "Cheat started. Press F1 to enable, F2 to disable trigger bot.\n";

    while (true) {
        if (GetAsyncKeyState(VK_F1) & 0x8000) {
            triggerBotEnabled = true;
            std::cout << "TRIGGER BOT ENABLED\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }

        if (GetAsyncKeyState(VK_F2) & 0x8000) {
            triggerBotEnabled = false;
            std::cout << "TRIGGER BOT DISABLED\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }

        if (GetAsyncKeyState(VK_END) & 0x8000) {
            std::cout << "Exiting program...\n";
            break;
        }

        if (triggerBotEnabled) {
            uintptr_t dwLocalPlayer = mem.Read<uintptr_t>(ModuleClientDLL + OFFSETS::offsets::dwLocalPlayerPawn);

            if (!dwLocalPlayer) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                continue;
            }

            BYTE team = mem.Read<BYTE>(dwLocalPlayer + OFFSETS::client::m_iTeamNum);
            uintptr_t dwEntityList = mem.Read<uintptr_t>(ModuleClientDLL + OFFSETS::offsets::dwEntityList);

            int entIndex = mem.Read<int>(dwLocalPlayer + OFFSETS::client::m_iIDEntIndex);

            if (entIndex > 0) {
                uintptr_t listEntry = mem.Read<uintptr_t>(dwEntityList + 0x8 * (entIndex >> 9) + 0x10);
                uintptr_t entity = mem.Read<uintptr_t>(listEntry + 120 * (entIndex & 0x1ff));

                if (entity && team != mem.Read<BYTE>(entity + OFFSETS::client::m_iTeamNum)) {
                    if (mem.Read<int>(entity + OFFSETS::client::m_iHealth) > 0) {
                        if (mem.Read<int>(dwLocalPlayer + OFFSETS::client::m_flFlashBangTime) > 0)
                            continue;

                        if (mem.Read<int>(dwLocalPlayer + OFFSETS::client::m_fFlags) == KEYS::Value::IN_AIR)
                            continue;

                        mem.Write<int>(ModuleClientDLL + OFFSETS::buttons::attack, KEYS::Value::PLUS_ATTACK);
                        std::this_thread::sleep_for(std::chrono::milliseconds(5));

                        mem.Write<int>(ModuleClientDLL + OFFSETS::buttons::attack, KEYS::Value::MINUS_ATTACK);
                        std::this_thread::sleep_for(std::chrono::milliseconds(5));
                    }
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}