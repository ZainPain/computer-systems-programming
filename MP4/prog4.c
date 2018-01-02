/* intro paragraph
	Throughout the duration of developing this code, 3 functions were needed inorder to produce a  number matching game with the possibility of 8 numbers and a string of 4 numbers be provided to be
 guessed. Implementing the set seed function was trivial as only thing you were setting was the seed and making sure that only 1 integer was scanned from the seed_str into the memory of seed and post. 
the second function start game just initialized a set of random numbers and stored them at the memory locations for 4 distinct variables and initialized the turn to be 1. It also creates a solution key
 for the game which were stored in the peg variables. The final function was a bit of a challenge in the sense that it was hard to make sure the mismatches weren't overlapping. first you store the guess
string in 4 other variables and then make sure that the guess string isn't an invalid solution such as below 0 or above 8 and obviously not a character but only an integer. Next i check for perfect 
matches and mismatches MIS MATCH BRACKETS WAS A PAIN TO MAKE.*/



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

	int seed;
	char post[2];
	if( sscanf( seed_str, "%d%1s", &seed, post ) == 1){
		srand( seed );
		 	return 1;			  }
		else
			printf("set_seed: invalid seed.\n");
	

//    Example of how to use sscanf to read a single integer and check for anything after the integer
//    Seed will contain the number typed by the user (if any) and string post will contain anything after the integer
//    The user should enter only an integer, and nothing else
//    int seed;
//    char post[2];
//    This sscanf statement reads the integer. The return value indicates the number of items read succesfully by sscanf
//    When the user has typed in only an integer, only one item should be read sucessfully 
//    sscanf (seed_str, "%d%1s", &seed, post)



    return 0;
}


