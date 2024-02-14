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
static void userInterfaceDisplayInit();
static void userInterfaceDisplayUpdate();
//=====[Implementations of public functions]===================================
//=====[Implementations of private functions]==================================
static void userInterfaceDisplayInit()
{
    displayInit();
     
    displayCharPositionWrite ( 0,0 );
    displayStringWrite( "Wiper-Mode:" );
    
    displayCharPositionWrite ( 0,1 );
    displayStringWrite( "Int-Speed:" );
}

static void userInterfaceDisplayUpdate()
{
    static int accumulatedDisplayTime = 0;
    
    if( accumulatedDisplayTime >=
        DISPLAY_REFRESH_TIME_MS ) {

        accumulatedDisplayTime = 0;

        if (wiperMode == W_OFF){
        displayCharPositionWrite ( 12,0 );
        displayStringWrite( "Off" );
        }

        if (wiperMode == W_HIGH){
        displayCharPositionWrite ( 12,0 );
        displayStringWrite( "High" );
        }

        if (wiperMode == W_LO){
        displayCharPositionWrite ( 12,0 );
        displayStringWrite( "Low" );
        }

        if (wiperMode == W_INT){
            if (intervalMode == INT_SHORT){
                displayCharPositionWrite ( 12,1 );
                displayStringWrite( "Short" );
            }

            if (intervalMode == INT_MEDIUM){
                displayCharPositionWrite ( 12,1 );
                displayStringWrite( "Medium" );
            }

            if (intervalMode == INT_LONG){
                displayCharPositionWrite ( 12,1 );
                displayStringWrite( "Long" );
            }
        }


    } else {
        accumulatedDisplayTime =
            accumulatedDisplayTime + SYSTEM_TIME_INCREMENT_MS;        
    } 
}
