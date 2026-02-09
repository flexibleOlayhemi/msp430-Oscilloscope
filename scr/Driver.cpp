/*
 * Driver.cpp
 *
 *  Created on: Feb 5, 2026
 *      Author: Olayemi
 */

#include <msp430.h>
#include "include/Driver.hpp"
#include <cstdio>


namespace Hardware{
 namespace Scope{

     void init(const ScopeConfig& cfg){// ADC : reference voltage , sample and hold time
         ADC10CTL0 = ADC10SHT_2 + ADC10ON;
         ADC10CTL1 = (cfg.inputChannel << 12) + SHS_0 + ADC10SSEL_3;
         ADC10AE0 |= (1 << cfg.inputChannel);

         //Timer setup
         if (cfg.sampleRateHz > 0) {
              uint32_t period= 1000000UL / cfg.sampleRateHz;

              // CCRO is a 16-bit register , this logic ensures it doesn't exceed 65535
              TA1CCR0 = (uint16_t)(period > 65535 ? 65535 : period);

         }

         TA1CCTL0 = CCIE; // Enable interrupt
         TA1CTL = TASSEL_2 + MC_1 + TACLR; // SMCLK , up  mode
     }

     void captureAndStream(){
         ADC10CTL0 |= ENC + ADC10SC; //start conversion
         while (ADC10CTL1 & ADC10BUSY); // wait

         uint16_t val = ADC10MEM;

         Uart::printNumber(val);
         Uart::print("\r\n");

     }
 }
}
