//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============
AnalogIn lightSensor(A1);
DigitalOut entryLightLed(D1);
//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============
//=====[Declarations (prototypes) of private functions]========================
void powerToLed()
//=====[Implementations of public functions]===================================

//=====[Implementations of private functions]==================================
void PowerToLed()
{
    entryLightLed = OFF;
    char str[20];
    while (true) {
        float lightSensorReading = lightSensor.read();
        sprintf(str,"light Level: %.2f\r\n", lightSensorReading);
        int stringLength = strlen(str);
        uartUsb.write(str, stringLength);
        if (lightSensorReading>0.5) {
        entryLightLed = ON;
        }
        else
        {
        entryLightLed = OFF;
        }
}
}