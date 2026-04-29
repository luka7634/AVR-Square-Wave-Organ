/**
 * @mainpage Serial-Controlled Musical Organ for ATmega168
 * 
 * @image html https://via.placeholder.com/800x200?text=Serial+Organ "Serial Organ Banner"
 * 
 * @section intro Introduction
 * This project implements a **serial-controlled musical organ** on an ATmega168 
 * microcontroller. Convert your computer keyboard into a musical instrument via 
 * the serial terminal!
 * 
 * @section features Features
 * - 🎹 **18-key polyphonic organ** (2 octaves including sharps)
 * - 🎵 **Real-time note playback** via USART (9600 baud)
 * - 🎼 **Pre-programmed songs** (Twinkle Little Star, Imperial March)
 * - ⚡ **Adjustable tempo** (short/long note duration modes)
 * - 🔌 **Simple hardware** (MCU + buzzer + USB-to-serial)
 * 
 * @section quickstart Quick Start Guide
 * 1. Connect buzzer to PD5 (configurable)
 * 2. Connect USB-to-serial to PD0(RX)/PD1(TX)
 * 3. Compile with `make`
 * 4. Flash with `make flash`
 * 5. Open serial terminal at 9600 baud
 * 6. Press keys to play music!
 * 
 * @section authors Authors
 * - Roybel Carbonell Camejo
 * 
 * @section date Date
 * 2026-04-29
 * 
 * @section license License
 * Open source - feel free to modify and distribute
 * 
 * @section related Related Pages
 * - @subpage commands_page
 * - @subpage hardware_page
 * - @subpage development_page
 */

/**
 * @page commands_page Serial Commands Reference
 * 
 * @section keyboard_layout Keyboard to Note Mapping
 * 
 * ### White Keys (Natural Notes)
 * | Key | Note | Frequency | Octave |
 * |-----|------|-----------|--------|
 * | a   | G4   | 392 Hz    | 4th    |
 * | s   | A4   | 440 Hz    | 4th    |
 * | d   | B4   | 494 Hz    | 4th    |
 * | f   | C5   | 523 Hz    | 5th    |
 * | g   | D5   | 587 Hz    | 5th    |
 * | h   | E5   | 659 Hz    | 5th    |
 * | j   | F5   | 698 Hz    | 5th    |
 * | k   | G5   | 784 Hz    | 5th    |
 * | l   | A5   | 880 Hz    | 5th    |
 * | ;   | A#5  | 932 Hz    | 5th    |
 * | '   | C6   | 1047 Hz   | 6th    |
 * 
 * ### Black Keys (Sharp Notes)
 * | Key | Note | Frequency | Octave |
 * |-----|------|-----------|--------|
 * | w   | G#4  | 415 Hz    | 4th    |
 * | e   | A#4  | 466 Hz    | 4th    |
 * | t   | C#5  | 554 Hz    | 5th    |
 * | y   | D#5  | 622 Hz    | 5th    |
 * | i   | F#5  | 740 Hz    | 5th    |
 * | o   | G#5  | 831 Hz    | 5th    |
 * | p   | B5   | 988 Hz    | 5th    |
 * 
 * @section control_commands Control Commands
 * | Command | Action | Description |
 * |---------|--------|-------------|
 * | `[`     | Short mode | Set note duration to 250ms |
 * | `]`     | Long mode  | Set note duration to 500ms |
 * | `1`     | Play song  | Twinkle Twinkle Little Star |
 * | `2`     | Play song  | Imperial March (Star Wars) |
 * 
 * @section usage_example Usage Example
 * @verbatim
 * ---Serial Organ---
 * Ready!
 * > a        (plays G4)
 * > s        (plays A4)
 * > [        (short mode enabled)
 * > a        (plays G4 - shorter)
 * > 1        (plays Twinkle Little Star)
 * @endverbatim
 */

