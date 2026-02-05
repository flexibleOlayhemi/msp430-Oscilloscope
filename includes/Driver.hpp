/*
 * Driver.hpp
 *
 *  Created on: Feb 5, 2026
 *      Author: Olayemi
 */

#pragma once
#include <msp430.h>
#include <stdint.h>

namespace Hardware {
    struct ScopeConfig{ //configure to pass by reference
        uint16_t sampleRateHz;
        uint8_t inputChannel;
    }

    namespace Scope{
        void init(const ScopeConfig& cfg);
        void captureAndStream();
    }

    namespace SignalGen {
        void init ();
        void updateWaveform(uint8_t type);

    }
}
