//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    intervalMode = INT_SHORT;
    wiperMode = W_OFF;
    ignitionState = B_OFF;
    ignitionInit();
    wiperInit();
    userInterfaceDisplayInit();
    while (true);{
        delayAccumulate();
        ignitionStateUpdate();
        wModeUpdate();
        intModeUpdate();
    }
}
