/*									
 *
 * prog4.h - header file from UIUC ECE198KL Spring 2013 Program 4
 *           student code by Steven S. Lumetta
 */

#if !defined(PROG_4_H)
#define PROG_4_H

#include <stdarg.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif //defined(__cplusplus)


/*--------------------------------------------------------------------------*/
/*                                                                          */
/*                  PROGRAM 4 EXTERNALLY DEFINED FUNCTIONS                  */
/*                                                                          */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*                                                                          */
/*                  PROGRAM 4 EXTERNALLY VISIBLE FUNCTIONS                  */
/*                                                                          */
/*--------------------------------------------------------------------------*/

/* 
 * Called when the user enters a string for a game's random seed.  Returns 0
 * if the seed string is invalid, or 1 if the string is a valid number. 
 * When successful, also calls srand with the seed as an argument to 
 * initialize the random number generator.
 */
int32_t set_seed (const char* seed_str);

/*
 * Called before starting the game.  Selects four color values using the
 * algorithm defined in the specification.  Copies those four values into
 * the four integer points passed into the function.  Your code will also
 * need to retain a copy of the 'correct' answer for the game for the 
 * make_guess function (below).  Returns 1 on success, or 0 on error.
 */
int32_t start_game (int32_t* one, int32_t* two, int32_t* three, int32_t* four);

/*
 * Called when the user enters a string t make a guess.  Returns 0 if the
 * guess is invalid, whether because it does not correspond to a sequence
 * of four numbers or because any of the numbers is outside of the range
 * 1 to 8.  Returns 1 on success, copies the guessed values into the
 * integer pointers passed to the function, and prints a message using the
 * format given in the specification to tell the player how many perfect
 * and misplaced matches were found for the guess made.
 */
int32_t make_guess (const char* guess_str, int32_t* one, int32_t* two, 
		    int32_t* three, int32_t* four);

#if defined(__cplusplus)
}
#endif //defined(__cplusplus)

#endif /* PROG_4_H */


