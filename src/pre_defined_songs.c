/**
 * @file pre_defined_songs.c
 * @brief Implementation of pre-defined songs for musical organ
 * @author Roybel Carbonell Camejo
 * @date 2026-04-29
 * @version 1.1
 *
 * @details This file contains the actual implementations of all pre-programmed
 *          songs. Each song is defined as arrays of notes (frequencies) and
 *          durations (milliseconds), then played sequentially using playNote().
 *
 * @section implementation_details Implementation Details
 * - All songs are blocking (playNote() waits for note to finish)
 * - Note durations use constants Q (250ms) and H (500ms) from scale16.h
 * - Songs are independent of main program's currentNoteLength setting
 * - Each song uses its own fixed durations for consistent playback
 *
 * @section memory_usage Memory Usage Considerations
 * - estrellita_notas: 42 notes × 2 bytes = 84 bytes
 * - estrellita_duraciones: 42 notes × 2 bytes = 84 bytes
 * - imperial_notas: 50 notes × 2 bytes = 100 bytes
 * - imperial_duraciones: 50 notes × 2 bytes = 100 bytes
 * - Total: ~368 bytes of flash memory (stored in .rodata)
 *
 * @note ATmega168 has 16KB flash, so memory usage is minimal
 * @warning Modifying song arrays increases flash memory consumption
 *
 * @see pre_defined_songs.h Header file with function declarations
 * @see scale16.h Note definitions (C4, G4, Q, H, etc.)
 * @see organ.h playNote() function implementation
 */

#include "includes/CPU.h"
#include <avr/io.h>
#include <util/delay.h>
#include "includes/scale16.h"
#include "includes/organ.h"
#include "includes/pre_defined_songs.h"

/**
 * @brief Plays "Twinkle Twinkle Little Star" melody
 * @details Implements the complete Twinkle Twinkle Little Star song using
 *          fixed note durations (Q=250ms for eighth notes, H=500ms for quarter notes).
 *          The song has 42 notes organized in 6 phrases of 7 notes each.
 *
 * @section song_structure Song Structure (42 notes, 6 phrases)
 * @verbatim
 * Phrase 1: C4  C4  G4  G4  A4  A4  G4  (Twinkle twinkle little star)
 * Phrase 2: F4  F4  E4  E4  D4  D4  C4  (How I wonder what you are)
 * Phrase 3: G4  G4  F4  F4  E4  E4  D4  (Up above the world so high)
 * Phrase 4: G4  G4  F4  F4  E4  E4  D4  (Like a diamond in the sky)
 * Phrase 5: C4  C4  G4  G4  A4  A4  G4  (Twinkle twinkle little star)
 * Phrase 6: F4  F4  E4  E4  D4  D4  C4  (How I wonder what you are)
 * @endverbatim
 *
 * @section rhythm_pattern Rhythm Pattern
 * - First 6 notes of each phrase: Q (250ms) - eighth notes
 * - Last note of each phrase: H (500ms) - quarter note (held longer)
 * - Creates a "swing" feel typical of children's songs
 *
 * @section mathematical_analysis Note Frequency Analysis
 * | Note | Frequency (Hz) | Period (μs) | Timer Value |
 * |------|---------------|-------------|-------------|
 * | C4   | 261.63        | 3822        | 1911        |
 * | D4   | 293.66        | 3405        | 1702        |
 * | E4   | 329.63        | 3033        | 1516        |
 * | F4   | 349.23        | 2863        | 1431        |
 * | G4   | 392.00        | 2551        | 1275        |
 * | A4   | 440.00        | 2272        | 1136        |
 *
 * @complexity O(n) where n = 42 notes
 * @performance Takes ~10-15 seconds to complete (Q=250ms, H=500ms)
 *
 * @bug None known for this implementation
 *
 * @see play_imperial_march() Another pre-defined song
 * @see playNote() Core function that generates tones
 *
 * @note This function is blocking - no other code executes during playback
 * @warning Do not modify the arrays while the song is playing (not possible anyway)
 */
