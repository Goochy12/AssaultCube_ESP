#pragma once
#include <Windows.h>

HWND hwndAC_Client;	//window handler for client
HANDLE hProcessAC_Client;	//process handler
DWORD processIdAC_Client;	//process ID of the client
DWORD localPlayerPtr;	//pointer to localplayer entity
DWORD healthOffset = 0xF8;	//health offset

void setValue(int value, HANDLE hProcess, uintptr_t dynamicPtrBaseAddr, uintptr_t address);


//DWORD getProcessIDByName(const wchar_t* processName);