/*
 * SignalGen.cpp
 *
 *  Created on: Feb 9, 2026
 *      Author: Olayemi
 */


#include <msp430.h>
#include "include/Timer.hpp"

namespace Hardware{
    namespace SignalGen{
        //LUT for 32-Point Sine wave
    static const uint16_t sineTable[32] = {
       500, 597, 691, 777, 853, 915, 961, 990,
       1000, 990, 961, 915, 853, 777, 691, 597,
       500, 402, 308, 222, 146, 84, 38, 9,
       0, 9, 38, 84, 146, 222, 308, 402
    };

    static uint8_t currentIndex = 0;

        void init(){
            P1DIR |= BIT6;
            P1SEL |= BIT6; //p.6 PWM TA0.1
            P1SEL2 &= ~BIT6;

            //using timer A0 as A1 was used for Scope
            //Period of 1000 at 1MHz = 1khz PWM frequency
            TimerA<TimerClock::SMCLK>::setupPWM(TA0CTL, TA0CCR0, TA0CCR1, TA0CCTL1, 1000);
        }

        void setVoltage(uint16_t milliVolts){
            //Convert 0-3300mV to 0-1000 Duty Cycle-> (mV * Preriod)/Vcc
            uint32_t duty = ((uint32_t)milliVolts * 1000) / 3300;
            TA0CCR1 = (uint16_t)duty;
        }

        void setDutyCycle(uint16_t duty){
            if(duty >1000) duty = 1000;
            TA0CCR1 = duty;
        }

        void updateWaveform(uint8_t type, uint8_t gain){
            uint32_t sample = 0;

            switch(type){
            case 0: //SINE WAVE
                sample = sineTable[currentIndex];
                //currentIndex = (currentIndex + 1) % 32;
                break;
            case 1: //SQUARE WAVE
                sample = (currentIndex < 16) ? 1000 : 0; //halve 100% half 0 duty cycle
                //currentIndex = (currentIndex + 1) % 32;
                break;
            case 2: // SAWTOOTH WAVE
                sample = currentIndex * 31; // 31 * 32 steps avoiding floating point
                //currentIndex = (currentIndex + 1) % 32;
                break;
            case 3: // TRIANGULAR WAVE
                sample = (currentIndex < 16) ? (currentIndex * 62) : ((31 - currentIndex) *62);
                //currentIndex = (currentIndex + 1) % 32;
                break;
            case 4: // TRAPEZOID
                if (currentIndex < 8) {
                    // Rise: 0 to 7 * 125 = 875 (roughly 1000)
                    sample = currentIndex * 125;
                }
                else if (currentIndex < 16) {
                    // Hold High
                    sample = 1000;
                }
                else if (currentIndex < 24) {
                    // Fall: (23 - 16) * 125... we subtract from 1000
                    sample = 1000 - ((currentIndex - 16) * 125);
                }
                else {
                    // Hold Low
                    sample = 0;
                }
                //currentIndex = (currentIndex + 1) % 32;
                break;
            }

            TA0CCR1 = (uint16_t)(((uint32_t)sample * gain) / 100);

            currentIndex = (currentIndex + 1) % 32;

        }
    }
}

