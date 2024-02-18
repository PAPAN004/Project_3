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

#define PERIOD_SEC              0.02
#define DUTY_MIN                0.021
#define DUTY_MAX                0.059

#define SPEED_INCREMENT         0.001

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

AnalogIn modePotentiometer(A0);
AnalogIn intPotentiometer(A1);

PwmOut wiper(PF_9);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

static void servoRiseUpdate(int speed);
static void servoFallUpdate(int speed);
//=====[Implementations of public functions]===================================

void servoInit()
{
    servo.period(PERIOD_SEC);
    servo.write(DUTY_MIN);
}

static void servoRiseUpdate(int speed)
{
    static float pos_rise = 0.021;
    pos_rise = pos_rise + SPEED_INCREMENT;
    servo.write(pos_rise);
    
    //replace this with incrementor
    delay(speed);    
    
    if pos_rise >= DUTY_MAX
    {
        pos_rise = 0.021;
    }
}

static void servoFallUpdate(int speed)
{
    static float pos_fall = 0.059;
    pos_fall = pos_fall - SPEED_INCREMENT;        
    servo.write(pos_fall);
    
    //replace this with incrementor
    delay(speed);
    
    if pos_fall <= DUTY_MIN 
    {
        pos_fall = 0.059;
    }

}
void wModeUpdate() {
    float f = modePotentiometer.read();
    // pot reading below 0.25, wipers set to off
    if (f <= W_OFF_TH)
    {   
        wiperMode = W_OFF;
    }
    // pot reading is between 0.25 and 0.50, wipers set to low
    else if (f > W_OFF_TH && f <= W_HIGH_TH)
    {
        wiperMode = W_LOW;
    }
    // pot reading is between 0.50 and 0.75, wipers set to high
    else if (f > W_HIGH_TH && f <= W_INT_TH)
    {
        wiperMode = W_HIGH;
    }
    // pot reading is above 0.75, wipers set to interval
    else if (f > W_INT_TH)
    {
        wiperMode = W_INT;
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