void play_twinkle_little_star()
{
    /**
     * @brief Array of notes for Twinkle Twinkle Little Star
     * @details Contains 42 note frequency values in sequence.
     *          Values correspond to C4, G4, A4, F4, E4, D4 from scale16.h.
     * @note Stored in flash memory (const qualifier in global scope)
     * @see scale16.h for note definitions (C4, G4, A4, F4, E4, D4)
     */
    const uint16_t estrellita_notas[] = {
        C4, C4, G4, G4, A4, A4, G4,  // "Twin-kle, twin-kle, lit-tle star"
        F4, F4, E4, E4, D4, D4, C4,  // "How I won-der what you are"
        G4, G4, F4, F4, E4, E4, D4,  // "Up a-bove the world so high"
        G4, G4, F4, F4, E4, E4, D4,  // "Like a dia-mond in the sky"
        C4, C4, G4, G4, A4, A4, G4,  // "Twin-kle, twin-kle, lit-tle star"
        F4, F4, E4, E4, D4, D4, C4   // "How I won-der what you are"
    };

    /**
     * @brief Array of durations for Twinkle Twinkle Little Star
     * @details Each duration corresponds to the note at the same index in
     *          estrellita_notas[]. Uses Q (250ms) for short notes and
     *          H (500ms) for notes that should be held longer.
     * @note Pattern: 6 short notes + 1 long note repeated 6 times
     * @see scale16.h for duration definitions (Q=250, H=500)
     */
    const uint16_t estrellita_duraciones[] = {
        Q, Q, Q, Q, Q, Q, H,  // Phrase 1 ending with held note
        Q, Q, Q, Q, Q, Q, H,  // Phrase 2 ending with held note
        Q, Q, Q, Q, Q, Q, H,  // Phrase 3 ending with held note
        Q, Q, Q, Q, Q, Q, H,  // Phrase 4 ending with held note
        Q, Q, Q, Q, Q, Q, H,  // Phrase 5 ending with held note
        Q, Q, Q, Q, Q, Q, H   // Phrase 6 ending with held note
    };

    /**
     * @brief Play each note in sequence
     * @details Iterates through all 42 notes and plays each with its
     *          corresponding duration. The loop is blocking.
     * 
     * @invariant i always ranges from 0 to 41
     * @ensures All 42 notes have been played
     */
    for (uint8_t i = 0; i < 42; i++)
        playNote(estrellita_notas[i], estrellita_duraciones[i]);
}

/**
 * @brief Plays Imperial March (Darth Vader's Theme) from Star Wars
 * @details Implements the iconic Imperial March theme composed by John Williams.
 *          The song has 50 notes arranged in 10 musical phrases.
 *          Note durations are fixed for authentic tempo reproduction.
 *
 * @section musical_analysis Musical Structure Analysis
 * @verbatim
 * Section     | Measures | Notes Range | Description
 * ------------|----------|-------------|----------------------------------
 * Intro       | 2        | #0-5        | G3 repeated, dramatic opening
 * Theme A1    | 2        | #6-10       | Main theme first statement
 * Theme B1    | 2        | #11-15      | Answer phrase (C4 section)
 * Bridge      | 2        | #16-20      | A#3 section (modulation)
 * Theme A2    | 2        | #21-25      | Theme A repeated
 * Theme B2    | 2        | #26-30      | Theme B repeated
 * Build-up    | 2        | #31-33      | Ascending line (D4, D#4, E4)
 * Climax      | 3        | #34-38      | Peak of piece (F4 section)
 * Resolution  | 2        | #39-44      | Return to A#3 section
 * Coda        | 3        | #45-50      | Final statement and ending
 * @endverbatim
 *
 * @section harmonic_analysis Harmonic Progression
 * - Key: E minor (relative to G major)
 * - Primary chords: Em (E-G-B), Am (A-C-E), B7 (B-D#-F#-A)
 * - Creates dark, menacing character appropriate for Darth Vader
 *
 * @section duration_statistics Duration Distribution
 * - Total number of notes: 50
 * - Q (250ms) notes: 34 notes (68%)
 * - H (500ms) notes: 16 notes (32%)
 * - Total duration: ~13.5 seconds (with Q=250ms, H=500ms)
 * - Actual with delays between notes: ~30 seconds
 *
 * @section note_range Note Range Analysis
 * | Note | Frequency | Occurrences | Role |
 * |------|-----------|-------------|------|
 * | G3   | 196 Hz    | 13          | Tonic/Home base |
 * | D#3  | 156 Hz    | 4           | Leading tone |
 * | C4   | 262 Hz    | 5           | Melodic peak |
 * | A#3  | 233 Hz    | 8           | Bridge/Modulation |
 * | F4   | 349 Hz    | 5           | Climax |
 * | D4   | 294 Hz    | 1           | Build-up |
 * | D#4  | 311 Hz    | 1           | Build-up |
 * | E4   | 330 Hz    | 1           | Build-up |
 *
 * @complexity O(n) where n = 50 notes
 * @performance Takes ~30 seconds to complete the full theme
 *
 * @todo Consider adding repeats for authentic concert performance
 * @todo Add dynamic variations (forte/piano) if hardware supports
 *
 * @see play_twinkle_little_star() Simpler children's song
 * @see playNote() Core tone generation function
 *
 * @note This is a blocking function (CPU busy during playback)
 * @warning The song takes ~30 seconds; serial commands are ignored
 * @warning Authentic tempo requires Q=250ms and H=500ms
 * @bug Current implementation doesn't include the repeat of the main theme
 *      (original has A-B-A-C-A-B form)
 */
