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