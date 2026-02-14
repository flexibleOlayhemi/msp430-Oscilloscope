/*
 * Controls.hpp
 *
 *  Created on: Feb 13, 2026
 *      Author: Olayemi
 */

#pragma once
#include <msp430.h>
#include <stdint.h>

namespace Hardware{

    class Controls{
    private:
        static uint8_t lastButtonState;
        static void pulse();
    public:
        static void init();
        static uint8_t getPressed();
        static void writeLeds(uint8_t data);

    };
}
