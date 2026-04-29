#include "includes/CPU.h"
#include <avr/io.h>
#include <util/delay.h>
#include "includes/organ.h"
#include "includes/pinDefines.h"

void play_note(uint16_t half_us, uint16_t duration_ms)
{
    uint16_t cycles = (500000 / half_us) * duration_ms / 1000;

    for (uint16_t i = 0; i < cycles; i++)
    {
        BUZZER_PORT |= (1 << BUZZER_PIN);
        for (uint16_t k = 0; k < half_us; k++)
            _delay_us(1);
        BUZZER_PORT &= ~(1 << BUZZER_PIN);
        for (uint16_t m = 0; m < half_us; m++)
            _delay_us(1);
    }
    _delay_ms(30);
}