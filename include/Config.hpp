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
#include "Button.hpp"


namespace AppConfig {

    using RegPtr = volatile uint8_t*;

    static const Hardware::ScopeConfig OscilloscopeSettings = {
                                                               .sampleRateHz = 100,
                                                               .inputChannel  = 4
    };

    namespace  MainScope = Hardware::Scope;
    using Console = Hardware::Uart;
    using Timer = Hardware::TimerA<Hardware::TimerClock::SMCLK>;
    namespace SignalGenerator = Hardware::SignalGen;
    using Controls = Hardware::Controls;
    using Btn5 = Hardware::Button<RegPtr,&P3IN,&P3DIR,&P3REN,&P3OUT,
            nullptr,nullptr,nullptr,BIT2>;
    using Btn6 = Hardware::Button<RegPtr,&P3IN,&P3DIR,&P3REN,&P3OUT,
            nullptr,nullptr,nullptr,BIT3>;


}
