//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"
#inlcude "wiper.h"
#include "display.h"
#include "ignition.h"
#include "user_interface.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    //initializations of each main subsystem
    ignitionInit();
    wiperInit();
    userInterfaceDisplayInit();
    
    // functionality of the system
    while (true)
    {
        ignitionStateUpdate();
        wModeUpdate();
        intModeUpdate();
        userInterfaceDisplayUpdate();
        delay(DELAY_MS);
    }
}
