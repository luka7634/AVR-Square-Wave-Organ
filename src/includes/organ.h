/**
 * @file        organ.h
 * @brief       Organ tone generator interface
 * @author      Roybel Carbonell Camejo
 * @date        2026-04-28
 */

#ifndef ORGAN_H
#define ORGAN_H

/**
 * @brief       Play a musical tone
 * @param       half_us     Half period in microseconds (1/(2*frequency))
 * @param       duration_ms Tone duration in milliseconds
 * 
 * @details     Generates a square wave on the buzzer pin.
 *              Example: play_note(1136, 500) plays 440Hz for 500ms.
 * 
 * @warning     Blocking function - pauses execution during playback
 * @pre         Buzzer pin must be configured as output
 * 
 * @see         pinDefines.h for buzzer pin configuration
 */
void playNote(uint16_t half_us, uint16_t duration_ms);
void rest(uint16_t duration_ms);

#endif /* ORGAN_H */