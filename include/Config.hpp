/*
 * Config.hpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Olayemi
 */

#pragma once
#include <msp430.h>
#include "Driver.hpp"
#include "Timer"
#include "Uart.hpp"
#include "Controls.hpp"


namespace AppConfig {

    static const Hardware::ScopeConfig OscilloscopeSettings = {
                                                               .sampleRateHz = 100,
                                                               .inputChannel  = 4
    };

    namespace  MainScope = Hardware::Scope;
    using Console = Hardware::Uart;
    using Timer = Hardware::TimerA<Hardware::TimerClock::SMCLK>;
    namespace SignalGenerator = Hardware::SignalGen;
    using Controls = Hardware::Controls;


}
