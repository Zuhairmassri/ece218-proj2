//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "headlight.h"
#include "ignition.h"
#include "ldr_sensor.h"


//=====[Declaration of private defines]========================================

#define LIGHT_LIMIT_LEVEL                  0.50
#define BEAMS_ON                           0.80
#define BEAMS_OFF                          0.20
#define SWITCH_OFF_DELAY                   2000
#define SWITCH_ON_DELAY                    1000

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut leftBeam(D7);
DigitalOut rightBeam(D6);
AnalogIn   mode(A0);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static bool nightDetected                  = OFF;
static bool nightState                     = OFF;

//=====[Declarations (prototypes) of private functions]========================

static void toggleLight();

//=====[Implementations of public functions]===================================

void beamsInit(){
    ldrSensorInit();
}

void beamsActivationUpdate(){
    if(ignitionState()){
        if (modeRead() >= BEAMS_ON){
            turnHeadlightsOn();
        } else if(modeRead() <= BEAMS_OFF){
            turnHeadlightsOff();
        } else{
        nightDetected = ldrSensorRead() < LIGHT_LIMIT_LEVEL;
        if ( nightDetected ) {
            delay(SWITCH_ON_DELAY);
            turnHeadlightsOn();
        } else {
            delay(SWITCH_ON_DELAY);
            turnHeadlightsOff();
            }
        }   
    }else{
        turnHeadlightsOff();
    }
}


//=====[Implementations of private functions]==================================

void turnHeadlightsOn(){
        leftBeam = ON;
        rightBeam = ON;
}

void turnHeadlightsOff(){
        leftBeam = OFF;
        rightBeam = OFF;
}

bool ldrDetectorStateRead(){
    return nightDetected;
}

bool nightDetectedRead(){
    return nightState;
}

float modeRead()
{
    return mode.read();
}

