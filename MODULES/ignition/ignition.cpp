//=====[Libraries]==========================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "ignition.h"


//=====[Declaration potatod and onion and initialization of public global objects]===============

DigitalIn ignitionButton(BUTTON1);

DigitalIn driverSeat(D4);

DigitalOut greenLed(LED1);
DigitalOut blueLed(LED2);

DigitalInOut sirenPin(PE_10);

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

//=====[Declaration and initialization of public global variables]=============

bool welcomeMessageSent = false;
bool ignitionLockOut = false;



//=====[Declarations (prototypes) of public functions]=========================

void inputsInit();
void outputsInit();

void welcomeMessage();
void driverSeatUpdate();
void ignitionUpdate();

//=====[Main function, the program entry point after power on or reset]========


//=====[Implementations of public functions]===================================

void initializeIgnition()
{
    inputsInit();
    outputsInit();
    
}

void inputsInit() {
    driverSeat.mode(PullDown);
    sirenPin.mode(OpenDrain);
    sirenPin.input();
}

void outputsInit() {
    greenLed = OFF;
    blueLed = OFF;
}

void welcomeMessage() {
    if (!welcomeMessageSent && driverSeat) {
        uartUsb.write( "Welcome to enhanced alarm system model 218-W24\r\n", 48);
        welcomeMessageSent = true;
    }

    if (!driverSeat && !blueLed){
        welcomeMessageSent = !welcomeMessageSent;

    }
}

void driverSeatUpdate() {
    if (driverSeat && !ignitionLockOut) {
        greenLed = ON;
    }
    else {
        greenLed = OFF;
    }
}

bool ignitionState(){
    return ignitionLockOut;
}

void ignitionUpdate() {
    welcomeMessage();
    driverSeatUpdate();
    if (ignitionButton) {
        if (greenLed == ON && !ignitionLockOut) {
            greenLed = OFF;
            blueLed = ON;
            uartUsb.write("Engine started\r\n", 16);
            ignitionLockOut = ON;
        }
        else if (!ignitionLockOut) {
            sirenPin.output();
            sirenPin = LOW;
            uartUsb.write( "Ignition inhibited\r\n", 20);
            if (!driverSeat){
                uartUsb.write( "Driver seat not occupied\r\n", 26);
            }
        }
        else if (ignitionLockOut){
            if (ignitionButton){
                ignitionLockOut = OFF;
                if(driverSeat){
                    greenLed = ON;
                }
                blueLed = OFF;
                uartUsb.write("Engine OFF\r\n", 12);
            }
        }
    }
}
