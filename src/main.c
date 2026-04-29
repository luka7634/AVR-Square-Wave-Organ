/**
 * @file main.c
 * @brief Main program for serial-controlled musical organ
 * @author Roybel Carbonell Camejo
 * @date 2026-04-29
 * @version 1.0
 *
 * @details This program implements a serial-controlled musical organ that plays
 *          notes received via USART on an ATmega168 microcontroller. It maps
 *          keyboard keys to musical notes and allows dynamic control of note
 *          duration through serial commands.
 *
 * @section hardware Hardware Requirements
 * - ATmega168 microcontroller
 * - Buzzer/Piezo element connected to BUZZER_PIN
 * - USART connection (typically via USB-to-Serial converter)
 *
 * @section dependencies Dependencies
 * - CPU.h: CPU-specific configurations
 * - pinDefines.h: Pin definitions for buzzer
 * - scale16.h: Musical note frequency definitions
 * - organ.h: Note playing functions
 * - pre_defined_songs.h: Pre-programmed songs
 * - USART.h: Serial communication functions
 *
 * @section commands Serial Commands
 * | Key      | Action                                    |
 * |----------|-------------------------------------------|
 * | a, s, d, f, g, h, j, k, l, ;, ' | White keys (natural notes)     |
 * | w, e, t, y, i, o, p             | Black keys (sharp notes)        |
 * | [                              | Set short note duration (250ms) |
 * | ]                              | Set long note duration (500ms)  |
 * | 1                              | Play "Twinkle Twinkle Little Star" |
 *
 * @section note_mapping Musical Note Mapping
 * The following keyboard keys correspond to musical notes:
 * - a: G4    | w: G#4  | s: A4    | e: A#4  | d: B4
 * - f: C5    | t: C#5  | g: D5    | y: D#5  | h: E5
 * - j: F5    | i: F#5  | k: G5    | o: G#5  | l: A5
 * - ;: A#5   | p: B5   | ': C6
 *
 * @section note_durations Note Durations
 * - Q: Quarter note (250ms) - Short mode
 * - H: Half note (500ms) - Long mode
 *
 * @section usage Usage Instructions
 * 1. Connect serial terminal to the microcontroller (baud rate defined in USART.h)
 * 2. Press keyboard keys to play corresponding notes
 * 3. Use '[' and ']' to change note duration
 * 4. Press '1' to play a pre-programmed song
 *
 * @section known_issues Known Issues
 * - The current implementation is blocking during note playback, which may cause
 *   character loss if multiple keys are pressed rapidly.
 * - A queue-based buffering system is recommended for future improvements.
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
 * @brief Calculate the number of elements in a static array
 * @param x The array to calculate size for
 * @return Number of elements in the array
 */
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

/**
 * @brief Current note duration in milliseconds
 * @details Global variable that stores the currently selected note duration.
 *          Initialized to Q (quarter note, typically 250ms).
 *          Modified by '[' and ']' commands.
 */
uint16_t currentNoteLength = Q;

/**
 * @brief Array of musical notes mapped to keyboard keys
 * @details This array contains frequency values for notes corresponding to keys:
 *          index 0: 'a' -> G4
 *          index 1: 'w' -> G#4
 *          index 2: 's' -> A4
 *          ... and so on
 *
 * @note The order must match the keys array in main() function
 * @see keys array in main() function
 */
const uint16_t notes[] = {G4, Gx4, A4, Ax4, B4, C5, Cx5,
						  D5, Dx5, E5, F5, Fx5, G5, Gx5,
						  A5, Ax5, B5, C6};

/**
 * @brief Main program entry point
 * @return int Program exit status (never reached in embedded systems)
 *
 * @details Initializes the buzzer pin and USART communication, then enters
 *          an infinite loop that:
 *          1. Waits for a character via USART
 *          2. Echoes the character back
 *          3. If the character is a valid key, plays the corresponding note
 *          4. If it's a command, changes settings or plays a song
 *          5. Otherwise, plays a rest (silence)
 *
 * @section initialization Initialization Steps
 * - Configure buzzer pin as output
 * - Initialize USART communication
 * - Display control instructions
 * - Enter main processing loop
 *
 * @section main_loop Main Loop Operation
 * The main loop continuously:
 * - Receives characters via `receiveByte()` (blocking call)
 * - Echoes characters via `transmitByte()`
 * - Maps keys to notes using parallel arrays
 * - Processes special commands
 * - Adds small delay to prevent CPU saturation
 */
int main(void)
{
	/* Initialize buzzer pin as output */
	BUZZER_DDR |= (1 << BUZZER_PIN);

	/* Initialize USART serial communication */
	initUSART();

	/* Display welcome message and instructions */
	printString("---Serial Organ---\r\n");
	printString("Controls: a-s-d-f-g-h-j-k-l-;-' for white keys\r\n");
	printString("          w-e-t-y-i-o-p for black keys\r\n");
	printString("          1 to play Twinkle Twinkle Little Star\r\n");
	printString("          2 to play Imperial March from Star Wars\r\n");
	printString("          '[' = short note (250ms), ']' = long note (500ms)\r\n");
	printString("Ready!\r\n");

	char receivedChar;
	uint8_t isNote;
	uint8_t i;

	/**
	 * @brief Keyboard key mapping array
	 * @details Maps physical keyboard keys to musical notes.
	 *          Must maintain same order as notes[] array.
	 * @see notes array
	 */
	const uint8_t keys[] = {'a', 'w', 's', 'e', 'd', 'f', 't',
							'g', 'y', 'h', 'j', 'i', 'k', 'o',
							'l', 'p', ';', '\''};

	/* Main program loop */
	while (1)
	{
		/* Wait for and receive a character (blocking) */
		receivedChar = receiveByte();

		/* Echo the character back to the sender */
		transmitByte(receivedChar);

		/* Check if received character is a valid musical note key */
		isNote = 0;
		for (i = 0; i < ARRAY_SIZE(keys); i++)
		{
			if (receivedChar == keys[i])
			{
				/* Play the corresponding note with current duration */
				playNote(notes[i], currentNoteLength);
				isNote = 1;
				break;
			}
		}

		/* Process non-note commands */
		if (!isNote)
		{
			if (receivedChar == '[')
			{
				/* Set short note duration mode */
				currentNoteLength = Q;
				printString("\r\nShort mode (250ms)\r\n");
			}
			else if (receivedChar == ']')
			{
				/* Set long note duration mode */
				currentNoteLength = H;
				printString("\r\nLong mode (500ms)\r\n");
			}
			else if (receivedChar == '1')
			{
				/* Play pre-programmed song */
				play_twinkle_little_star();
				printString("\r\nPlaying Twinkle Twinkle Little Star\r\n");
			}
			else if (receivedChar == '2')
			{
				printString("\r\nPlaying Imperial March from Star Wars\r\n");
				play_imperial_march();
			}
			else
			{
				/* Ignore carriage return and line feed characters */
				if (receivedChar != '\r' && receivedChar != '\n')
				{
					/* Play silence (rest) for unassigned keys */
					rest(currentNoteLength);
				}
			}
		}

		/* Small delay to prevent CPU saturation and allow other tasks */
		_delay_ms(10);
	}

	/* Never reached in embedded systems */
	return 0;
}