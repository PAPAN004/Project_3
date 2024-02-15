//=====[#include guards - begin]===============================================

#ifndef _WIPER_H_
#define _WIPER_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

typedef enum wMode {
    W_HIGH,
    W_LO,
    W_INT,
    W_OFF,
} wMode_t;

typedef enum intMode {
    INT_SHORT,
    INT_MEDIUM,
    INT_LONG,
} intMode_t;


wMode_t wiperMode;
intMode_t intervalMode;

//=====[Declarations (prototypes) of public functions]=========================

void servoInit();
void wModeUpdate();
void intModeUpdate();

//=====[#include guards - end]=================================================

#endif
