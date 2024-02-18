//=====[#include guards - begin]===============================================

#ifndef _WIPER_H_
#define _WIPER_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

// this enumarated data type is used to tell the display module what state the wMode potentiometer
typedef enum wMode {
    W_HIGH,
    W_LO,
    W_INT,
    W_OFF,
} wMode_t;

// this enumarated data type is used to tell the display module what state the intMode potentiometer
typedef enum intMode {
    INT_SHORT,
    INT_MEDIUM,
    INT_LONG,
} intMode_t;

typedef enum servoState {
    
}

wMode_t wiperMode;
intMode_t intervalMode;

//=====[Declarations (prototypes) of public functions]=========================

void servoInit();
void servoRiseUpdate();
void servoFallUpdate();
void wModeUpdate();
void intModeUpdate();

//=====[#include guards - end]=================================================

#endif
