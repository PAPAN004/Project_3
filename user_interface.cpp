#include "mbed.h"
#include "arm_book_lib.h"

#include "user_interface.h"
#include "display.h"
#include "wiper.h"

//=====[Declaration of private defines]========================================

#define DISPLAY_REFRESH_TIME_MS 1000

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============
//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============
//=====[Declaration and initialization of private global variables]============
//=====[Declarations (prototypes) of private functions]========================

void userInterfaceDisplayInit();
void userInterfaceDisplayUpdate();

//=====[Implementations of public functions]===================================
//=====[Implementations of private functions]==================================

//this function initializes the LCD display with the words "Wiper-Mode:" and "Int-Speed:" prior to any information being fed into it
void userInterfaceDisplayInit()
{
    displayInit();
     
    displayCharPositionWrite ( 0,0 );
    displayStringWrite( "Wiper-Mode:" );
    
    displayCharPositionWrite ( 0,1 );
    displayStringWrite( "Int-Speed:" );
}

//upon any changes in the movement of the servo, the LCD display will be updated to reflect these changes
void userInterfaceDisplayUpdate()
{
    static int accumulatedDisplayTime = 0;
    if( accumulatedDisplayTime >= DISPLAY_REFRESH_TIME_MS ) 
    {

        accumulatedDisplayTime = 0;

        if (wiperMode == W_OFF)
        {
        displayCharPositionWrite ( 12,0 );
        displayStringWrite( "Off " );
        displayCharPositionWrite ( 10,1 );
        displayStringWrite( "      " );
        }

        if (wiperMode == W_HIGH)
        {
        displayCharPositionWrite ( 12,0 );
        displayStringWrite( "High" );
        displayCharPositionWrite ( 10,1 );
        displayStringWrite( "      " );
        }

        if (wiperMode == W_LO)
        {
        displayCharPositionWrite ( 12,0 );
        displayStringWrite( "Low " );
        displayCharPositionWrite ( 10,1 );
        displayStringWrite( "      " );
        }

        if (wiperMode == W_INT)
        {
            displayCharPositionWrite ( 12,0 );
            displayStringWrite( "Int " );
            if (intervalMode == INT_SHORT)
            {
                displayCharPositionWrite ( 10,1 );
                displayStringWrite( "Short " );
            }

            if (intervalMode == INT_MEDIUM)
            {
                displayCharPositionWrite ( 10,1 );
                displayStringWrite( "Medium" );
            }

            if (intervalMode == INT_LONG)
            {
                displayCharPositionWrite ( 10,1 );
                displayStringWrite( "Long  " );
            }
        }


    } else 
    {
        accumulatedDisplayTime = accumulatedDisplayTime + DELAY_MS;        
    } 
}
