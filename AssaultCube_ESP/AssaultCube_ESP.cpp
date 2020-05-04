// AssaultCube_ESP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AssaultCube_ESP.h"
#include "process.h"
#include <vector>
#include <Windows.h>
#include "Menu/menu.h"
#include "mem.h"


DWORD processID;
uintptr_t moduleBase;
uintptr_t dynamicPtrBaseAddr;
HANDLE hProcess;

//menu
Menu* menu;

//localPlayer
uintptr_t playerEntityPtrOffset = 0x10f4f4;

//health
DWORD healthOffset = 0xF8;	//health offset
boolean healthToggle = FALSE;
std::string healthStatus = "OFF";
uintptr_t healthAddress;

//ammo
std::vector<unsigned int> ammoOffsets = { 0x374, 0x14, 0x0 };   //ammo offsets
boolean ammoToggle = FALSE;
std::string ammoStatus = "OFF";
uintptr_t ammoAddress;



int main()
{

	processID = NULL;   //initiate to null

	//welcome message
	std::cout << "Waiting for Assult Cube to be opened..." << std::endl;

	while (processID == NULL)
	{
		//get process id
		processID = GetProcessID(L"ac_client.exe");   //L - converts to unicode
	}

	system("cls");  //clear the screen
	Sleep(500); // give the process time to open

	//load the menu
	std::cout << "Welcome to Liam's Assult Cube Trainer/ESP" << std::endl;


	handleProcessOpen(processID);

	findAddresses();

	//start the menu
	startMenu();

	//start input loop
	menuInputLoop();

	//TODO:
	//loop display - update on change
	//update menu on item toggle

	//getchar(); // press enter for input before code ends
	return 0;
}

void findAddresses() {
	ammoAddress = FindDMAAddy(hProcess, dynamicPtrBaseAddr, ammoOffsets);
}

void menuInputLoop() {


	while (!GetAsyncKeyState(VK_END)) {

		continuousWriteToMemory();

		if(GetAsyncKeyState(VK_NUMPAD1) && 1){

			//setValue(9999, hProcess, dynamicPtrBaseAddr, ammoAddress);

			ammoToggle = !ammoToggle;
			if (ammoToggle) {
				ammoStatus = "ON";
			}
			else {
				ammoStatus = "OFF";
			}
			//update menu
			menu->updateMenuItemToggle(0, ammoToggle);
			menu->updateMenuItemToggleDisplay(0, ammoStatus);
			menu->display();
		}

	}
}

void continuousWriteToMemory() {

	if (ammoToggle) {
		setValue(9999, hProcess, dynamicPtrBaseAddr, ammoAddress);
	}
}

void createMenuItems() {
	menu->addMenuItem(false, "OFF", '1', { "Unlimited Ammo" });
	menu->addMenuItem(false, "OFF", '2', { "God Mode" });
	menu->addMenuItem(false, "OFF", '3', { "ESP" });
	menu->addMenuItem(false, "OFF", '4', { "Aimbot" });

}

void startMenu() {
	menu = new Menu("AssaultCube Sample External Hack", "Welcome to my sample external hack!", "");
	createMenuItems();

	menu->display();
}

void handleProcessOpen(DWORD processID) {
	/*
		OPEN PROCESS

		Get the module base address
		Use the module base address to get the dynamic pointer address
		Open the process
	*/

	//get module base address
	moduleBase = GetModuleBaseAddress(processID, L"ac_client.exe");

	//resolve the base address
	dynamicPtrBaseAddr = moduleBase + playerEntityPtrOffset;
	//std::cout << "DyanmicPtrBaseAddr: " << "0x" << std::hex << dynamicPtrBaseAddr << std::endl;

	//get handler to process
	hProcess = 0;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, processID);
}

void setValue(int value, HANDLE hProcess, uintptr_t dynamicPtrBaseAddr, uintptr_t address) {
	//read ammo value
	int initialGameValue = 0;
	//ReadProcessMemory(hProcess, (BYTE*)address, &initialGameValue, sizeof(initialGameValue), nullptr);
	//std::cout << "Current Value: " << std::dec << initialGameValue << std::endl;

	WriteProcessMemory(hProcess, (BYTE*)address, &value, sizeof(value), nullptr);

	//read again
	//ReadProcessMemory(hProcess, (BYTE*)address, &initialGameValue, sizeof(initialGameValue), nullptr);
	//std::cout << "New Value: " << std::dec << initialGameValue << std::endl;
}

uintptr_t getAmmoAddress(std::vector<unsigned int> ammoOffsets, HANDLE hProcess, uintptr_t dynamicPtrBaseAddr) {
	uintptr_t ammoAddress;

	//resolve ammo pointer
	ammoAddress = FindDMAAddy(hProcess, dynamicPtrBaseAddr, ammoOffsets);

	return ammoAddress;
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

//DWORD getProcessIDByName(const wchar_t* processName) {
//    return  0;
//}

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
