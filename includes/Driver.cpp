/*
 * Driver.cpp
 *
 *  Created on: Feb 5, 2026
 *      Author: User
 */

#iclude Drivers.hpp"

namespace Hardware{
 namespace Scope{
     void init(const ScopeConfig& cfg){// ADC : reference voltage , sample and hold time
         DC10CTL0 = SHT_2 + ADC10ON;
         ADC10TL1 = cfg.inputChannel + SHS_0 + ADC10SSEL_3;
         ADC10AE0 |= (1 << cfg.inputChannel);

         //Timer setup
         TA1CCR0 = 1000000 / cfg.sampleRateHz;
         TA1CTL = TASSEL_2 + MC_1; // SMCLK , up  mode
     }

     void captureAndStream(){
         ADC10CTL0 |= ENC + ADC10SC; //start conversion
         while (ADC10CTL1 & ADC10BUSY); // wait

         uint16_t val = ADC10MEM;
     }
 }
}
