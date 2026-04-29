/**
 * @file    pinDefines.h
 * @brief   Hardware pin mapping for BUZZER/buzzer output
 * @author  Roybel Carbonell Camejo
 * @date    2026-04-28
 *
 * @details Maps the BUZZER/buzzer to specific microcontroller pins.
 *          Centralizes pin definitions for easy hardware changes.
 *
 * @note    Modify these definitions if BUZZER is connected to different pins
 * @warning Ensure pin configuration matches actual hardware connections
 */

#ifndef PIN_DEFINES_H
#define PIN_DEFINES_H

/**
 * @defgroup Pin_Config Hardware Pin Configuration
 * @brief   Pin mappings for BUZZER output
 * @{
 */

/**
 * @brief   Data Direction Register for BUZZER pin
 * @details Defines which port's DDR register controls the BUZZER pin.
 *          Typically DDRB for Port B, DDRC for Port C, or DDRD for Port D.
 *
 * @note    Current configuration: Port B
 * @see     BUZZER, BUZZER_PORT
 */
#define BUZZER_DDR DDRB

/**
 * @brief   BUZZER pin number within its port
 * @details Pin number (0-7) for the BUZZER connection.
 *          PB0 means Pin 0 of Port B.
 *
 * @note    Current configuration: Port B, Pin 0
 * @warning Change with BUZZER_DDR and BUZZER_PORT if moving to different pin
 * @see     BUZZER_DDR, BUZZER_PORT
 */
#define BUZZER_PIN PB0

/**
 * @brief   Output port register for BUZZER pin
 * @details Defines which port register controls the BUZZER pin's output state.
 *          Used to set the pin HIGH or LOW to drive the BUZZER.
 *
 * @note    Current configuration: Port B output register
 * @see     BUZZER_DDR, BUZZER
 */
#define BUZZER_PORT PORTB

/** @} */

#endif /* PIN_DEFINES_H */