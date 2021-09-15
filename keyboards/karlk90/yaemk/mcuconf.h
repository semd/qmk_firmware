/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio
    ChibiOS - Copyright (C) 2021 Stefan Kerkmann

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#pragma once

#if defined(__arm__)

/* STM32F303 */
#include_next <mcuconf.h>

#undef STM32_PPRE2
#define STM32_PPRE2 STM32_PPRE2_DIV1

#undef STM32_RTCSEL
#define STM32_RTCSEL STM32_RTCSEL_NOCLOCK

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE

#undef STM32_PWM_USE_TIM1
#define STM32_PWM_USE_TIM1 TRUE

#undef STM32_SERIAL_USE_USART3
#define STM32_SERIAL_USE_USART3 TRUE

#undef STM32_SERIAL_USART3_PRIORITY
#define STM32_SERIAL_USART3_PRIORITY 10

#elif defined(__riscv)

/* GD32VF103 */
#include_next <mcuconf.h>

/*
 * I2C driver system settings.
 */
#undef GD32_I2C_USE_I2C0
#define GD32_I2C_USE_I2C0                  TRUE

/*
 * PWM driver system settings.
 */
#undef GD32_PWM_USE_ADVANCED              
#define GD32_PWM_USE_ADVANCED              TRUE
#undef GD32_PWM_USE_TIM0
#define GD32_PWM_USE_TIM0                  TRUE

/*
 * SERIAL driver system settings.
 */
#undef GD32_SERIAL_USE_USART2
#define GD32_SERIAL_USE_USART2             TRUE

#endif