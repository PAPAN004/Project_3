//=====[#include guards - begin]===============================================

#ifndef _IGNITION_H_
#define _IGNITION_H_

//=====[Declaration of public defines]=========================================

#define DELAY_MS    10

//=====[Declaration of public data types]======================================

typedef enum ButtonState {
    B_ON,
    B_RISING,
    B_OFF,
    B_FALLING,
} ButtonState_t;

ButtonState_t ignitionState;

//=====[Declarations (prototypes) of public functions]=========================

void ignitionInit();
void ignitionStateUpdate ();

//=====[#include guards - end]=================================================

#endif
