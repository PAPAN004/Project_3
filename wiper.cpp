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

static void wActivated(int speed);

//=====[Implementations of public functions]===================================

void wiperInit()
{
    servo.period(PERIOD_SEC);
    servo.write(DUTY_MIN);
    wiperMode = W_OFF;
    intervalMode = SHORT;
}


void wModeUpdate() {
    float f = modePotentiometer.read();

    switch ( wiperMode )
    {
    case(W_OFF):
        // pot reading above 0.25 in this state, wipers set to low
        if (f > W_OFF_TH)
        {   
            wiperMode = W_LOW;
        }
        break;
    
    case(W_LOW):

        // pot reading below 0.25 in this state, wipers set to off
        if (f < W_OFF_TH)
        {
            wiperMode = W_OFF;
        }
        // pot reading above 0.50 in this state, wipers set to high
        else if (f > W_LO_TH)
        {
            wiperMode = W_HIGH;
        }
        break;

    case(W_HIGH):
        // pot reading is below 0.50 in this state, wipers set to low
        if( f < W_LO_TH)
        {
            wiperMode = W_LOW;
        }
        // pot reading is above 0.75 in this state, wipers set to interval
        else if (f > W_HIGH_TH)
        {
            wiperMode = W_INT;
        }
        break;
        
    default:
        wiperMode = W_OFF;
    }
}

void intModeUpdate()
{
    float f = intPotentiometer.read();
    if (wiperMode == W_INT) 
    {    
        switch ( intervalMode )
        {
        case (INT_SHORT) :
            if (f > INT_SHORT_TH) 
            {
                intervalMode = INT_MEDIUM;
            }
            break;
            
        case (INT_MEDIUM):
            if (f < INT_SHORT_TH) 
            {
                intervalMode = INT_SHORT;
            }
            else if (f > INT_MEDIUM_TH) 
            {
                intervalMode = INT_LONG;
            }
            break;

        case (INT_LONG):
            if (f < INT_MEDIUM_TH) 
            {
                intervalMode = INT_MEDIUM;
            }
            break;

        default:
            intervalMode = INT_SHORT;
            break;
        }
    }
}

//=====[Implementations of private functions]===================================

static void wActivated(int speed)
{
    static bool servoInstruction = true;
    static float rise_increment = 0.021;
    static float fall_increment = 0.059;
    
    switch (servoInstruction)
    {
    case(true):
        //replace this with incrementor
        delay(speed); 
        rise_increment = rise_increment + SPEED_INCREMENT;
        servo.write(rise_increment);
    
        if (pos_rise > DUTY_MAX)
        {    
            servoInstruction = false;
            rise_increment = 0.021;
            break;
        }
    
    case(false):
        //replace this with incrementor
        delay(speed); 
        fall_increment = fall_increment - SPEED_INCREMENT;  
        servo.write(fall_increment);   
    
        if (fall_increment < DUTY_MIN )
        {
            servoInstruction = true
            fall_increment = 0.059;
            break;
        }
    default:
        servoInstruction = false;
        break;
    }
}

    
