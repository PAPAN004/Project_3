//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "wiper.h"

//=====[Declaration of private defines]========================================

#define W_OFF_TH   0.25
#define W_LOW_TH  0.50
#define W_HIGH_TH   0.75 
#define INT_SHORT_TH  0.33
#define INT_MEDIUM_TH   0.67
#define INT_TIME_UP_DOWN   380

#define PERIOD_SEC              0.02
#define DUTY_MIN                0.023
#define DUTY_MAX                0.059

#define SPEED_INCREMENT         0.001
#define TIME_INCREMENT_HI_MS    5
#define TIME_INCREMENT_LO_MS    18

#define WIPER_UP_POSITION       67.0

#define SHORT_TIME       3000   
#define MEDIUM_TIME      6000
#define LONG_TIME        8000


#define COUNTER_LIMIT        75

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

AnalogIn modePotentiometer(A0);
AnalogIn intPotentiometer(A1);

PwmOut wiper(PF_9);

//=====[Declaration of external public global variables]=======================
int debounce_accumulated_time_ms = 0;
//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

int delay_accumulated_time_ms = 0;

//=====[Declarations (prototypes) of private functions]========================

static void wiper_potentiometer_read();
static void potentiometer_read();
static void activateWiper(int speed);
static void delayAccumulate(int speed);

//=====[Implementations of public functions]===================================

void wiperInit()
{
    wiper.period(PERIOD_SEC);
    wiper.write(DUTY_MIN);
    wiperMode = W_OFF;
    intervalMode = INT_SHORT;
    servoInstruction = S_HOLD;
}


void wModeUpdate() 
{
    if (engine == ON) 
    {
        wiper_potentiometer_read();
    }

    switch ( wiperMode )
    {
    case(W_OFF):
        if (servoInstruction != S_HOLD) 
        {
            activateWiper(TIME_INCREMENT_LO_MS);
        }
            break;

    case(W_LO):
        if (engine == ON)
        {
            activateWiper(TIME_INCREMENT_LO_MS);
        }
        break;
        
    case(W_HIGH):
        if (engine == ON)
        {
            activateWiper(TIME_INCREMENT_HI_MS);
        }
        break;

    case(W_INT):
        if (engine == ON)
        {
            timer_int_mode_ms += 10;
            intModeUpdate();
        }
        break;

    default:
        wiperMode = W_OFF;
        
    }
}

void potentiometer_read()
{
    float f = intPotentiometer.read();
    if (f < INT_SHORT_TH)
    {
        intervalMode = INT_SHORT;
    }
    else if (f > INT_MEDIUM_TH)
    {
        intervalMode = INT_LONG;
    }
    else
    {
        intervalMode = INT_MEDIUM;
    }
}

void wiper_potentiometer_read() 
{
    float f = modePotentiometer.read();

    if (f > W_HIGH_TH) 
    {
        wiperMode = W_INT;
    } 
    else if (f > W_LOW_TH)
    {
        wiperMode = W_HIGH;
    } 
    else if (f >= W_OFF_TH) 
    {
        wiperMode = W_LO;
    } 
    else 
    {
        wiperMode = W_OFF;
    }
}

void intModeUpdate()
{
    static int function_counter = 0;
    potentiometer_read();
    if (wiperMode == W_INT) 
    {    
        switch ( intervalMode )
        {
        case (INT_SHORT) :
            if (timer_int_mode_ms >= SHORT_TIME) 
            {
                activateWiper(TIME_INCREMENT_LO_MS);
                function_counter ++;
                if(function_counter == COUNTER_LIMIT)
                {
                    timer_int_mode_ms = 0;
                    function_counter = 0;
                }
            }
            else
            {
                wiper.write(DUTY_MIN);
                timer_int_mode_ms += 10;
            }
            break;
            
        case (INT_MEDIUM):
            if (timer_int_mode_ms >= MEDIUM_TIME) 
            {
                    activateWiper(TIME_INCREMENT_LO_MS);
                    function_counter ++;
                    if(function_counter == COUNTER_LIMIT)
                    {
                        timer_int_mode_ms = 0;
                        function_counter = 0;
                    }
                    
            }
            else{
                wiper.write(DUTY_MIN);
                timer_int_mode_ms += 10;
            }
            break;

        case (INT_LONG):
            if (timer_int_mode_ms >= LONG_TIME) {
                    activateWiper(TIME_INCREMENT_LO_MS);
                    function_counter ++;
                    if(function_counter == COUNTER_LIMIT){
                        timer_int_mode_ms = 0;
                        function_counter = 0;
                
                    }
            }
            else{
                wiper.write(DUTY_MIN);
                timer_int_mode_ms += 10;
            }
            break;
        }
    }
}



void activateWiper(int speed)
{
    static float rise_increment = DUTY_MIN;
    static float fall_increment = DUTY_MAX;
    
    switch (servoInstruction)
    {

    case(S_HOLD):
        servoInstruction = S_RISE;
        break;

    case(S_RISE):

        rise_increment = rise_increment + SPEED_INCREMENT;
        wiper.write(rise_increment);
        delayAccumulate(speed);
         
        if ((rise_increment >= DUTY_MAX) && (delay_accumulated_time_ms >= INT_TIME_UP_DOWN))
        {    
            servoInstruction = S_FALL;
            delay_accumulated_time_ms = 0;
            rise_increment = DUTY_MIN;
        }
        break;
        
    case(S_FALL):
        //replace this with incrementor
        fall_increment = fall_increment - SPEED_INCREMENT;  
        wiper.write(fall_increment);   
        delayAccumulate(speed);

        if ((fall_increment < DUTY_MIN ) && (delay_accumulated_time_ms >= INT_TIME_UP_DOWN))
        {
            servoInstruction = S_HOLD;
            delay_accumulated_time_ms = 0;
            fall_increment = DUTY_MAX;
        }
        break;

    default:
        servoInstruction = S_FALL;
        break;
    }
}

void delayAccumulate(int increment) 
{
    delay(increment);
    delay_accumulated_time_ms += 10;
    debounce_accumulated_time_ms += 10;
}
