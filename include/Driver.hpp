/*
 * Driver.hpp
 *
 *  Created on: Feb 5, 2026
 *      Author: Olayemi
 */

#pragma once
#include <msp430.h>
#include <stdint.h>
#include "Uart.hpp"

namespace Hardware {
    struct ScopeConfig{ //configure to pass by reference
        uint16_t sampleRateHz;
        uint8_t inputChannel;
    };

    namespace Scope{
        void init(const ScopeConfig& cfg);
        void captureAndStream();
    }

    namespace SignalGen {
        void init ();
        void setVoltage(uint16_t miliVolts);
        void setDutyCycle(uint16_t duty);
        void updateWaveform(uint8_t type,uint8_t index, uint8_t gain);

    }
}
