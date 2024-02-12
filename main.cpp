//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    intMode = INT_SHORT;
    wMode = W_OFF;
    ignitionInit();
    wiperInit();
    while (true);{
        delayAccumulate();
        ignitionStateUpdate();
        wModeUpdate();
        intModeUpdate();
    }
}
