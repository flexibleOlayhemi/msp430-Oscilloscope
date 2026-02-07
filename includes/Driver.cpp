/*
 * Driver.cpp
 *
 *  Created on: Feb 5, 2026
 *      Author: User
 */

#include "Drivers.hpp"
#include <cstdio>


namespace Hardware{
 namespace Scope{
     static char txBuffer[10]; // shared internal buffer to save RAM

     void init(const ScopeConfig& cfg){// ADC : reference voltage , sample and hold time
         DC10CTL0 = SHT_2 + ADC10ON;
         ADC10TL1 = cfg.inputChannel + SHS_0 + ADC10SSEL_3;
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

         int len = snprintf(txBuff, sizeof(txBuffer), "%u\r\n", val);

         for (int i = 0; i < len; i++){
             while (!(IFG2 & UCA0TXIFG)); // wait for UART TX Buffer
             UCA0TXBUF = txBuffer[i];
         }
     }
 }
}
