#include <iostream>
#include <string>
#include <windows.h>
#include <sstream>
#include<vector>
#include <cmath>
#include "func.h"

using namespace std;

DWORD pid;
DWORD localPlayer = 0x57e0a8;
DWORD entityArray = 0x58AC04;
DWORD playerNumber = 0x591fd4;
DWORD entitySpacement = 0x04;
/////// DATA //////////////
struct Player {
    DWORD posXAddress;
    DWORD posYAddress;
    DWORD angleX;
    DWORD angleY;
    DWORD posZAddress;
    DWORD hpAddress;
    DWORD ammoAddress;
    DWORD XrotAddress;
    DWORD YrotAddress;
    DWORD nameAddress;

    void show() {
        cout<<hex<<posXAddress<<endl;
        cout<<hex<<posYAddress<<endl;
        cout<<hex<<posZAddress<<endl;
        cout<<hex<<hpAddress<<endl;
        cout<<hex<<ammoAddress<<endl;
        cout<<hex<<XrotAddress<<endl;
        cout<<hex<<YrotAddress<<endl;
    }
};

struct Other {
    DWORD healthAddress;
    DWORD posXAddress;
    DWORD posYAddress;
    DWORD posZAddress;
    DWORD nameAddress;
};

///////////////////////////////////////////////////


int main() {
    cout<<"----------------------------------------------"<<endl;
    HWND wind = FindWindowA(NULL, "AssaultCube");
    GetWindowThreadProcessId(wind, &pid);
    HANDLE handler = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    // Player Data
    Player playerLocal;

    vector<Other> botList;
    vector<DWORD> espace = {0x04};
    int ammoHack = 30;

    for(;;) {

        if(GetKeyState('A') < 0) {
            playerLocal.posXAddress = GetPointerAddress(wind, localPlayer, {0x4});
            playerLocal.posYAddress = GetPointerAddress(wind, localPlayer, {0x8});
            playerLocal.posZAddress = GetPointerAddress(wind, localPlayer, {0xc});
            playerLocal.angleX = GetPointerAddress(wind, localPlayer, {0x34});
            playerLocal.angleY = GetPointerAddress(wind, localPlayer, {0x38});
            playerLocal.ammoAddress = GetPointerAddress(wind, localPlayer, {0x138});
            playerLocal.nameAddress = GetPointerAddress(wind, localPlayer, {0x205});
            playerLocal.hpAddress = GetPointerAddress(wind, localPlayer, {0xEC});
            playerLocal.XrotAddress = GetPointerAddress(wind, localPlayer, {0x34});
            playerLocal.YrotAddress = GetPointerAddress(wind, localPlayer, {0x38});
            int nbrEntity = getValueInt(wind, playerNumber);
            cout<<"Entity Nbr  ==================== "<<nbrEntity<<endl;
            for(int i = 0 ;i<5;i++) {
                Other bot;
                bot.posXAddress = GetPointerAddress(wind, entityArray, {espace[0],0x4});
                bot.posYAddress = GetPointerAddress(wind, entityArray, {espace[0],0x8});
                bot.posZAddress = GetPointerAddress(wind, entityArray, {espace[0],0xc});
                bot.healthAddress = GetPointerAddress(wind, entityArray, {espace[0],0xEC});
                bot.nameAddress = GetPointerAddress(wind, localPlayer, {0x205});

                if(getValueInt(wind, bot.healthAddress) > 0 && getValueInt(wind, bot.healthAddress) <= 100) {

                    botList.push_back(bot);
                    cout<<"ADD"<<botList.size()<<endl;
                }
                else {
                    cout<<"Nope"<<endl;
                    cout<<"DOadd"<<botList.size()<<endl;
                }
                espace[0] += 0x04;
                cout<<"Espace "<<hex<<espace[0]<<endl;

            }
            cout<<"Nbr entity"<<botList.size()<<endl;
            ///
            int closest = 0;
            float closestRotX = 0;
            float closestRotY = 0;
            float maxDist = 99999;
            //
            for (Other bot: botList) {

                //
                float playerX = getValueFloat(wind, playerLocal.posXAddress);
                float playerY = getValueFloat(wind, playerLocal.posYAddress);
                float playerZ = getValueFloat(wind, playerLocal.posZAddress);
                float botX = getValueFloat(wind, bot.posXAddress);
                float botY = getValueFloat(wind, bot.posYAddress);
                float botZ = getValueFloat(wind, bot.posZAddress) - 1;
                int botHp = getValueInt(wind, bot.healthAddress);
                float a = botX - playerX;
                float b = botY - playerY;
                float c = sqrt((a*a + b*b));//hyp
                float height = botZ - playerZ;//opp

                float angleXX = atan2(b, a)*180/M_PI + 90.00 ;
                float angleYY = atan(height/c)*180/M_PI;
                if(maxDist >= c && botHp > 0) {
                    maxDist = c;
                    closest = getValueInt(wind, bot.healthAddress);
                    closestRotX = angleXX;
                    closestRotY = angleYY;
                }
                //WriteProcessMemory(handler, (void*)playerLocal.angleX, &angleXX, sizeof(float), 0);
                //WriteProcessMemory(handler, (void*)playerLocal.angleY, &angleYY, sizeof(float), 0);

            }
            cout<<"Closest Health : "<<closest<<endl;

            if(getValueInt(wind, playerNumber)>0) {
                WriteProcessMemory(handler, (void*)playerLocal.ammoAddress, &ammoHack, sizeof(int), 0);
                WriteProcessMemory(handler, (void*)playerLocal.angleX, &closestRotX, sizeof(float), 0);
                WriteProcessMemory(handler, (void*)playerLocal.angleY, &closestRotY, sizeof(float), 0);
            }
            espace[0] = 0x4;
            botList.clear();

        }
        else {

            continue;
        }

    }


    return 0;
}
//B9D9410
