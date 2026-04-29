#include "includes/CPU.h"
#include <avr/io.h>
#include <util/delay.h>
#include "includes/scale16.h"
#include "includes/organ.h"
#include "includes/pre_defined_songs.h"

void play_twinkle_little_star()
{
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
        playNote(estrellita_notas[i], estrellita_duraciones[i]);
}

void play_imperial_march()
{
    const uint16_t imperial_notas[] = {
        G3, G3, G3, G3, Dx3, G3, G3, G3, G3, Dx3, G3, C4, C4, C4, G3, C4, Ax3, Ax3, Ax3, F3, Ax3, G3, G3, G3, Dx3, G3, C4, C4, C4, G3, C4, D4, Dx4, E4, F4, F4, F4, F4, F4, Ax3, Ax3, Ax3, F3, Ax3, G3, G3, G3, Dx3, G3, G3};

    const uint16_t imperial_duraciones[] = {
        H, H, H, Q, Q, H, Q, Q, Q, Q, H, Q, Q, Q, Q, H, Q, Q, Q, Q, H, Q, Q, Q, Q, H, Q, Q, Q, Q, H, H, H, H, H, H, Q, Q, H, Q, Q, Q, Q, H, Q, Q, Q, Q, H, H};

#define _num_notes(x) sizeof(x) / sizeof(x[0])

    for (uint8_t i = 0; i < _num_notes(imperial_notas); i++)
        playNote(imperial_notas[i], imperial_duraciones[i]);
}