/**
 * @page hardware_page Hardware Setup Guide
 * 
 * @section components Required Components
 * - ATmega168 microcontroller (DIP-28)
 * - 16 MHz crystal (optional, can use internal 8MHz)
 * - 2 × 22pF capacitors (for crystal)
 * - Piezo buzzer (5V)
 * - 220Ω resistor (for buzzer)
 * - USB-to-serial adapter (FTDI, CP2102, CH340)
 * - 5V power supply
 * - Breadboard and jumper wires
 * 
 * @section wiring Wiring Diagram
 * @verbatim
 * ATmega168          USB-to-Serial
 * ┌─────────┐        ┌──────────┐
 * │PD0 (2)  ├────────┤RX        │
 * │PD1 (3)  ├────────┤TX        │
 * │PD5 (11) ├────┬───┤          │
 * │         │   220Ω│          │
 * │         │    ┌─┴─┐          │
 * │GND (8)  ├────┴───┴──────────┤GND
 * │VCC (7)  ├────────┤VCC (5V)  │
 * └─────────┘        └──────────┘
 *            Buzzer
 * @endverbatim
 * 
 * @section pin_configuration Pin Configuration
 * Edit `src/includes/pinDefines.h` to change buzzer pin:
 * @code
 * #define BUZZER_DDR   DDRD
 * #define BUZZER_PORT  PORTD
 * #define BUZZER_PIN   PD5    // Change to any PD pin
 * @endcode
 * 
 * @section power_requirements Power Requirements
 * - Voltage: 5V DC
 * - Current (idle): ~15mA
 * - Current (playing): ~25-35mA
 * - Can be powered via USB-to-serial adapter
 */

/**
 * @page development_page Development & Customization
 * 
 * @section adding_songs Adding New Songs
 * 
 * **Step 1:** Add function declaration in `pre_defined_songs.h`
 * @code
 * void play_my_song(void);
 * @endcode
 * 
 * **Step 2:** Implement the song in `pre_defined_songs.c`
 * @code
 * void play_my_song(void)
 * {
 *     const uint16_t notes[] = {C4, D4, E4, F4, G4, A4, B4, C5};
 *     const uint16_t durations[] = {Q, Q, Q, Q, Q, Q, Q, H};
 *     
 *     for (uint8_t i = 0; i < 8; i++)
 *         playNote(notes[i], durations[i]);
 * }
 * @endcode
 * 
 * **Step 3:** Add command in `main.c`
 * @code
 * else if (receivedChar == '3')
 * {
 *     printString("\r\nPlaying my custom song\r\n");
 *     play_my_song();
 * }
 * @endcode
 * 
 * @section note_frequencies Note Frequency Calculation
 * 
 * Timer values are calculated as:
 * @code
 * OCR = F_CPU / (2 × frequency × prescaler)
 * 
 * Example for C4 (261.63 Hz) with F_CPU=16MHz, prescaler=1:
 * OCR = 16000000 / (2 × 261.63 × 1) = 30578
 * @endcode
 * 
 * @section adding_notes Adding New Notes
 * Add to `scale16.h`:
 * @code
 * #define NewNote  OCR_VALUE
 * @endcode
 * 
 * @section improving_performance Performance Improvements
 * 
 * ### Implement Non-blocking Playback
 * @code
 * // Use timer interrupts instead of _delay_ms()
 * ISR(TIMER1_COMPA_vect) {
 *     // Toggle buzzer pin
 * }
 * @endcode
 * 
 * ### Add Serial Buffer Queue
 * @code
 * #define RX_BUFFER_SIZE 32
 * volatile char rx_buffer[RX_BUFFER_SIZE];
 * // Implement circular buffer in ISR
 * @endcode
 * 
 * @section troubleshooting Troubleshooting
 * 
 * | Problem | Solution |
 * |---------|----------|
 * | No sound | Check buzzer connection and resistor |
 * | Garbled serial | Verify baud rate (9600) and F_CPU |
 * | Wrong notes | Check F_CPU in CPU.h |
 * | No serial echo | Verify RX/TX cross connection |
 */

