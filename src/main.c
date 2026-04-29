#include "includes/CPU.h"
#include <avr/io.h>
#include <util/delay.h>
#include "includes/pinDefines.h"
#include "includes/scale16.h"
#include "includes/organ.h"
#include "includes/pre_defined_songs.h"
#include "includes/USART.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
uint16_t currentNoteLength = Q;

/* Array with a few notes to play */
const uint16_t notes[] = {G4, Gx4, A4, Ax4, B4, C5, Cx5,
						  D5, Dx5, E5, F5, Fx5, G5, Gx5,
						  A5, Ax5, B5, C6};

int main(void)
{
	BUZZER_DDR |= (1 << BUZZER_PIN);
	initUSART();

	printString("---Serial Organ---\r\n");
	printString("Controls: a-s-d-f-g-h-j-k-l-;-' for white keys\r\n");
	printString("          w-e-t-y-i-o-p for black keys\r\n");
	printString("          1 to play Twinkle Twinkle Little Star\r\n");
	printString("          '[' = short note (250ms), ']' = long note (500ms)\r\n");
	printString("Ready!\r\n");
	char receivedChar;
	uint8_t isNote;
	uint8_t i;

	const uint8_t keys[] = {'a', 'w', 's', 'e', 'd', 'f', 't',
							'g', 'y', 'h', 'j', 'i', 'k', 'o',
							'l', 'p', ';', '\''};

	while (1)
	{
		receivedChar = receiveByte();
		transmitByte(receivedChar);

		isNote = 0;
		for (i = 0; i < ARRAY_SIZE(keys); i++)
		{
			if (receivedChar == keys[i])
			{
				playNote(notes[i], currentNoteLength);
				isNote = 1;
				break;
			}
		}

		if (!isNote)
		{
			if (receivedChar == '[')
			{
				currentNoteLength = Q;
				printString("\r\nShort mode (250ms)\r\n");
			}
			else if (receivedChar == ']')
			{
				currentNoteLength = H;
				printString("\r\nLong mode (500ms)\r\n");
			}
			else if (receivedChar == '1')
				play_twinkle_little_star();
			else
			{
				if (receivedChar != '\r' && receivedChar != '\n')
					rest(currentNoteLength);
			}
		}
	}

	return 0;
}