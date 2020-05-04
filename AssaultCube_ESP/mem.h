#pragma once
#include <Windows.h>

namespace mem {
	void PatchEx(BYTE* dest, BYTE* source, unsigned int size, HANDLE hProcess);
	void NopEX(BYTE* dest, unsigned int size, HANDLE hProcess);
}