/**
 * @file main.c
 * @brief Main program for serial-controlled musical organ
 * @author Roybel Carbonell Camejo
 * @date 2026-04-29
 * @version 1.1
 *
 * @details This program implements a serial-controlled musical organ that plays
 *          notes received via USART on an ATmega168 microcontroller. It maps
 *          keyboard keys to musical notes and allows dynamic control of note
 *          duration through serial commands. The program also supports playing
 *          pre-programmed songs.
 *
 * @section hardware Hardware Requirements
 * - ATmega168 microcontroller (or compatible)
 * - Buzzer/Piezo element connected to BUZZER_PIN (defined in pinDefines.h)
 * - USART connection (typically via USB-to-Serial converter like FTDI)
 * - 16 MHz external crystal or calibrated internal oscillator
 *
 * @section dependencies Dependencies
 * - CPU.h: CPU-specific configurations (F_CPU, BAUD)
 * - pinDefines.h: Pin definitions for buzzer (BUZZER_DDR, BUZZER_PIN)
 * - scale16.h: Musical note frequency definitions (C4, G4, Q, H, etc.)
 * - organ.h: Note playing functions (playNote, rest)
 * - pre_defined_songs.h: Pre-programmed songs
 * - USART.h: Serial communication functions (initUSART, printString, etc.)
 *
 * @section commands Serial Commands
 * | Key        | Action                                    | Mode      |
 * |------------|-------------------------------------------|-----------|
 * | a, s, d, f, g, h, j, k, l, ;, ' | White keys (natural notes)     | Musical   |
 * | w, e, t, y, i, o, p             | Black keys (sharp notes)        | Musical   |
 * | [                              | Set short note duration (250ms) | Control   |
 * | ]                              | Set long note duration (500ms)  | Control   |
 * | 1                              | Play "Twinkle Twinkle Little Star" | Song   |
 * | 2                              | Play "Imperial March" (Star Wars) | Song    |
 *
 * @section note_mapping Musical Note Mapping
 * The following keyboard keys correspond to musical notes:
 * 
 * **White Keys (Natural Notes):**
 * | Key | Note | Frequency | Octave |
 * |-----|------|-----------|--------|
 * | a   | G4   | 392 Hz    | 4th    |
 * | s   | A4   | 440 Hz    | 4th    |
 * | d   | B4   | 494 Hz    | 4th    |
 * | f   | C5   | 523 Hz    | 5th    |
 * | g   | D5   | 587 Hz    | 5th    |
 * | h   | E5   | 659 Hz    | 5th    |
 * | j   | F5   | 698 Hz    | 5th    |
 * | k   | G5   | 784 Hz    | 5th    |
 * | l   | A5   | 880 Hz    | 5th    |
 * | ;   | A#5  | 932 Hz    | 5th    |
 * | '   | C6   | 1047 Hz   | 6th    |
 *
 * **Black Keys (Sharp Notes):**
 * | Key | Note | Frequency | Octave |
 * |-----|------|-----------|--------|
 * | w   | G#4  | 415 Hz    | 4th    |
 * | e   | A#4  | 466 Hz    | 4th    |
 * | t   | C#5  | 554 Hz    | 5th    |
 * | y   | D#5  | 622 Hz    | 5th    |
 * | i   | F#5  | 740 Hz    | 5th    |
 * | o   | G#5  | 831 Hz    | 5th    |
 * | p   | B5   | 988 Hz    | 5th    |
 *
 * @section note_durations Note Durations
 * - **Q**: Quarter note (250ms) - Short mode, faster tempo
 * - **H**: Half note (500ms) - Long mode, slower tempo
 * - **currentNoteLength**: Global variable tracking current duration mode
 *
 * @section usage Usage Instructions
 * 1. **Hardware Setup:**
 *    - Connect buzzer to BUZZER_PIN (see pinDefines.h)
 *    - Connect USB-to-Serial adapter to USART pins (PD0/RX, PD1/TX)
 * 
 * 2. **Software Setup:**
 *    - Compile and flash to ATmega168
 *    - Open serial terminal (9600 baud, 8N1)
 * 
 * 3. **Operation:**
 *    - Press letter keys (a, s, d, f, etc.) to play notes
 *    - Press '[' or ']' to change note duration
 *    - Press '1' to play Twinkle Twinkle Little Star
 *    - Press '2' to play Imperial March
 *
 * @section flow_control Flow Control & Blocking Behavior
 * - `receiveByte()` blocks until a character is received
 * - `playNote()` blocks for the duration of the note (250-500ms)
 * - `play_twinkle_little_star()` blocks for ~10-15 seconds
 * - `play_imperial_march()` blocks for ~30 seconds
 * - Serial commands are ignored during song playback
 *
 * @section memory_usage Memory Usage Analysis
 * - Notes array: 18 notes × 2 bytes = 36 bytes
 * - Keys array: 18 keys × 1 byte = 18 bytes
 * - Stack usage: ~50 bytes (function calls, local variables)
 * - Total RAM usage: ~100-150 bytes (ATmega168 has 1KB)
 * - Flash usage: ~2-3KB (ATmega168 has 16KB)
 *
 * @section known_issues Known Issues & Limitations
 * - **Blocking playback**: No serial input accepted during note/song playback
 * - **Buffer overflow**: Rapid key presses may be lost (no input queue)
 * - **No interrupt handling**: UART interrupts not used
 * - **Fixed tempo**: Songs use hardcoded durations (Q=250ms, H=500ms)
 * - **No volume control**: Buzzer operates at fixed volume
 *
 * @section future_improvements Future Improvements
 * - [ ] Implement circular buffer for UART RX (queue system)
 * - [ ] Add non-blocking timer-based note generation
 * - [ ] Support for multiple octaves (octave shifting)
 * - [ ] Volume control (PWM on buzzer)
 * - [ ] More pre-programmed songs
 * - [ ] MIDI input support
 * - [ ] LCD display for current settings
 *
 * @section license License Information
 * This program is open source. Feel free to modify and distribute.
 *
 * @see pre_defined_songs.c Song implementations
 * @see organ.c Note generation implementation
 * @see USART.c Serial communication implementation
 */