/*
 * start_game -- creates the solution combination using the approach  described in the assignment specification (using rand)
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
	*one = rand() % 8;	//only 0-7 values
	*one = *one + 1;	//made change from above to 1-8
	*two = rand() % 8;	// same as above for next 5 lines
	*two =  *two + 1;
	*three = rand() % 8;
	*three = *three + 1;
	*four = rand() % 8;
	*four = *four + 1;
	turn_number = 1;	//initialized game to turn 1
	peg1 = *one;	// next 4 lines store solutions for game
	peg2 = *two;
	peg3 = *three;
	peg4 = *four;

	
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
char post[2];
	int w,x,y,z;
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int pm = 0;		//# of perfect matches
	int mm = 0;		// amount of mismatches
		
if( sscanf (guess_str, "%d%d%d%d%1s",&w, &x, &y,&z, post) == 4){
	// if scanf was successful than  the guesses are alll integers
	
	*one = w;	//guesses are being stored in the four addresses
	*two = x;
	*three = y;
	*four = z;	
	if( *one > 8 || *one <= 0){
				 printf("make_guess: invlaid guess\n ");	//checking for proper inputs
						return 0;
				 }
	 if( *two > 8 || *two <= 0){
                		 printf("make_guess: invlaid guess\n ");	//checking for proper inputs
						return 0;
				 }
 	 if( *three > 8 || *three <= 0){
               			 printf("make_guess: invlaid guess\n ");	//checking for proper inputs
						return 0;
				      }
  	 if( *four > 8 || *four <= 0){
               			 printf("make_guess: invlaid guess\n ");	//checking for proper inputs

						return 0;
				    }
		
	if(*one == peg1){
		pm = pm + 1;	//if the guess is equivalent to the actual number, 1 perfect match is found
		a = a + 1;
			}
	if(*two == peg2){
		pm = pm + 1;
		b = b + 1;
			}
	if(*three == peg3){
		pm = pm + 1;
		c = c + 1;
			  }
	if(*four == peg4){
		pm = pm + 1; 	// all the perfect matches check
		d = d + 1;
			}
	
	// checking if there are any same numbers stored in the peg's
	if( a == 0 && b == 0 && c == 0 && d == 0){	
		if(*one ==  peg2 || *one ==  peg3 || *one == peg4)
			mm = mm + 1;
		if(*two == peg1 || *two == peg3 || *two ==  peg4)
			mm = mm + 1;
		if(*three == peg1 || *three ==  peg2 || *three == peg4)
			mm = mm + 1;
		if(*four == peg1 || *four == peg2 ||*four ==  peg3)
			mm = mm + 1;
													   }	
	// in the case where there are repeated values in the solution
	// 1 or 2 perfect matches and the others are wrong so you check if the remaining solutions match other pegs for mismatching

 	if(a == 1 && b == 0 && c == 0 && d == 0){			// checked
		if( *two == peg3 || *two == peg4){		// 2=s3 or s4?
			mm = mm + 1;
						 }
						
		if( *three == peg2 || *three == peg4){		//3 = s2 or s4
			mm = mm + 1;
						  }
		if( *four == peg2 || *four == peg3){		// 4 = s2 or s3?
			mm = mm + 1;
						   }
					   }



	if(a == 0 && b == 1 && c == 0 && d == 0){
		if( *one == peg3 || *one == peg4){		// 1 = s3 or s4
                        mm = mm + 1;
                                                 }
                if( *three == peg1 || *three == peg4){		// 3 = s1 or s4
                        mm = mm + 1;
                                                  }
                if( *four == peg1 || *four == peg3){		// 4 = s1 or s3
                        mm = mm + 1;
                                                   }
                                           }
	

	if(a == 0 && b == 0 && c == 1 && d == 0){	
		if( *one == peg2 || *one == peg4){		// 1 = s2 or s4
                        mm = mm + 1;
                                                 }
                if( *two == peg1 || *two == peg4){		// 2 = s1 or s4
                        mm = mm + 1;
                                                  }
                if( *four == peg1 || *four == peg2){		// 4 = s1 or s2
                        mm = mm + 1;
                                                   }
                                           }


	if(a == 0 && b == 0 && c == 0 && d == 1){
		if( *one == peg2 || *one == peg3){		// 1 =s2 or s3
                        mm = mm + 1;
                                                 }
                if( *two == peg1 || *two == peg3){		//2 = s1 or s3
                        mm = mm + 1;
                                                  }
                if( *three == peg1 || *three == peg2){		//3 = s1 or s2
                        mm = mm + 1;
                                                   }
                                           }
	



	if(a == 1 && b == 1 && c == 0 && d == 0){
		if( *three == peg4)		//3 =s4 or 4 = s3
			mm = mm + 1;
				   	    
		if(*four == peg3)
			mm = mm + 1;
						}					    



	if(a == 1 && b == 0 && c == 1 && d == 0){
		if( *two == peg4)		//2 =s4 or 4 =s2
                	mm = mm + 1;
                if(*four == peg2)
			mm = mm + 1;
					   }

	
	if(a == 1 && b == 0 && c == 0 && d == 1){
		if( *three == peg4)		//3 =s4 or 4 = s3
               		 mm = mm + 1;
                if(*four == peg3)
			mm = mm + 1;                    		    
					   }


	
	if(a == 0 && b == 0 && c == 1 && d == 1){
		if( *one == peg2)		//1 =s2 or 2 =s1
                	mm = mm + 1;
                if( *two == peg1)            		
			mm = mm + 1;
					   }



	if(a == 0 && b == 1 && c == 0 && d == 1){
		if( *one == peg3)		//1 =s3 or 3 = s1
               		 mm = mm + 1;	
		if(*three == peg1)
			mm = mm + 1;
                                		    
					   }


	if(a == 0 && b == 1 && c == 1 && d == 0){
		if( *one == peg4)		//1 =s4 or 4 =s1
               		 mm = mm + 1;
                if(*four == peg1)
			mm = mm + 1;       			            
					   }


					
					
					    
	printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", turn_number, pm, mm);
	turn_number = turn_number + 1;
			return 1;					}		
	else{ 
		printf("make_guess: invlaid guess\n ");
	    }		return 0;

//  One thing you will need to read four numbers from the string
//  The following statement, given char post[2]; and four integers w,x,y,z
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four numbers from the string into the integers and anything else into post
//  The return value indicates the number of items read from the string.
//  The user should enter exaclty 4 integers.
//  Feel free to use this statement, delete these comments, and modify the return statement

//  Your Code Here
   
}


