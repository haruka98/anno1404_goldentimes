#ifndef MAIN_HPP
#define MAIN_HPP

#define GOLDPTR_A 0x00ED92E8
#define GOLDPTR_B 0x34
#define GOLDPTR_C 0xE8
#define GOLDPTR_D 0x50
#define GOLDPTR_E 0x0
#define GOLDPTR_F 0xA0

DWORD pid = 0;

HANDLE open_process_mem(char* process_window_title);
HANDLE open_process_mem_pid(DWORD set_pid);
void close_process_mem(HANDLE hProcess);
uintptr_t GetModuleBaseAddress(DWORD procId, const char* modName);
void inc_res(HANDLE hProcess, int res_type);

#endif