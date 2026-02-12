/*
 * main.cpp
 *
 *  Created on: Feb 5, 2026
 *      Author: Olayemi
 */

#include <msp430.h>
#include "include/Config.hpp"
using namespace AppConfig;

void main(void){
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer


    Console::init(); // Init uart at 9600 baud rate
    //initialize timer 1 for melody at 1ms : Period 1000 = 1ms at 1Mhz SMCLK
    Timer::init(TA1CTL,TA1CCR0,TA1CCTL0,1000);
    SignalGenerator::init();
    //SignalGenerator::setDutyCycle(500); // 1.65V test

    MainScope::init(OscilloscopeSettings);
    __enable_interrupt();  // enable global interrupt
    __bis_SR_register(GIE);

    while(1){

        __no_operation(); // Place holder for the debugger
    }
}


//ISR
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A1_Sampling_ISR(void){

    //creating ~31Hz Sine Wave at 1ms per step and 32 steps
    SignalGenerator::updateWaveform(0);

    //static uint16_t tickCounter = 0;

    //for 100Hz since the timer is initialized at 1ms
   // if (++tickCounter >= 10){
        MainScope::captureAndStream();  // 1000Hz when tickCounter is commented
       // tickCounter = 0;

   //}
}


