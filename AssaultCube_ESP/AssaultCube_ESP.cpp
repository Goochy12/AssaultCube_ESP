// AssaultCube_ESP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AssaultCube_ESP.h"
#include "process.h"
#include <vector>
#include <Windows.h>

int main()
{

    //get process id
    DWORD processID = GetProcessID(L"ac_client.exe");   //L - converts to unicode

    //get module base address
    uintptr_t moduleBase = GetModuleBaseAddress(processID, L"ac_client.exe");

    //get handler to process
    HANDLE hProcess = 0;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, processID);

    //resolve the base address
    uintptr_t dynamicPtrBaseAddr = moduleBase + 0x10f4f4;

    std::cout << "DyanmicPtrBaseAddr: " << "0x" << std::hex << dynamicPtrBaseAddr << std::endl;

    //resolve ammo pointer
    std::vector<unsigned int> ammoOffsets = { 0x374, 0x14, 0x0 };
    uintptr_t ammoAddress = FindDMAAddy(hProcess, dynamicPtrBaseAddr, ammoOffsets);

    std::cout << "AmmoAddr: " << "0x" << std::hex << ammoAddress << std::endl;

    //read ammo value
    int ammoValue = 0;
    ReadProcessMemory(hProcess, (BYTE*)ammoAddress, &ammoValue, sizeof(ammoValue), nullptr);
    std::cout << "Current Ammo: " << std::dec << ammoValue << std::endl;

    //write ammo value
    int newAmmo = 1337;
    WriteProcessMemory(hProcess, (BYTE*)ammoAddress, &newAmmo, sizeof(newAmmo), nullptr);

    //read again
    ReadProcessMemory(hProcess, (BYTE*)ammoAddress, &ammoValue, sizeof(ammoValue), nullptr);
    std::cout << "Current Ammo: " << std::dec << ammoValue << std::endl;


    getchar(); // press enter for input before code ends
    return 0;
}

DWORD getProcessIDByName(const wchar_t* processName) {
    return  0;
}

void setHealth() {

}

//std::cout << "Waiting to open Assult Cube...\n"; // Welcome message
//
//    //get process window
//hwndAC_Client = NULL;
//
//// wait for the user to open the game
//while (hwndAC_Client == NULL) {
//    //find game process
//    hwndAC_Client = FindWindow(0, L"AssaultCube");
//}
//
///*
//get the process ID by the name of the window
//*/
//
////getProcessIdByWindowName(hwndAC_Client);
//
////get the process ID of the client
//GetWindowThreadProcessId(hwndAC_Client, &processIdAC_Client);
//
//std::cout << "Assult Cube opened! Process ID: " << processIdAC_Client << std::endl;  // confirm the game is open
//
////open game process
///hProcessAC_Client = OpenProcess(PROCESS_VM_READ, FALSE, processIdAC_Client);

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
