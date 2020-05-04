#include "mem.h"

void mem::PatchEx(BYTE* dest, BYTE* source, unsigned int size, HANDLE hProcess) {

	DWORD oldProtect;
	VirtualProtectEx(hProcess, dest, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	WriteProcessMemory(hProcess, dest, source, size, nullptr);
	VirtualProtectEx(hProcess, dest, size, oldProtect, &oldProtect);

}
void mem::NopEX(BYTE* dest, unsigned int size, HANDLE hProcess) {
	BYTE* nopArray = new BYTE[size];
	memset(nopArray, 0x90, size);

	PatchEx(dest, nopArray, size, hProcess);
	delete[] nopArray;
}