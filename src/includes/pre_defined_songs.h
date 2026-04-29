/**
 * @file pre_defined_songs.h
 * @brief Pre-defined songs for musical organ
 * @author Roybel Carbonell Camejo
 * @date 2026-04-29
 * @version 1.1
 * 
 * @details Declares functions to play pre-programmed songs via USART commands.
 *          Songs are triggered by numeric keys (e.g., '1' for Twinkle Star,
 *          '2' for Imperial March).
 * 
 * @section song_list Available Songs
 * | Key | Function               | Song Title                    | Duration  |
 * |-----|------------------------|-------------------------------|-----------|
 * | '1' | play_twinkle_little_star() | Twinkle Twinkle Little Star | ~10-15 sec |
 * | '2' | play_imperial_march()   | Imperial March (Star Wars)    | ~30 sec    |
 * 
 * @section usage Usage Example
 * @code
 * #include "pre_defined_songs.h"
 * 
 * // In main.c serial command handling
 * switch(receivedChar) {
 *     case '1':
 *         play_twinkle_little_star();
 *         printString("\r\nPlaying Twinkle Twinkle Little Star\r\n");
 *         break;
 *     case '2':
 *         play_imperial_march();
 *         printString("\r\nPlaying Imperial March\r\n");
 *         break;
 * }
 * @endcode
 */

#ifndef PRE_DEFINED_SONGS_H
#define PRE_DEFINED_SONGS_H

/**
 * @brief Plays "Twinkle Twinkle Little Star" melody
 * @details Blocking function that plays the classic children's song 
 *          "Twinkle Twinkle Little Star" through the buzzer.
 * 
 * @section melody Melody (C major scale)
 * @verbatim
 * CC GG AA G - FF EE DD C - GG FF EE D - GG FF EE D -
 * CC GG AA G - FF EE DD C
 * @endverbatim
 * 
 * @section song_info Song Information
 * - **Composer**: Traditional/French folk melody (1761)
 * - **Lyrics by**: Jane Taylor (1806)
 * - **Key**: C major
 * - **Time Signature**: 4/4
 * - **Tempo**: Andante (~120 BPM with Q=250ms)
 * - **Duration**: ~10-15 seconds (depends on note duration mode)
 * 
 * @note Blocking function - no serial input accepted while playing
 * @note Triggered by pressing '1' in the main program
 * @warning Note durations are affected by global currentNoteLength variable
 * @warning If currentNoteLength = H (500ms), song plays slower
 *          If currentNoteLength = Q (250ms), song plays faster
 * 
 * @see playNote() from organ.h for individual note playback
 * @see currentNoteLength in main.c for duration control
 * @see play_imperial_march() Another pre-defined song
 */
void play_twinkle_little_star();

/**
 * @brief Plays "Imperial March" (Darth Vader's Theme) from Star Wars
 * @details Blocking function that plays the iconic Imperial March theme
 *          composed by John Williams for Star Wars: The Empire Strikes Back (1980).
 *          Associated with Darth Vader and the Galactic Empire.
 * 
 * @section composition Composition Details
 * - **Composer**: John Williams
 * - **Movie**: Star Wars: Episode V - The Empire Strikes Back (1980)
 * - **Key**: E minor (Em)
 * - **Time Signature**: 4/4 (march tempo)
 * - **Original Tempo**: ~104 BPM
 * - **Duration**: ~30 seconds (complete main theme)
 * 
 * @section structure Musical Structure
 * The piece follows this structure:
 * @verbatim
 * Intro (4 bars) | Main Theme A (4 bars) | Main Theme B (4 bars) |
 * Bridge (4 bars) | Main Theme A (4 bars) | Build-up (3 bars) |
 * Climax (5 bars) | Resolution (4 bars) | Coda (6 bars)
 * @endverbatim
 * 
 * @section melody Melody Pattern
 * @verbatim
 * G3 - G3 - G3 - (G3 D#3) G3 | G3 G3 G3 D#3 G3 |
 * C4 C4 C4 G3 C4 | A#3 A#3 A#3 F3 A#3 |
 * [Pattern repeats with variations]
 * @endverbatim
 * 
 * @section trivia Trivia & Cultural Impact
 * - One of the most recognizable film themes in cinema history
 * - Often used in popular culture to denote villainy or impending doom
 * - Has been performed by numerous orchestras worldwide
 * - Frequently appears in video games, memes, and parodies
 * 
 * @section usage Usage
 * @code
 * // Play the Imperial March
 * play_imperial_march();
 * 
 * // Trigger with '2' in main.c
 * if (receivedChar == '2') {
 *     play_imperial_march();
 *     printString("\r\n*** Imperial March ***\r\n");
 * }
 * @endcode
 * 
 * @note Blocking function - no serial input accepted while playing
 * @note Triggered by pressing '2' in the main program (recommended)
 * @note The theme uses notes from G3 to F4 (range: G3, G#3, A#3, C4, D4, D#4, E4, F4)
 * 
 * @warning This is a **blocking** function - the microcontroller will not
 *          respond to any serial commands until the song finishes (~30 seconds)
 * @warning Note durations are affected by global currentNoteLength variable
 * @warning For authentic tempo, ensure currentNoteLength matches intended duration
 *          - Use Q (250ms) for faster, more dramatic tempo
 *          - Use H (500ms) for slower, more ominous tempo
 * 
 * @bug Current blocking implementation prevents interrupt during playback
 * @todo Implement non-blocking version using timer interrupts
 * @todo Add ability to stop playback mid-song (emergency stop)
 * 
 * @see play_twinkle_little_star() Another pre-defined song
 * @see playNote() Core function for note playback
 * @see scale16.h Contains note definitions (G3, C4, F4, etc.)
 */
void play_imperial_march();

/**
 * @defgroup upcoming_songs Upcoming Songs
 * @brief Planned songs for future releases
 * @{
 */

/**
 * @brief Happy Birthday song
 * @todo Implement this function
 * @details Traditional birthday song, public domain
 * @see https://en.wikipedia.org/wiki/Happy_Birthday_to_You
 */
/* void play_happy_birthday(void); */

/**
 * @brief Jingle Bells (Christmas song)
 * @todo Implement this function
 * @details Classic Christmas song by James Lord Pierpont (1857)
 * @see https://en.wikipedia.org/wiki/Jingle_Bells
 */
/* void play_jingle_bells(void); */

/**
 * @brief Für Elise (Beethoven)
 * @todo Implement this function
 * @details Bagatelle No. 25 in A minor by Ludwig van Beethoven (1810)
 * @see https://en.wikipedia.org/wiki/F%C3%BCr_Elise
 */
/* void play_fur_elise(void); */

/**
 * @brief Tetris Theme (Korobeiniki)
 * @todo Implement this function
 * @details Russian folk song, famous from Tetris game
 * @see https://en.wikipedia.org/wiki/Korobeiniki
 */
/* void play_tetris_theme(void); */

/**
 * @brief Super Mario Bros. Theme
 * @todo Implement this function
 * @details Iconic video game theme by Koji Kondo (1985)
 * @see https://en.wikipedia.org/wiki/Super_Mario_Bros._theme
 */
/* void play_mario_theme(void); */

/** @} */

/**
 * @brief Emergency stop function for songs
 * @todo Implement this function
 * @details Should immediately stop any currently playing song
 *          and return control to the main loop
 * @warning Requires non-blocking song implementation to work properly
 */
/* void stop_current_song(void); */

#endif /* PRE_DEFINED_SONGS_H */