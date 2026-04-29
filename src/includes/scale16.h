/**
 * @file    scale16.h
 * @brief   Musical note frequency lookup table (16-bit timer values)
 * @author  Roybel Carbonell Camejo
 * @date    2026-04-28
 * 
 * @details This file contains pre-calculated timer compare values
 *          (wavelengths) for generating musical notes with a 16-bit timer.
 *          Each value corresponds to a specific musical pitch.
 * 
 * @note    Values are calculated for 16-bit timer mode
 * @warning These values assume specific timer prescaler settings
 * 
 * @section calculation Calculation Method
 * The wavelength values represent the timer counter top value (OCR)
 * needed to generate specific frequencies. Smaller values = higher pitch.
 * 
 * @section usage Usage Example
 * @code
 * #include "scale16.h"
 * #include "organ.h"
 * 
 * // Play a C major scale
 * playNote(C4, 500);
 * playNote(D4, 500);
 * playNote(E4, 500);
 * playNote(F4, 500);
 * playNote(G4, 500);
 * playNote(A4, 500);
 * playNote(B4, 500);
 * playNote(C5, 500);
 * @endcode
 */

#ifndef SCALE16_H
#define SCALE16_H

/**
 * @defgroup Note_Constants Note Wavelength Constants
 * @brief   Pre-calculated timer values for musical notes
 * @{
 */

/* Octave 3 Notes */
#define A3  2272    /**< A note, 3rd octave (220 Hz) */
#define Ax3 2145    /**< A# note, 3rd octave (233 Hz) */
#define B3  2024    /**< B note, 3rd octave (247 Hz) */
#define C3  3822    /**< C note, 3rd octave (131 Hz) */
#define Cx3 3607    /**< C# note, 3rd octave (139 Hz) */
#define D3  3405    /**< D note, 3rd octave (147 Hz) */
#define Dx3 3214    /**< D# note, 3rd octave (156 Hz) */
#define E3  3033    /**< E note, 3rd octave (165 Hz) */
#define F3  2863    /**< F note, 3rd octave (175 Hz) */
#define Fx3 2702    /**< F# note, 3rd octave (185 Hz) */
#define G3  2551    /**< G note, 3rd octave (196 Hz) */
#define Gx3 2407    /**< G# note, 3rd octave (208 Hz) */

/* Octave 4 Notes (Middle octave) */
#define A4  1136    /**< A note, 4th octave (440 Hz - Concert pitch) */
#define Ax4 1072    /**< A# note, 4th octave (466 Hz) */
#define B4  1012    /**< B note, 4th octave (494 Hz) */
#define C4  1911    /**< C note, 4th octave (262 Hz - Middle C) */
#define Cx4 1803    /**< C# note, 4th octave (277 Hz) */
#define D4  1702    /**< D note, 4th octave (294 Hz) */
#define Dx4 1607    /**< D# note, 4th octave (311 Hz) */
#define E4  1516    /**< E note, 4th octave (330 Hz) */
#define F4  1431    /**< F note, 4th octave (349 Hz) */
#define Fx4 1351    /**< F# note, 4th octave (370 Hz) */
#define G4  1275    /**< G note, 4th octave (392 Hz) */
#define Gx4 1203    /**< G# note, 4th octave (415 Hz) */

/* Octave 5 Notes */
#define A5  568     /**< A note, 5th octave (880 Hz) */
#define Ax5 536     /**< A# note, 5th octave (932 Hz) */
#define B5  506     /**< B note, 5th octave (988 Hz) */
#define C5  955     /**< C note, 5th octave (523 Hz) */
#define Cx5 901     /**< C# note, 5th octave (554 Hz) */
#define D5  851     /**< D note, 5th octave (587 Hz) */
#define Dx5 803     /**< D# note, 5th octave (622 Hz) */
#define E5  758     /**< E note, 5th octave (659 Hz) */
#define F5  715     /**< F note, 5th octave (698 Hz) */
#define Fx5 675     /**< F# note, 5th octave (740 Hz) */
#define G5  637     /**< G note, 5th octave (784 Hz) */
#define Gx5 601     /**< G# note, 5th octave (831 Hz) */

/* Octave 6 Notes */
#define C6  477     /**< C note, 6th octave (1047 Hz) */

/* Notes duration */
#define Q 250 /**< Short note duration */
#define H 500 /**< Long note duration */

/**
 * @defgroup Scale_Notes Scale Note Aliases (4th Octave)
 * @brief   Convenience aliases for standard scale notes in 4th octave
 * @{
 */

#define DO  C4      /**< DO note (C4) - Tonic in C major scale */
#define RE  D4      /**< RE note (D4) - Supertonic */
#define MI  E4      /**< MI note (E4) - Mediant */
#define FA  F4      /**< FA note (F4) - Subdominant */
#define SOL G4      /**< SOL note (G4) - Dominant */
#define LA  A4      /**< LA note (A4) - Submediant */
#define SI  B4      /**< SI note (B4) - Leading tone */

/** @} */
/** @} */

#endif /* SCALE16_H */