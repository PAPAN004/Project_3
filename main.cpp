//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    intervalMode = INT_SHORT;
    wiperMode = W_OFF;
    ignitionInit();
    wiperInit();
    while (true);{
        delayAccumulate();
        ignitionStateUpdate();
        wModeUpdate();
        intModeUpdate();
    }
}
