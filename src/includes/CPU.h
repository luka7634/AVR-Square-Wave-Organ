/**
 * @file CPU.h
 * @brief CPU configuration and definitions for ATmega168
 * @author Roybel Carbonell Camejo
 * @date 2026-04-29
 * @version 1.0
 *
 * @details This header file centralizes all CPU-specific configurations for 
 *          the ATmega168 microcontroller. It defines the processor type, 
 *          clock frequency, and default serial communication baud rate.
 *
 * @section usage Usage
 * Include this file before any AVR-specific headers or other modules that 
 * depend on CPU definitions:
 * @code
 * #include "includes/CPU.h"
 * #include <avr/io.h>
 * #include <util/delay.h>
 * @endcode
 *
 * @section dependencies Dependencies
 * - No external dependencies required
 *
 * @section notes Notes
 * - This file should be included BEFORE <avr/io.h> to ensure proper CPU definition
 * - F_CPU is required by <util/delay.h> for accurate delay calculations
 * - BAUD is used by USART modules for serial communication configuration
 *
 * @warning If F_CPU is not defined correctly, timing functions like _delay_ms()
 *          will produce incorrect delays.
 * @warning Changing BAUD requires matching configuration on the serial terminal side.
 */

#ifndef CPU_H
#define CPU_H

/**
 * @def __AVR_ATmega168__
 * @brief ATmega168 microcontroller selection
 * @details Ensures the compiler uses the correct memory map, register definitions,
 *          and hardware-specific optimizations for the ATmega168.
 * 
 * This macro is:
 * - Required by avr-libc headers
 * - Used by avr-gcc for proper code generation
 * - Essential for correct interrupt vector table mapping
 * 
 * @note The conditional guard prevents redefinition if already set by compiler flags
 * @see https://www.nongnu.org/avr-libc/user-manual/using_tools.html
 */
#ifndef __AVR_ATmega168__
    #define __AVR_ATmega168__
#endif

/**
 * @def BAUD
 * @brief Default USART baud rate for serial communication
 * @details Sets the serial communication speed to 9600 bits per second.
 *          This is a standard baud rate commonly used for microcontroller
 *          communication and terminal interfaces.
 * 
 * Range of typical baud rates for ATmega168 @ 16MHz:
 * - 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 115200
 * 
 * @note The actual achievable baud rate depends on F_CPU and UBRR register precision
 * @warning Baud rate error should ideally be less than 2% for reliable communication
 * 
 * Calculation formula:
 * @code
 * UBRR = (F_CPU / (16 * BAUD)) - 1
 * For F_CPU=16MHz, BAUD=9600: UBRR = (16000000 / (16 * 9600)) - 1 = 103.166 → 103
 * Error = 0.16% (well within acceptable range)
 * @endcode
 * 
 * @see F_CPU Required for baud rate calculation
 * @see USART.h Where this BAUD definition is typically used
 */
#ifndef BAUD
    #define BAUD 9600UL
#endif

/**
 * @def F_CPU
 * @brief CPU clock frequency in Hertz
 * @details Defines the operating frequency of the ATmega168 microcontroller
 *          as 16 MHz. This macro is critical for timing functions and
 *          peripheral configuration.
 * 
 * Important uses:
 * - Used by <util/delay.h> for _delay_ms() and _delay_us() functions
 * - Required for USART baud rate calculations
 * - Used in timer/Counter configurations
 * - Affects PWM frequency calculations
 * - Used for SPI and I2C timing
 * 
 * For ATmega168 typical clock configurations:
 * - 1 MHz (default internal RC oscillator)
 * - 8 MHz (internal RC oscillator calibrated)
 * - 16 MHz (external crystal, as used here)
 * - 20 MHz (maximum recommended with external crystal)
 * 
 * @note This value MUST match the actual hardware clock configuration
 * @warning If F_CPU is incorrect:
 *          - _delay_ms() will be too fast or too slow
 *          - USART will have baud rate errors
 *          - Timer-based code will fail
 * 
 * Derivation for UBRR calculation:
 * @code
 * UBRR = (F_CPU / (16 * BAUD)) - 1
 *      = (16000000 / (16 * 9600)) - 1
 *      = (16000000 / 153600) - 1
 *      = 104.166 - 1
 *      = 103.166 → 103 (integer)
 * @endcode
 * 
 * @see BAUD Used together with F_CPU for baud rate calculation
 * @see sleep.h Used for sleep mode timing
 */
#ifndef F_CPU
    #define F_CPU 16000000UL
#endif

/**
 * @brief CPU Speed in MHz (convenience macro)
 * @details Helper macro for documentation and potential future use
 * @note Not defined by default, shown here for reference only
 */
/* #define F_CPU_MHZ 16  // (F_CPU / 1000000) */

/**
 * @example
 * Example usage of these definitions in USART initialization:
 * @code
 * #include "CPU.h"
 * #include <avr/io.h>
 * 
 * void USART_Init(void) {
 *     // Calculate UBRR value using defined F_CPU and BAUD
 *     uint16_t ubrr = (F_CPU / (16UL * BAUD)) - 1;
 *     UBRR0H = (uint8_t)(ubrr >> 8);
 *     UBRR0L = (uint8_t)ubrr;
 *     
 *     // Enable transmitter and receiver
 *     UCSR0B = (1 << TXEN0) | (1 << RXEN0);
 *     
 *     // Asynchronous mode, 8-bit data, 1 stop bit
 *     UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
 * }
 * @endcode
 */

#endif /* CPU_H */