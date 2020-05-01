#pragma once
#include <Windows.h>

HWND hwndAC_Client;	//window handler for client
HANDLE hProcessAC_Client;	//process handler
DWORD processIdAC_Client;	//process ID of the client
DWORD localPlayerPtr;	//pointer to localplayer entity

void setValue(int value, HANDLE hProcess, uintptr_t dynamicPtrBaseAddr, uintptr_t address);
void handleProcessOpen(DWORD processID);

//DWORD getProcessIDByName(const wchar_t* processName);