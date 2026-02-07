/*
 * main.cpp
 *
 *  Created on: Feb 5, 2026
 *      Author: Olayemi
 */

#include "Config.hpp"
using namespace AppConfig;

void main(void){
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

    MainScope::init(OscilloscopeSettings);

    __enable_interrupt();  // enable global interrupt

    while(1){

        __no_operations(); // Place holder for the debugger
    }
}


//ISR
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A1_Sampling_ISR(void){
    MainScope::captureAndStream();
}


