#include "includes/CPU.h"
#include <avr/io.h>
#include <util/delay.h>
#include "includes/pinDefines.h"
#include "includes/scale16.h"
#include "includes/organ.h"

int main(void)
{
	BUZZER_DDR |= (1 << BUZZER_PIN);

	const uint16_t estrellita_notas[] = {
		C4, C4, G4, G4, A4, A4, G4,
		F4, F4, E4, E4, D4, D4, C4,
		G4, G4, F4, F4, E4, E4, D4,
		G4, G4, F4, F4, E4, E4, D4,
		C4, C4, G4, G4, A4, A4, G4,
		F4, F4, E4, E4, D4, D4, C4};

	const uint16_t estrellita_duraciones[] = {
		Q, Q, Q, Q, Q, Q, H,
		Q, Q, Q, Q, Q, Q, H,
		Q, Q, Q, Q, Q, Q, H,
		Q, Q, Q, Q, Q, Q, H,
		Q, Q, Q, Q, Q, Q, H,
		Q, Q, Q, Q, Q, Q, H};

	for (uint8_t i = 0; i < 42; i++)
		play_note(estrellita_notas[i], estrellita_duraciones[i]);

	return 0;
}