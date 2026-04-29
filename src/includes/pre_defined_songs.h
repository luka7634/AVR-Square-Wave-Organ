/**
 * @file pre_defined_songs.h
 * @brief Pre-defined songs for musical organ
 * @author Roybel Carbonell Camejo
 * @date 2026-04-29
 * 
 * @details Declares functions to play pre-programmed songs via USART commands.
 *          Songs are triggered by numeric keys (e.g., '1' for Twinkle Star).
 */

#ifndef PRE_DEFINED_SONGS_H
#define PRE_DEFINED_SONGS_H

/**
 * @brief Plays "Twinkle Twinkle Little Star" melody
 * @details Blocking function that plays the complete song through the buzzer.
 *          Song duration: ~10-15 seconds depending on note duration mode.
 * 
 * @note Blocking function - no serial input accepted while playing
 * @note Triggered by pressing '1' in the main program
 * @warning Note durations are affected by global currentNoteLength variable
 * 
 * @see playNote() from organ.h for individual note playback
 * @see currentNoteLength in main.c for duration control
 */
void play_twinkle_little_star();

void play_imperial_march();

/**
 * @todo Add more songs:
 *       - play_happy_birthday()
 *       - play_jingle_bells()
 */

#endif /* PRE_DEFINED_SONGS_H */