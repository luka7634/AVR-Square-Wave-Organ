/**
 * @file        organ.c
 * @brief       Implementation of tone generation functions for electronic organ
 * @author      Roybel Carbonell Camejo
 * @date        2026-04-28
 * 
 * @details
 * This file contains the implementation of functions required to generate
 * musical tones using a piezoelectric buzzer.
 */

#include "includes/CPU.h"
#include <avr/io.h>
#include <util/delay.h>
#include "includes/organ.h"
#include "includes/pinDefines.h"

/**
 * @brief       Generates a musical tone with specific duration
 * @param[in]   half_us         Half period of the square wave in microseconds (1/(2*frequency))
 * @param[in]   duration_ms     Total note duration in milliseconds
 * 
 * @details
 * This function generates a square wave on the buzzer pin to produce
 * a musical tone. The tone is generated using the following formula:
 * - Frequency (Hz) = 1,000,000 / (2 * half_us)
 * - Total cycles = (frequency * duration_ms) / 1000
 * 
 * @par Algorithm:
 * The function toggles the buzzer pin between HIGH and LOW, with delays
 * equal to the specified half period, thus generating a perfect square wave.
 * 
 * @par Example:
 * @code
 * // Generate A4 (440 Hz) for 500 ms
 * // half_us = 1,000,000/(2*440) = 1136 us
 * play_note(1136, 500);
 * @endcode
 * 
 * @note        The cycle calculation is performed as:
 *              cycles = (500000 / half_us) * duration_ms / 1000
 *              This formula avoids integer overflow.
 * 
 * @warning     This function uses _delay_us() which is NOT accurate for
 *              delays > 768 us at 16 MHz. For half_us > 768, consider
 *              using hardware timers.
 * 
 * @warning     Delays are blocking; no other tasks can execute during
 *              note playback.
 * 
 * @pre         The BUZZER_PIN must be configured as output on BUZZER_PORT
 *              before calling this function.
 * 
 * @post        After playing the note, there is an additional 30ms delay
 *              to prevent "clicks" between notes.
 * 
 * @see         timer_generate_tone() For non-blocking implementation
 * @see         play_song() For playing complete melodies
 * 
 * @bugs        For very small half_us (< 10), the generated frequency
 *              may be inaccurate due to loop overhead.
 * 
 * @todo        Implement hardware timer version for non-blocking playback
 * @todo        Add volume control using PWM modulation
 */
void play_note(uint16_t half_us, uint16_t duration_ms)
{
    /* Calculate the number of complete cycles needed
     * Optimized formula: (0.5e6 / half_us) * duration_ms / 1000
     * Equivalent to: cycles = frequency_Hz * (duration_ms/1000)
     */
    uint16_t cycles = (500000 / half_us) * duration_ms / 1000;

    /* Main tone generation loop */
    for (uint16_t i = 0; i < cycles; i++)
    {
        /* HIGH phase of square wave */
        BUZZER_PORT |= (1 << BUZZER_PIN);          /* Set pin high */
        for (uint16_t k = 0; k < half_us; k++)     /* Half cycle delay */
            _delay_us(1);
        
        /* LOW phase of square wave */
        BUZZER_PORT &= ~(1 << BUZZER_PIN);         /* Set pin low */
        for (uint16_t m = 0; m < half_us; m++)     /* Half cycle delay */
            _delay_us(1);
    }
    
    /* Short pause between notes to eliminate transition noise */
    _delay_ms(30);
}