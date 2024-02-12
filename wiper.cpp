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
    float f = modePotentiometer.read();
    if (wiperMode == W_OFF) {
        if (f > W_OFF_TH) {
            wiperMode = W_LO;
        }
        return;
    }
    if (wiperMode == W_LO) {
        if (f < W_OFF_TH) {
            wiperMode = W_OFF;
        }
        if (f > W_LO_TH) {
            wiperMode = W_HIGH;
        }
        return;
    }
    if (wiperMode == W_HIGH) {
        if (f < W_LO_TH) {
            wiperMode = W_LO;
        }
        if (f > W_HIGH_TH) {
            wiperMode = W_INT;
        }
        return;
    if (wiperMode == W_INT) {
        if (f < W_HIGH_TH) {
            wiperMode = W_HIGH;
        }
        return;
    }
}
}

void intModeUpdate() {
    float f = intPotentiometer.read();
    if (wiperMode == W_INT) {
        if (intervalMode == INT_SHORT) {
            if (f > INT_SHORT_TH) {
                intervalMode = INT_MEDIUM;
            }
            return;
        }
        if (intervalMode == INT_MEDIUM) {
            if (f < INT_SHORT_TH) {
                intervalMode = INT_SHORT;
            }
            if (f > INT_MEDIUM_TH) {
                intervalMode = INT_LONG;
            }
            return;
        }
        if (intervalMode == INT_LONG) {
            if (f < INT_MEDIUM_TH) {
                intervalMode = INT_MEDIUM;
            }
            return;
        }
    }
}

//=====[Implementations of private functions]==================================
