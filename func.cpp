//
// Created by RedEric on 04/07/2024.
//

#include "func.h"

using namespace std;

DWORD GetPointerAddress(HWND hwnd, DWORD address, vector<DWORD> offsets)
{
    DWORD pID = NULL;
    GetWindowThreadProcessId(hwnd, &pID);
    HANDLE phandle = NULL;
    phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
    if (phandle == INVALID_HANDLE_VALUE || phandle == NULL);

    DWORD offset_null = NULL;
    ReadProcessMemory(phandle, (LPVOID*)address, &offset_null, sizeof(offset_null), 0);
    DWORD pointeraddress = offset_null; // the address we need
    for (int i = 0; i < offsets.size() - 1; i++) // we dont want to change the last offset value so we do -1
    {
        ReadProcessMemory(phandle, (LPVOID*)(pointeraddress + offsets.at(i)), &pointeraddress, sizeof(pointeraddress), 0);
    }
    return pointeraddress += offsets.at(offsets.size() - 1);
}
int getValueInt(HWND hwnd, DWORD address) {
    int ref = 1234;
    DWORD pID = NULL; // Game process ID
    GetWindowThreadProcessId(hwnd, &pID);
    HANDLE phandle = NULL;
    phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
    ReadProcessMemory(phandle, (void*)address,&ref,sizeof(int), 0);
    return ref;
}

float getValueFloat(HWND hwnd, DWORD address) {
    float ref = 1234;
    DWORD pID = NULL; // Game process ID
    GetWindowThreadProcessId(hwnd, &pID);
    HANDLE phandle = NULL;
    phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
    ReadProcessMemory(phandle, (void*)address,&ref,sizeof(float), 0);
    return ref;
}


