/*			
 *
 * prog4.c - source file originally from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * here to help you get started.
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog4.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the number.
 */

static int32_t turn_number;
static int32_t peg1;
static int32_t peg2;
static int32_t peg3;
static int32_t peg4;


/*
 * set_seed -- uses sscanf to find the random seed value from the string seed_str, 
 *	       then initializes the random number generator by calling srand with the seed
 * INPUTS: seed_str -- a string entered by the user for the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (contains something
 *               other than a single integer), or 1 on success
 * SIDE EFFECTS: initializes pseudo-random number generation using srand
 */
int32_t 
set_seed (const char* seed_str)
{
//    Example of how to use sscanf to read a single integer and check for anything after the integer
//    Seed will contain the number typed by the user (if any) and string post will contain anything after the integer
//    The user should enter only an integer, and nothing else
//    int seed;
//    char post[2];
//    This sscanf statement reads the integer. The return value indicates the number of items read succesfully by sscanf
//    When the user has typed in only an integer, only one item should be read sucessfully 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    Feel free to uncomment these statements, modify them, delete these comments, or change the return statement

//    Your Code Here
    return 0;
}


/*
 * start_game -- creates the solution combination using the approach
 *               described in the assignment specification (using rand)
 * INPUTS: none
 * OUTPUTS: *one -- the first color value in the code (between 1 and 8)
 *          *two -- the second color value in the code (between 1 and 8)
 *          *three -- the third color value in the code (between 1 and 8)
 *          *four -- the fourth color value in the code (between 1 and 8)
 * RETURN VALUE: 1 on success, or 0 on failure (should never fail, though)
 * SIDE EFFECTS: records the solution code for use by make_guess, set turn_number,
 * save values to peg variables
 */
int32_t
start_game (int32_t* one, int32_t* two, int32_t* three, int32_t* four)
{
    //your code here, you may modify the return value if you like
    return 1;
}

/*
 * make_guess -- calculates the number of perfect and misplaced matches
 *               for a given guess, relative to the solution code recorded
 *               earlier by start_game
 * INPUTS: guess_str -- a string consisting of four numbers for the guess
 * OUTPUTS: the following are only valid if the function returns 1
 *          *one -- the first color value in the guessed code (between 1 and 8)
 *          *two -- the second color value in the guessed code (between 1 and 8)
 *          *three -- the third color value in the guessed code
 *                    (between 1 and 8)
 *          *four -- the fourth color value in the guessed code
 *                    (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (represents exactly four
 *               numbers between 1 and 8), or if it is not
 * SIDE EFFECTS: prints the number of matches found using printf
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int32_t
make_guess (const char* guess_str, int32_t* one, int32_t* two, 
	    int32_t* three, int32_t* four)
{
//  One thing you will need to read four numbers from the string
//  The following statement, given char post[2]; and four integers w,x,y,z
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four numbers from the string into the integers and anything else into post
//  The return value indicates the number of items read from the string.
//  The user should enter exaclty 4 integers.
//  Feel free to use this statement, delete these comments, and modify the return statement

//  Your Code Here
    return 1;
}