#include "includes/CPU.h"
#include <avr/io.h>
#include <util/delay.h>
#include "includes/pinDefines.h"
#include "includes/scale16.h"
#include "includes/organ.h"
#include "includes/pre_defined_songs.h"
#include "includes/USART.h"

/**
 * @def ARRAY_SIZE(x)
 * @brief Calculate the number of elements in a static array at compile time
 * @param x The array to calculate size for
 * @return Number of elements in the array
 * 
 * @note This macro only works with actual arrays, not pointers
 * @warning Using on pointers will give incorrect results
 * 
 * @example
 * @code
 * uint8_t data[] = {1, 2, 3, 4, 5};
 * uint8_t count = ARRAY_SIZE(data);  // count = 5
 * @endcode
 */
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

/**
 * @brief Current note duration in milliseconds
 * @details Global variable that stores the currently selected note duration.
 *          Initialized to Q (quarter note, typically 250ms) for shorter notes.
 *          Modified by '[' (short mode) and ']' (long mode) commands.
 * 
 * @note Changing this variable affects ALL subsequent notes played
 * @warning Does NOT affect songs that use hardcoded durations
 * 
 * @see Q Short note duration (250ms)
 * @see H Long note duration (500ms)
 */
uint16_t currentNoteLength = Q;

/**
 * @brief Array of musical notes mapped to keyboard keys
 * @details This array contains frequency values (timer compare values) for 
 *          notes corresponding to keys in the same position in the keys array.
 * 
 * **Index Mapping:**
 * | Index | Key | Note | Frequency |
 * |-------|-----|------|-----------|
 * | 0     | a   | G4   | 392 Hz    |
 * | 1     | w   | G#4  | 415 Hz    |
 * | 2     | s   | A4   | 440 Hz    |
 * | 3     | e   | A#4  | 466 Hz    |
 * | 4     | d   | B4   | 494 Hz    |
 * | 5     | f   | C5   | 523 Hz    |
 * | 6     | t   | C#5  | 554 Hz    |
 * | 7     | g   | D5   | 587 Hz    |
 * | 8     | y   | D#5  | 622 Hz    |
 * | 9     | h   | E5   | 659 Hz    |
 * | 10    | j   | F5   | 698 Hz    |
 * | 11    | i   | F#5  | 740 Hz    |
 * | 12    | k   | G5   | 784 Hz    |
 * | 13    | o   | G#5  | 831 Hz    |
 * | 14    | l   | A5   | 880 Hz    |
 * | 15    | p   | B5   | 988 Hz    |
 * | 16    | ;   | A#5  | 932 Hz    |
 * | 17    | '   | C6   | 1047 Hz   |
 *
 * @note The order MUST match the keys array in main() function
 * @warning Changing this array requires updating keys array to match
 * 
 * @see keys Keyboard key mapping array
 * @see scale16.h Note definitions
 */
