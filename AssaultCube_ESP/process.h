#pragma once

#include <vector>
#include <Windows.h>
#include <TlHelp32.h>

DWORD GetProcessID(const wchar_t* processName);	//wchar_t use unicode as default character set

uintptr_t GetModuleBaseAddress(DWORD processID, const wchar_t* moduleName);

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);