#pragma once

#include <cstddef>

namespace OFFSETS {
    namespace offsets {
        constexpr std::ptrdiff_t dwCSGOInput = 0x1E37430;
        constexpr std::ptrdiff_t dwEntityList = 0x1D0FE08;
        constexpr std::ptrdiff_t dwGameEntitySystem = 0x1FAFD98;
        constexpr std::ptrdiff_t dwGameEntitySystem_highestEntityIndex = 0x20F0;
        constexpr std::ptrdiff_t dwGameRules = 0x1E29038;
        constexpr std::ptrdiff_t dwGlobalVars = 0x1BE1990;
        constexpr std::ptrdiff_t dwGlowManager = 0x1E29048;
        constexpr std::ptrdiff_t dwLocalPlayerController = 0x1E19010;
        constexpr std::ptrdiff_t dwLocalPlayerPawn = 0x1BEC440;
        constexpr std::ptrdiff_t dwPlantedC4 = 0x1E32140;
        constexpr std::ptrdiff_t dwPrediction = 0x1BEC370;
        constexpr std::ptrdiff_t dwSensitivity = 0x1E29B68;
        constexpr std::ptrdiff_t dwSensitivity_sensitivity = 0x48;
        constexpr std::ptrdiff_t dwViewAngles = 0x1E37BE0;
        constexpr std::ptrdiff_t dwViewMatrix = 0x1E2D030;
        constexpr std::ptrdiff_t dwViewRender = 0x1E2DCC0;
        constexpr std::ptrdiff_t dwWeaponC4 = 0x1DCA4C0;
    }

    namespace client {
        constexpr std::ptrdiff_t m_fFlags = 0x3F8;
        constexpr std::ptrdiff_t m_iTeamNum = 0x3EB;
        constexpr std::ptrdiff_t  m_iIDEntIndex = 0x3EDC;
        constexpr std::ptrdiff_t m_iHealth = 0x34C;
        constexpr std::ptrdiff_t m_flFlashBangTime = 0x160C;
    }

    namespace buttons {
        constexpr std::ptrdiff_t attack = 0x1BE5AD0;
        constexpr std::ptrdiff_t attack2 = 0x1BE5B60;
        constexpr std::ptrdiff_t back = 0x1BE5DA0;
        constexpr std::ptrdiff_t duck = 0x1BE6070;
        constexpr std::ptrdiff_t forward = 0x1BE5D10;
        constexpr std::ptrdiff_t jump = 0x1BE5FE0;
        constexpr std::ptrdiff_t left = 0x1BE5E30;
        constexpr std::ptrdiff_t lookatweapon = 0x1E37350;
        constexpr std::ptrdiff_t reload = 0x1BE5A40;
        constexpr std::ptrdiff_t right = 0x1BE5EC0;
        constexpr std::ptrdiff_t showscores = 0x1E37230;
        constexpr std::ptrdiff_t sprint = 0x1BE59B0;
        constexpr std::ptrdiff_t turnleft = 0x1BE5BF0;
        constexpr std::ptrdiff_t turnright = 0x1BE5C80;
        constexpr std::ptrdiff_t use = 0x1BE5F50;
        constexpr std::ptrdiff_t zoom = 0x1E372C0;
    }
}