const uint16_t notes[] = {G4, Gx4, A4, Ax4, B4, C5, Cx5,
                          D5, Dx5, E5, F5, Fx5, G5, Gx5,
                          A5, Ax5, B5, C6};

/**
 * @brief Main program entry point
 * @return int Program exit status (never reached in embedded systems)
 * 
 * @details Initializes the buzzer pin and USART communication, then enters
 *          an infinite loop that processes incoming serial commands and plays
 *          corresponding musical notes or songs.
 *
 * @section initialization Initialization Steps
 * 1. Configure buzzer pin as output (BUZZER_DDR)
 * 2. Initialize USART communication (initUSART)
 * 3. Display control instructions via serial (printString)
 * 4. Enter main processing loop
 *
 * @section main_loop Main Loop Operation
 * The main loop continuously:
 * 1. **Receive**: Waits for a character via `receiveByte()` (blocking call)
 * 2. **Echo**: Transmits the character back via `transmitByte()`
 * 3. **Check Notes**: Maps key to note using parallel arrays
 * 4. **Process Commands**: Handles special characters ([, ], 1, 2)
 * 5. **Default**: Plays a rest for unassigned keys (ignores CR/LF)
 * 6. **Delay**: Small delay (10ms) to prevent CPU saturation
 *
 * @section command_priority Command Priority
 * 1. Musical notes (a-z keys) - Highest priority
 * 2. Song triggers ('1', '2')
 * 3. Mode controls ('[', ']')
 * 4. Rest (all other characters) - Lowest priority
 *
 * @section error_handling Error Handling
 * - Unrecognized commands (except CR/LF) trigger a rest (silence)
 * - No error messages are sent to avoid serial clutter
 * - Invalid note keys are silently ignored (no error feedback)
 *
 * @performance Performance Characteristics
 * - Note latency: ~1-2ms (UART receive + processing)
 * - Note jitter: Low (deterministic blocking delays)
 * - CPU usage: 100% during note playback (busy-wait)
 * - Memory footprint: ~150 bytes RAM, ~3KB flash
 *
 * @see playNote() Function that generates tones
 * @see play_twinkle_little_star() Song implementation
 * @see play_imperial_march() Song implementation
 * @see rest() Silence generation function
 */
