//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "ignition.h"

//=====[Declaration of private defines]========================================

#define DEBOUNCE_MS 50

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalIn ignition(BUTTON1);
DigitalIn driverSeat(D14);

DigitalOut engine(LED2);

//=====[Declaration of external public global variables]=======================
int debounce_accumulated_time_ms = 0;
//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void ignitionInit()
{
    // set ignition button to a pulldown resistor
    ignition.mode(PullDown);
    // set dirver's seat pushbutton to a pulldown resistor
    driverSeat.mode(PullDown);

    //the engine should only be on if the the requirements of the ignition subsystem are met
    engine.write(OFF);
    ignitionState = B_OFF;
}

//must  debounce button and set to only send a signal on release 
void ignitionStateUpdate () 
{
    // define variables reading the states of each button
    bool ds = driverSeat.read();
    bool ig = ignition.read();

    if (ignitionState == B_OFF && ig == ON) 
    {
        ignitionState = B_RISING;
        debounce_accumulated_time_ms = 0;
    }
    if (ignitionState == B_ON && ig == OFF) 
    {
        ignitionState = B_FALLING;
        debounce_accumulated_time_ms = 0;
    }
    // prevents bouncing sending multiple upon one button press
    if ((ignitionState == B_RISING) && (debounce_accumulated_time_ms >= DEBOUNCE_MS)) 
    {
        if (ig == ON) {
            ignitionState = B_ON;
        }
        else {
            ignitionState = B_OFF;
        }
    }
    // only register button press upon release
    if ((ignitionState == B_FALLING) && (debounce_accumulated_time_ms >= DEBOUNCE_MS)) 
    {
        if (ig == ON) 
        {
            ignitionState = B_ON;
        }
        else 
        {
            ignitionState = B_OFF;
            if (ds == ON && engine == OFF) 
            {
                engine.write(ON);
                return;
            }
            if (engine == ON) 
            {
                engine.write(OFF);
                wiperMode = W_OFF;
            }
        }
    }
}

//=====[Implementations of private functions]==================================

