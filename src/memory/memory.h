#pragma once

#pragma once

#include <cstdint>
#include <string_view>
#include <Windows.h>
#include <tlhelp32.h>
#include <string> // äëÿ std::string

class Memory {
private:
    std::uintptr_t processID = 0;
    void* processHandle = nullptr;

    static bool EqualsIgnoreCase(std::string_view str1, const char* str2) {
        if (str1.size() != strlen(str2)) return false;
        return _stricmp(str1.data(), str2) == 0;
    }

public:
    Memory(const std::string_view processName) noexcept {
        ::PROCESSENTRY32 entry = { };
        entry.dwSize = sizeof(::PROCESSENTRY32);

        const auto processSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        while (::Process32Next(processSnapshot, &entry)) {
            if (EqualsIgnoreCase(processName, entry.szExeFile)) {
                this->processID = entry.th32ProcessID;
                this->processHandle = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->processID);
                break;
            }
        }

        if (processSnapshot) {
            ::CloseHandle(processSnapshot);
        }
    }

    ~Memory() {
        if (this->processHandle) {
            ::CloseHandle(this->processHandle);
        }
    }

    const std::uintptr_t GetModuleAddress(const std::string_view moduleName) const noexcept {
        ::MODULEENTRY32 entry = { };
        entry.dwSize = sizeof(::MODULEENTRY32);

        const auto processSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, this->processID);

        std::uintptr_t moduleBaseAddress = 0;

        while (::Module32Next(processSnapshot, &entry)) {
            if (EqualsIgnoreCase(moduleName, entry.szModule)) {
                moduleBaseAddress = reinterpret_cast<std::uintptr_t>(entry.modBaseAddr);
                break;
            }
        }

        if (processSnapshot) {
            ::CloseHandle(processSnapshot);
        }

        return moduleBaseAddress;
    }

    template<typename T>
    constexpr const T Read(const std::uintptr_t& address) const noexcept {
        T value = { };
        ::ReadProcessMemory(this->processHandle, reinterpret_cast<const void*>(address), &value, sizeof(T), NULL);
        return value;
    }

    template <typename T>
    constexpr void Write(const std::uintptr_t& address, const T& value) const noexcept {
        ::WriteProcessMemory(this->processHandle, reinterpret_cast<void*>(address), &value, sizeof(T), NULL);
    }

    bool PatchMemory(const std::uintptr_t& address, const BYTE* patch, size_t size) const noexcept {
        DWORD oldProtect;
        if (!::VirtualProtectEx(this->processHandle, reinterpret_cast<void*>(address), size, PAGE_EXECUTE_READWRITE, &oldProtect)) {
            return false;
        }
        BOOL success = ::WriteProcessMemory(this->processHandle, reinterpret_cast<void*>(address), patch, size, nullptr);
        ::VirtualProtectEx(this->processHandle, reinterpret_cast<void*>(address), size, oldProtect, &oldProtect);

        return success == TRUE;
    }
};