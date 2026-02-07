/*
 * Config.hpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Olayemi
 */

#pragma once
#include <msp430.h>
#include "Driver.hpp"

namespace AppConfig {

    static const Hardware::ScopeConfig OscilloscopeSettings = {
                                                               .sampleRateHz = 100,
                                                               .inputChannel  = 4
    };

    using MainScope = Hardware::Scope;

}
