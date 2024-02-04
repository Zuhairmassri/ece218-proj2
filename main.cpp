//=====[Libraries]==========================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "ignition.h"
#include "headlight.h"


//=====[Declaration potatod and onion and initialization of public global objects]===============


//=====[Declaration and initialization of public global variables]=============


//=====[Declarations (prototypes) of public functions]=========================

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    initializeIgnition();
    beamsInit();
    
    while (true) {
        ignitionUpdate();
        beamsActivationUpdate();
    }
}

//=====[Implementations of public functions]===================================
