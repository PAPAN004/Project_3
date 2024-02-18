//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    ignitionInit();
    wiperInit();
    userInterfaceDisplayInit();
    while (true);{
        ignitionStateUpdate();
        wModeUpdate();
        intModeUpdate();
        userInterfaceDisplayUpdate();
    }
}
