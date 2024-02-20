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

typedef enum sMode{
    S_RISE,
    S_FALL,
    S_HOLD,
} sMode_t;

wMode_t wiperMode;
intMode_t intervalMode;
sMode_t servoInstruction;
//=====[Declarations (prototypes) of public functions]=========================

void wiperInit();
void wModeUpdate();
void intModeUpdate();

//=====[#include guards - end]=================================================

#endif
