#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

#include "main.hpp"

int main(int argc, char* argv[]) {
	system("color b");
	system("cls");
	std::cout << std::endl << "========================================================================================================================" << std::endl;
	std::cout << "   ___   _  ___  ______    _______ ___  ____   _   __         _" << std::endl;
	std::cout << "  / _ | / |/ / |/ / __ \\  <  / / // _ \\/ / /  | | / /__ ___  (_)______" << std::endl;
	std::cout << " / __ |/    /    / /_/ /  / /_  _/ // /_  _/  | |/ / -_) _ \\/ / __/ -_)" << std::endl;
	std::cout << "/_/ |_/_/|_/_/|_/\\____/  /_/ /_/ \\___/ /_/    |___/\\__/_//_/_/\\__/\\__/                               v2.01.5010" << std::endl;
	std::cout << std::endl << "========================================================================================================================" << std::endl;
	std::cout << std::endl << "Press Numpad 0 to quit. Hold down Numpad 8 to increase gold. Hold down Numpad 9 to increase honor." << std::endl;
	std::cout << std::endl << "Make sure to have NumLock active and the anno window focused." << std::endl;
	char game_name[] = "Addon.exe";
	HANDLE hProcess = INVALID_HANDLE_VALUE;
	int quit = 0;
	if(argc == 1) {
		while(hProcess == INVALID_HANDLE_VALUE && quit == 0) {
			hProcess = open_process_mem(game_name);
			if(GetKeyState(VK_NUMPAD0) & 0x8000) {
				quit = 1;
			}
		}
	} else {
		while(hProcess == INVALID_HANDLE_VALUE && quit == 0) {
			hProcess = open_process_mem_pid(strtol(argv[1], 0, 0));
			if(GetKeyState(VK_NUMPAD0) & 0x8000) {
				quit = 1;
			}
		}
	}
	while(quit == 0) {
		if (GetKeyState(VK_NUMPAD0) & 0x8000) {
			quit = 1;
		}
		HWND test_window = GetForegroundWindow();
		DWORD test_window_pid;
		GetWindowThreadProcessId(test_window, &test_window_pid);
		if(pid == test_window_pid) {
			if(GetKeyState(VK_NUMPAD8) & 0x8000) {
				inc_res(hProcess, 1);
			}
			if(GetKeyState(VK_NUMPAD9) & 0x8000) {
				inc_res(hProcess, 2);
			}
		}
	}
	close_process_mem(hProcess);
	return 0;
}

HANDLE open_process_mem(char* process_window_title) {
	PROCESSENTRY32 pentry;
	pentry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE csnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, (DWORD)NULL);
	if(Process32First(csnapshot, &pentry) == TRUE) {
		while(Process32Next(csnapshot, &pentry) == TRUE) {
			if(_stricmp(pentry.szExeFile, process_window_title) == 0) {
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pentry.th32ProcessID);
				pid = pentry.th32ProcessID;
				CloseHandle(csnapshot);
				if(hProcess == INVALID_HANDLE_VALUE) {
					return hProcess;
				}
				return hProcess;
			}
		}
	}
	CloseHandle(csnapshot);
	return INVALID_HANDLE_VALUE;
}

HANDLE open_process_mem_pid(DWORD set_pid) {
	PROCESSENTRY32 pentry;
	pentry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE csnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, (DWORD)NULL);
	if(Process32First(csnapshot, &pentry) == TRUE) {
		while(Process32Next(csnapshot, &pentry) == TRUE) {
			if(pentry.th32ProcessID == set_pid) {
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pentry.th32ProcessID);
				pid = pentry.th32ProcessID;
				CloseHandle(csnapshot);
				if(hProcess == INVALID_HANDLE_VALUE) {
					return hProcess;
				}
				return hProcess;
			}
		}
	}
	CloseHandle(csnapshot);
	return INVALID_HANDLE_VALUE;
}

void close_process_mem(HANDLE hProcess) {
	CloseHandle(hProcess);
}


uintptr_t GetModuleBaseAddress(DWORD procId, const char* modName) {
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, procId);
	if(hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if(Module32First(hSnap, &modEntry)) {
			do{
				if(!strcmp(modEntry.szModule, modName)) {
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			}while(Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}

void inc_res(HANDLE hProcess, int res_type) {
	uintptr_t moduleBase = GetModuleBaseAddress(pid, "Addon.exe");
	uintptr_t addr = 0;
	BYTE value[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// gold
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};	// honor
	ReadProcessMemory(hProcess, (LPVOID)(moduleBase + GOLDPTR_A), &addr, sizeof(addr), NULL);
	ReadProcessMemory(hProcess, (LPVOID)(addr + GOLDPTR_B), &addr, sizeof(addr), NULL);
	ReadProcessMemory(hProcess, (LPVOID)(addr + GOLDPTR_C), &addr, sizeof(addr), NULL);
	ReadProcessMemory(hProcess, (LPVOID)(addr + GOLDPTR_D), &addr, sizeof(addr), NULL);
	ReadProcessMemory(hProcess, (LPVOID)(addr + GOLDPTR_E), &addr, sizeof(addr), NULL);
	ReadProcessMemory(hProcess, (LPVOID)(addr + GOLDPTR_F), value, 16, NULL);
	if(res_type == 1) {	// gold
		if(value[2] != 0xFF) {
			value[2] = value[2] + 0x01;
		} else {
			value[2] = 0x00;
			if(value[3] != 0xFF) {
				value[3] = value[3] + 0x01;
			} else {
				value[3] = 0x00;
				if(value[4] != 0xEE) {
					value[4] = value[4] + 0x01;
				}
			}
		}
	}
	if(res_type == 2) {	// honor
		if(value[10] != 0xFF) {
			value[10] = value[10] + 0x01;
		} else {
			value[10] = 0x00;
			if(value[11] != 0xFF) {
				value[11] = value[11] + 0x01;
			} else {
				value[11] = 0x00;
				if(value[12] != 0xEE) {
					value[12] = value[12] + 0x01;
				}
			}
		}
	}
	WriteProcessMemory(hProcess, (LPVOID)(addr + GOLDPTR_F), value, 16, NULL);
	return;
}