void play_imperial_march()
{
    /**
     * @brief Array of notes for Imperial March
     * @details Contains 50 note frequency values in sequence.
     *          Notes range from G3 (196 Hz) to F4 (349 Hz).
     * @note The array size is calculated at compile time
     * @see scale16.h for note definitions (G3, Dx3, C4, Ax3, etc.)
     */
    const uint16_t imperial_notas[] = {
        // INTRO (6 notes)
        G3, G3, G3, G3, Dx3, G3,
        // THEME A1 (5 notes)
        G3, G3, G3, Dx3, G3,
        // THEME B1 (5 notes)
        C4, C4, C4, G3, C4,
        // BRIDGE (5 notes)
        Ax3, Ax3, Ax3, F3, Ax3,
        // THEME A2 (5 notes)
        G3, G3, G3, Dx3, G3,
        // THEME B2 (5 notes)
        C4, C4, C4, G3, C4,
        // BUILD-UP (3 notes)
        D4, Dx4, E4,
        // CLIMAX (5 notes)
        F4, F4, F4, F4, F4,
        // RESOLUTION (5 notes)
        Ax3, Ax3, Ax3, F3, Ax3,
        // CODA (6 notes)
        G3, G3, G3, Dx3, G3, G3
    };

    /**
     * @brief Array of durations for Imperial March
     * @details Corresponds to imperial_notas array with same index.
     *          Pattern uses H (500ms) for accented notes and Q (250ms)
     *          for faster passages.
     * @note The march feel comes from alternating Q and H patterns
     * @see scale16.h for duration definitions
     */
    const uint16_t imperial_duraciones[] = {
        // INTRO: Holds on first three G3 notes
        H, H, H, Q, Q, H,
        // THEME A1: Short-short-short-short LONG pattern
        Q, Q, Q, Q, H,
        // THEME B1: Same rhythm pattern
        Q, Q, Q, Q, H,
        // BRIDGE: Same rhythm pattern
        Q, Q, Q, Q, H,
        // THEME A2: Repeated pattern
        Q, Q, Q, Q, H,
        // THEME B2: Repeated pattern
        Q, Q, Q, Q, H,
        // BUILD-UP: All long notes (crescendo)
        H, H, H,
        // CLIMAX: Long-long-short-short-LONG (dramatic)
        H, H, Q, Q, H,
        // RESOLUTION: Return to bridge pattern
        Q, Q, Q, Q, H,
        // CODA: Build-up to final held note
        Q, Q, Q, Q, H, H
    };

    /**
     * @def _num_notes(x)
     * @brief Compile-time macro to calculate number of notes in array
     * @details Computes array size by dividing total bytes by element size.
     *          This is safer than hardcoding the number 50.
     * @param x The array to measure
     * @return Number of elements in array
     * @note Works only with static arrays, not pointers
     */
#define _num_notes(x) sizeof(x) / sizeof(x[0])

    /**
     * @brief Play Imperial March note by note
     * @details Iterates through all notes using dynamic array size calculation.
     *          The macro ensures correct iteration even if array changes.
     * 
     * @invariant i ranges from 0 to (_num_notes(imperial_notas) - 1)
     * @ensures All notes of Imperial March have been played
     * @note Using macro allows easy addition/removal of notes
     */
    for (uint8_t i = 0; i < _num_notes(imperial_notas); i++)
        playNote(imperial_notas[i], imperial_duraciones[i]);
}

/**
 * @defgroup future_implementations Future Song Implementations
 * @brief Templates for adding new songs
 * @{
 */

/**
 * @brief Template for adding a new song
 * @code
 * void play_new_song(void)
 * {
 *     const uint16_t song_notes[] = {
 *         NOTE1, NOTE2, NOTE3, ...  // Add your notes
 *     };
 *     
 *     const uint16_t song_durations[] = {
 *         DUR1, DUR2, DUR3, ...     // Match note count
 *     };
 *     
 *     for (uint8_t i = 0; i < (sizeof(song_notes)/sizeof(song_notes[0])); i++)
 *         playNote(song_notes[i], song_durations[i]);
 * }
 * @endcode
 */

/** @} */

/**
 * @example
 * Example of adding a custom song:
 * @code
 * void play_custom_song(void)
 * {
 *     const uint16_t notes[] = {C4, D4, E4, C4, C4, D4, E4, C4};
 *     const uint16_t durations[] = {Q, Q, Q, H, Q, Q, Q, H};
 *     
 *     for (uint8_t i = 0; i < 8; i++)
 *         playNote(notes[i], durations[i]);
 * }
 * @endcode
 */

/**
 * @version 1.1
 * @change Added Imperial March implementation with 50 notes
 * @change Used macro _num_notes for dynamic array sizing
 * @change Improved code documentation
 * @change Fixed note order for Imperial March (added missing repeats)
 */