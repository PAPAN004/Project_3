//=====[#include guards - begin]===============================================

#ifndef _WIPER_H_
#define _WIPER_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

// this enumarated data type is used to tell the system what mode the wiper-mode is in
typedef enum wMode {
    W_HIGH,
    W_LO,
    W_INT,
    W_OFF,
} wMode_t;

// this enumarated data type is used to tell the system what mode the intermittent-mode in
typedef enum intMode {
    INT_SHORT,
    INT_MEDIUM,
    INT_LONG,
} intMode_t;
// this enumarated data type is used to tell the system what point the servo motor is at
typedef enum sMode{
    S_RISE,
    S_FALL,
    S_HOLD,
} sMode_t;

//alternate names for each enumerated data type to increase the readability of all code used
wMode_t wiperMode;
intMode_t intervalMode;
sMode_t servoInstruction;
//=====[Declarations (prototypes) of public functions]=========================

void wiperInit();
void wModeUpdate();
void intModeUpdate();

//=====[#include guards - end]=================================================

#endif
