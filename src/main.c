#include "includes/CPU.h"
#include <avr/io.h>
#include <util/delay.h>
#include "includes/pinDefines.h"
#include "includes/scale16.h"
#include "includes/organ.h"
#include "includes/pre_defined_songs.h"
#include "includes/USART.h"

int main(void)
{
	BUZZER_DDR |= (1 << BUZZER_PIN);
	initUSART();

	
	return 0;
}