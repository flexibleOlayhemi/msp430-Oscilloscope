/*
 * Control.cpp
 *
 *  Created on: Feb 13, 2026
 *      Author: Olayemi
 */

#pragma once
#include "include/Controls.hpp"

namespace Hardware {

         uint8_t Controls::lastButtonState = 0;

       //Pulsing the shift register
         void Controls::pulse(){
            P2OUT |= BIT4;  // Clock High
            P2OUT &= ~BIT4; // Clock Low
        }

         void Controls::init(){
            P2DIR |= (BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6);
            P2DIR &= ~BIT7;
            P2SEL &= ~(BIT6 | BIT7); // Disable Crystal function for GPIO

            P2OUT &= ~BIT5; // Reset
            __delay_cycles(100);
            P2OUT |= BIT5;
            P2OUT &= ~(BIT0 | BIT1 | BIT2 | BIT3); // Hold mode
            lastButtonState = 0;
        }

         uint8_t Controls::getPressed(){

            uint8_t currentVal = 0;

            P2OUT |= (BIT2 | BIT3);  //Parallel Load
            pulse();

            P2OUT &= ~BIT3; //Shift Right
            for(int i = 3; i >= 0; i--){
                if (P2IN & BIT7) currentVal |= (0x01 << i);
                pulse();
            }
            P2OUT &= ~(BIT2 | BIT3); // Back to hold mode

            //To capture when button is pushed
            uint8_t pressedTrigger = currentVal & (~lastButtonState);
            lastButtonState = currentVal;

            return pressedTrigger;
        }

        void Controls::writeLeds(uint8_t data)
        {
           //(S0=1 , S1=0)
           P2OUT |= BIT0; P2OUT &= ~BIT1; // SREG2 shif Right
           //MSB first
           for (int i = 3; i >= 0; i--){
              if (data & (0x01 << i)) P2OUT |= BIT6; else P2OUT &= ~ BIT6;
                   pulse();
              }
           P2OUT &= ~(BIT0 | BIT1);
        }



}




