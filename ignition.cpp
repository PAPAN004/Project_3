//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "ignition.h"

//=====[Declaration of private defines]========================================

#define DELAY_MS    10
#define DEBOUNCE_MS 50

//=====[Declaration of private data types]=====================================

typedef enum ButtonState {
    B_ON,
    B_RISING,
    B_OFF,
    B_FALLING,
} ButtonState_t;

ButtonState_t ignitionState;

//=====[Declaration and initialization of public global objects]===============

DigitalIn ignition(BUTTON1);
DigitalIn driverSeat(D4);
DigitalOut engine(LED2);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

int debounce_accumulated_time_ms = 0;

//=====[Declarations (prototypes) of private functions]========================

void inputsInit();
void outputsInit();
void delayAccumulate();
void ignitionStateUpdate ();

//=====[Implementations of public functions]===================================
//=====[Implementations of private functions]==================================

void inputsInit()
{
    ignition.mode(PullDown);
    driverSeat.mode(PullDown);
}

void outputsInit()
{
    engine.write(OFF);
}

void delayAccumulate() {
    delay(DELAY_MS);
    debounce_accumulated_time_ms += 10;
}

void ignitionStateUpdate () {
    bool ds = driverSeat.read();
    bool ig = ignition.read();
    if (ignitionState == B_OFF && ig == ON) {
        ignitionState = B_RISING;
        debounce_accumulated_time_ms = 0;
    }
    if (ignitionState == B_ON && ig == OFF) {
        ignitionState = B_FALLING;
        debounce_accumulated_time_ms = 0;
    }
    if ((ignitionState == B_RISING) && (debounce_accumulated_time_ms >= DEBOUNCE_MS)) {
        if (ig == ON) {
            ignitionState = B_ON;
        }
        else {
            ignitionState = B_OFF;
        }
    }
    if ((ignitionState == B_FALLING) && (debounce_accumulated_time_ms >= DEBOUNCE_MS)) {
        if (ig == ON) {
            ignitionState = B_ON;
        }
        else {
            ignitionState = B_OFF;
            if (ds == ON && engine == OFF) {
                engine.write(ON);
                return;
            }
            if (engine == ON) {
                engine.write(OFF);
            }
        }
    }
}
