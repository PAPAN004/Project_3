//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "wiper.h"
//=====[Declaration of private defines]========================================

#define W_OFF_TH   0.25
#define W_LO_TH  0.50
#define W_HIGH_TH   0.75 
#define INT_SHORT_TH  0.3
#define INT_MEDIUM_TH   0.7 
#define DUTY_MIN 0.017
#define DUTY_MAX 0.129

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

AnalogIn modePotentiometer(A0);
AnalogIn intPotentiometer(A1);

PwmOut wiper(PF_9);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void wModeUpdate() {
    float f = potentiometer.read();
    if (wMode == W_OFF) {
        if (f > W_OFF_TH) {
            wMode = W_LO;
        }
        return;
    }
    if (wMode == W_LO) {
        if (f < W_OFF_TH) {
            wMode = W_OFF;
        }
        if (f > W_LO_TH) {
            wMode = W_HIGH;
        }
        return;
    }
    if (wMode == W_HIGH) {
        if (f < W_LO_TH) {
            wMode = W_LO;
        }
        if (f > W_HIGH_TH) {
            wMode = W_INT;
        }
        return;
    if (wMode == W_INT) {
        if (f < W_HIGH_TH) {
            wMode = W_HIGH;
        }
        return;
    }
}
}

void intModeUpdate() {
    float f = intPotentiometer.read();
    if (wMode == W_INT) {
        if (intMode == INT_SHORT) {
            if (f > INT_SHORT_TH) {
                intMode = INT_MEDIUM;
            }
            return;
        }
        if (intMode == INT_MEDIUM) {
            if (f < INT_SHORT_TH) {
                INT_MODE = INT_SHORT;
            }
            if (f > INT_MEDIUM_TH) {
                intMode = INT_LONG;
            }
            return;
        }
        if (INT_Mode == INT_LONG) {
            if (f < INT_MEDIUM_TH) {
                intMode = INT_MEDIUM;
            }
            return;
        }
    }
}

//=====[Implementations of private functions]==================================
