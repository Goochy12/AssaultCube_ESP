#include "process.h"


DWORD GetProcessID(const wchar_t* processName) {
	DWORD processID = 0;	//error checking
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);	//get snapchot of processes
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;	//process entry
		procEntry.dwSize = sizeof(procEntry);	//set size correctly

		//grabs first process in snapshot and store in process entry
		if (Process32First(hSnap, &procEntry))
		{
			//loop through all processes (next command)
			do
			{
				if (!_wcsicmp(procEntry.szExeFile, processName)) {
					//compare file name against given process name (case insensitive)
					processID = procEntry.th32ProcessID;	//get process id
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);	//close snapshot
	return processID;	//return process id
}

//uintptr - architecture independent variable - addressable memory range (compile at same architecture as game process)
uintptr_t GetModuleBaseAddress(DWORD processID, const wchar_t* moduleName) {
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID);

	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);

		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, moduleName)) {
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}

//dynamic memory allocation
//handle to process, base pointer (ac client.exe), vector of unsigned ints (offsets)
uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets) {
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); i++) {
		ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr += offsets[i];
	}
	return addr;
}