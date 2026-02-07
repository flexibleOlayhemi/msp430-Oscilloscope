/*
 * Config.hpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Olayemi
 */

#pragma once
#include "Driver.hpp"
#include "Uart.hpp"
#include <msp430.h>

namespace AppConfig {

    static const Hardware::ScopeConfig OscilloscopeSettings = {
                                                               .sampleRateHz = 100,
                                                               .inputChannel  = 4
    };

    namespace  MainScope = Hardware::Scope;
    using Console = Hardware::Uart;

}
