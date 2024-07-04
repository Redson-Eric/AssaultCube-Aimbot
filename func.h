//
// Created by RedEric on 04/07/2024.
//

#include <iostream>
#include <string>
#include <windows.h>
#include <sstream>
#include<vector>
#include <cmath>
using namespace std;

#ifndef FUNC_H
#define FUNC_H

DWORD GetPointerAddress(HWND hwnd, DWORD address, vector<DWORD> offsets);
int getValueInt(HWND hwnd, DWORD address);
float getValueFloat(HWND hwnd, DWORD address);

#endif //FUNC_H