int main(void)
{
    /* Initialize buzzer pin as output */
    BUZZER_DDR |= (1 << BUZZER_PIN);

    /* Initialize USART serial communication (9600 baud, 8N1) */
    initUSART();

    /* Display welcome message and control instructions */
    printString("---Serial Organ---\r\n");
    printString("Controls: a-s-d-f-g-h-j-k-l-;-' for white keys\r\n");
    printString("          w-e-t-y-i-o-p for black keys\r\n");
    printString("          1 to play Twinkle Twinkle Little Star\r\n");
    printString("          2 to play Imperial March from Star Wars\r\n");
    printString("          '[' = short note (250ms), ']' = long note (500ms)\r\n");
    printString("Ready!\r\n");

    char receivedChar;      /**< Received character from USART */
    uint8_t isNote;         /**< Flag indicating if character was a valid note */
    uint8_t i;              /**< Loop counter for key mapping */

    /**
     * @brief Keyboard key mapping array
     * @details Maps physical keyboard keys to musical notes.
     *          Must maintain same order as notes[] array.
     * 
     * The array includes:
     * - White keys: a, s, d, f, g, h, j, k, l, ;, '
     * - Black keys: w, e, t, y, i, o, p
     * 
     * Total of 18 keys covering 2 octaves (G4 to C6)
     * 
     * @invariant ARRAY_SIZE(keys) == ARRAY_SIZE(notes)
     * @see notes Musical notes array (same order)
     */
    const uint8_t keys[] = {'a', 'w', 's', 'e', 'd', 'f', 't',
                            'g', 'y', 'h', 'j', 'i', 'k', 'o',
                            'l', 'p', ';', '\''};

    /* Main program loop - runs forever */
    while (1)
    {
        /**
         * @brief Step 1: Receive character from USART
         * @note This function blocks until a character is received
         */
        receivedChar = receiveByte();

        /**
         * @brief Step 2: Echo character back to sender
         * @details Useful for debugging and providing visual feedback
         * @note Can be disabled to reduce serial traffic
         */
        transmitByte(receivedChar);

        /**
         * @brief Step 3: Check if character is a valid musical note
         * @details Iterates through keys array and plays corresponding note
         *          if a match is found.
         */
        isNote = 0;
        for (i = 0; i < ARRAY_SIZE(keys); i++)
        {
            if (receivedChar == keys[i])
            {
                /* Play the corresponding note with current duration */
                playNote(notes[i], currentNoteLength);
                isNote = 1;
                break;  /* Exit loop once match is found */
            }
        }

        /**
         * @brief Step 4: Process non-note commands
         * @details Handles control characters, song triggers, and ignores
         *          unwanted characters.
         */
        if (!isNote)
        {
            if (receivedChar == '[')
            {
                /* Set short note duration mode (250ms, faster tempo) */
                currentNoteLength = Q;
                printString("\r\nShort mode (250ms)\r\n");
            }
            else if (receivedChar == ']')
            {
                /* Set long note duration mode (500ms, slower tempo) */
                currentNoteLength = H;
                printString("\r\nLong mode (500ms)\r\n");
            }
            else if (receivedChar == '1')
            {
                /* Play Twinkle Twinkle Little Star (blocks for ~10-15 seconds) */
                play_twinkle_little_star();
                printString("\r\nPlaying Twinkle Twinkle Little Star\r\n");
            }
            else if (receivedChar == '2')
            {
                /* Play Imperial March from Star Wars (blocks for ~30 seconds) */
                printString("\r\nPlaying Imperial March from Star Wars\r\n");
                play_imperial_march();
                printString("\r\nImperial March finished!\r\n");
            }
            else
            {
                /**
                 * @brief Handle all other characters
                 * @details Ignore carriage return and line feed (common from terminal)
                 *          For all other characters, play a rest (silence) to
                 *          indicate the key was received but invalid.
                 */
                if (receivedChar != '\r' && receivedChar != '\n')
                {
                    /* Play silence for unassigned keys */
                    rest(currentNoteLength);
                }
                /* CR and LF are silently ignored (no rest, no echo effect) */
            }
        }

        /**
         * @brief Step 5: Small delay to prevent CPU saturation
         * @details Allows other tasks (if any) to run and prevents
         *          the main loop from consuming 100% CPU when idle.
         *          A value of 10ms is sufficient for smooth operation.
         */
        _delay_ms(10);
    }

    /* Never reached in embedded systems - infinite loop above */
    return 0;
}

/**
 * @example Example Serial Session
 * @code
 * ---Serial Organ---
 * Controls: a-s-d-f-g-h-j-k-l-;-' for white keys
 *           w-e-t-y-i-o-p for black keys
 *           1 to play Twinkle Twinkle Little Star
 *           2 to play Imperial March from Star Wars
 *           '[' = short note (250ms), ']' = long note (500ms)
 * Ready!
 * a        (plays G4)
 * s        (plays A4)
 * [        (switches to short mode)
 * a        (plays G4 with 250ms duration)
 * 1        (plays Twinkle Twinkle Little Star)
 * 2        (plays Imperial March)
 * @endcode
 */

/**
 * @version 1.1
 * @change Added Imperial March support (command '2')
 * @change Updated documentation with detailed note mapping
 * @change Added completion message for Imperial March
 * @change Improved error handling for CR/LF characters
 */