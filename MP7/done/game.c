/*
 * Zain Paya (zpaya2)
 *  
 * This file implements the various functions to run a game of 2048.
 * We set up the grid based on the user's input for the rows and columns 
 * and begin the game. The game randomly assigns a cell with number 2 or 4.
 * We take the user's input (w,a,s,d) to move all the cells in that direction.
 * If a cell slides into another cell of the same value, the two cells merge,
 * and the user's score increases by the new cell's value. The goal is to have
 * one cell with the value 2048. The game ends if there is no valid move available,
 * if there are no empty cells for any cell to slide into, or merge.
 *
 * This code also demonstrates the usage of heap memory for the dynamic size
 * of the grid. We use the standard malloc, calloc, realloc, and free functions to
 * accomplish this.
 * 
 */

#include "game.h"


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    // Allocates heap memory for the new game
    game * newgame = malloc(sizeof(*newgame));
    // Initialize the number of rows, columns, and the starting score.
    newgame->rows = rows;
    newgame->cols = cols;
    newgame->score = 0;

    // Calculate the total number of cells
    unsigned int numcells = rows * cols;
    // Allocate heap memory for the cell array
    newgame->cells = calloc(numcells, sizeof(cell));

    // Initialize the value of every cell to -1
    for(int i = 0; i < numcells; i++) {
        newgame->cells[i] = -1;
    }

	return newgame;
}



void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. */
{
    // If cur_game is initialized
    if(cur_game != NULL) {
        // Free the memory allocated for the cell array
        free(cur_game->cells);
        // Free the memory allocated for the game
        free(cur_game);
        cur_game = NULL;
    }
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    // row and col given to us are 0-indexed
    // Check if the given row and col are out of bounds
    if(row < 0 || row >= cur_game->rows || col < 0 || col >= cur_game->cols)
        return NULL;
    // Calculate the index of the array
    unsigned int idx = row * cur_game->cols + col;
    // Returns the pointer to the cell offset from the start by idx
    return cur_game->cells + idx;
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    int flag = 0; // initially, flag is set to invalid move
    for(int c = 0; c < cur_game->cols; c++) {

        // Initialize an array to check whether the cells have merged yet or not
        int mergeArr[cur_game->rows];
        for(int i = 0; i < cur_game->rows; i++)
            mergeArr[i] = 0;

        for(int r = 1; r < cur_game->rows; r++) {
            cell* cur_cell = get_cell(cur_game, r, c);

            // if the current cell has a value, then we are going to run our checks
            if(*cur_cell != -1) {
                // Get the index of the above cell
                int above_cell_r = r-1;
                // Get the pointer to the above cell
                cell* above_cell = get_cell(cur_game, above_cell_r, c);

                // While the above cell is empty
                while(*above_cell == -1) {
                    // we can move cur_cell to above_cell
                    *above_cell = *cur_cell;
                    *cur_cell = -1;
                    flag = 1;
                    above_cell_r--;
                    // Exits the loop when we reach the topmost cell
                    if(above_cell_r < 0) {
                        above_cell_r++;
                        break;
                    }
                    above_cell = get_cell(cur_game, above_cell_r, c);
                    cur_cell = get_cell(cur_game, above_cell_r+1, c);
                }

                // check if curr_cell can be merged with above_cell
                if(*above_cell == *cur_cell && mergeArr[above_cell_r] == 0) {
                    // we merge the two cells and update the score
                    *above_cell *= 2;
                    *cur_cell = -1;
                    flag = 1;
                    cur_game->score += *above_cell;
                    // Update the mergeArr to indicate that the cell has been merged
                    mergeArr[above_cell_r] = 1;
                }

                // if the two cells have different values, we don't do anything
            }
        }
    }

    return flag;
}

int move_s(game * cur_game) //slide down
{
	int flag = 0; // initially, flag is for invalid move
    for(int c = 0; c < cur_game->cols; c++) {
        
        // Initialize an array to check whether the cells have merged yet or not
        int mergeArr[cur_game->rows];
        for(int i = 0; i < cur_game->rows; i++)
            mergeArr[i] = 0;

        for(int r = cur_game->rows - 2; r >= 0; r--) {
            cell* cur_cell = get_cell(cur_game, r, c);

            // if the current cell has a value, then we are going to run our checks
            if(*cur_cell != -1) {
                // Get the index of the below cell
                int below_cell_r = r+1;
                // Get the pointer to the below cell
                cell* below_cell = get_cell(cur_game, below_cell_r, c);

                // While the below cell is empty
                while(*below_cell == -1) {
                    // we can move cur_cell to below_cell
                    *below_cell = *cur_cell;
                    *cur_cell = -1;
                    flag = 1;
                    below_cell_r++;
                    // Exits the loop when we reach the bottommost cell
                    if(below_cell_r >= cur_game->rows) {
                        below_cell_r--;
                        break;
                    }
                    below_cell = get_cell(cur_game, below_cell_r, c);
                    cur_cell = get_cell(cur_game, below_cell_r-1, c);
                }

                // check if curr_cell can be merged with below_cell
                if(*below_cell == *cur_cell && mergeArr[below_cell_r] == 0) {
                    // we merge the two cells and update the score
                    *below_cell *= 2;
                    *cur_cell = -1;
                    flag = 1;
                    cur_game->score += *below_cell;
                    // Update the mergeArr to indicate that the cell has been merged
                    mergeArr[below_cell_r] = 1;
                }

                // if the two cells have different values, we don't do anything
            }
        }
    }

    return flag;
}

int move_a(game * cur_game) //slide left
{
	int flag = 0; // initially, flag is for invalid move
    for(int r = 0; r < cur_game->rows; r++) {
        
        // Initialize an array to check whether the cells have merged yet or not
        int mergeArr[cur_game->cols];
        for(int i = 0; i < cur_game->cols; i++)
            mergeArr[i] = 0;

        for(int c = 1; c < cur_game->cols; c++) {
            cell* cur_cell = get_cell(cur_game, r, c);

            // if the current cell has a value, then we are going to run our checks
            if(*cur_cell != -1) {
                // Get the index of the left cell
                int left_cell_c = c-1;
                // Get the pointer to the left cell
                cell* left_cell = get_cell(cur_game, r, left_cell_c);

                // While the left cell is empty
                while(*left_cell == -1) {
                    // we can move cur_cell to left_cell
                    *left_cell = *cur_cell;
                    *cur_cell = -1;
                    flag = 1;
                    left_cell_c--;
                    // Exits the loop when we reach the leftmost cell
                    if(left_cell_c < 0) {
                        left_cell_c++;
                        break;
                    }
                    left_cell = get_cell(cur_game, r, left_cell_c);
                    cur_cell = get_cell(cur_game, r, left_cell_c+1);
                }

                // check if curr_cell can be merged with left_cell
                if(*left_cell == *cur_cell && mergeArr[left_cell_c] == 0) {
                    // we merge the two cells and update the score
                    *left_cell *= 2;
                    *cur_cell = -1;
                    flag = 1;
                    cur_game->score += *left_cell;
                    // Update the mergeArr to indicate that the cell has been merged
                    mergeArr[left_cell_c] = 1;
                }

                // if the two cells have different values, we don't do anything
            }
        }
    }

    return flag;
}

int move_d(game * cur_game){ //slide to the right
	int flag = 0; // initially, flag is for invalid move
    for(int r = 0; r < cur_game->rows; r++) {
        
        // Initialize an array to check whether the cells have merged yet or not
        int mergeArr[cur_game->cols];
        for(int i = 0; i < cur_game->cols; i++)
            mergeArr[i] = 0;

        for(int c = cur_game->cols - 2; c >= 0; c--) {
            cell* cur_cell = get_cell(cur_game, r, c);

            // if the current cell has a value, then we are going to run our checks
            if(*cur_cell != -1) {
                // Get the index of the right cell
                int right_cell_c = c+1;
                // Get the pointer to the right cell
                cell* right_cell = get_cell(cur_game, r, right_cell_c);

                // While the right cell is empty
                while(*right_cell == -1) {
                    // we can move cur_cell to right_cell
                    *right_cell = *cur_cell;
                    *cur_cell = -1;
                    flag = 1;
                    right_cell_c++;
                    // Exits the loop when we reach the rightmost cell
                    if(right_cell_c >= cur_game->cols) {
                        right_cell_c--;
                        break;
                    }
                    right_cell = get_cell(cur_game, r, right_cell_c);
                    cur_cell = get_cell(cur_game, r, right_cell_c-1);
                }

                // check if curr_cell can be merged with right_cell
                if(*right_cell == *cur_cell && mergeArr[right_cell_c] == 0) {
                    // we merge the two cells and update the score
                    *right_cell *= 2;
                    *cur_cell = -1;
                    flag = 1;
                    cur_game->score += *right_cell;
                    // Update the mergeArr to indicate that the cell has been merged
                    mergeArr[right_cell_c] = 1;
                }

                // if the two cells have different values, we don't do anything
            }
        }
    }

    return flag;
}

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    for(int r = 0; r < cur_game->rows; r++) {
        for(int c = 0; c < cur_game->cols; c++) {
            // if even one cell is empty, we know that legal moves are possible
            // so return 1
            unsigned int idx = r * cur_game->cols + c;
            if(cur_game->cells[idx] == -1)
                return 1;

            // Calculate indexes of adjacent cells
            int idxup = (r-1) * cur_game->cols + c;
            int idxdown = (r+1) * cur_game->cols + c;
            int idxleft = r * cur_game->cols + (c-1);
            int idxright = r * cur_game->cols + (c+1);
    
            if(r == 0)
                idxup = -1;
            if(c == 0)
                idxleft = -1;
            if(r == cur_game->rows-1)
                idxdown = -1;
            if(c == cur_game->cols-1)
                idxright = -1;

            // check with current's top
            if(idxup != -1 && cur_game->cells[idx] == cur_game->cells[idxup])
                return 1;
            // check with current's bottom
            if(idxdown != -1 && cur_game->cells[idx] == cur_game->cells[idxdown])
                return 1;
            // check with current's left
            if(idxleft != -1 && cur_game->cells[idx] == cur_game->cells[idxleft])
                return 1;
            // check with current's right
            if(idxright != -1 && cur_game->cells[idx] == cur_game->cells[idxright])
                return 1;
        }
    }
    // No legal moves possible
    return 0;
}


void remake_game(game ** _cur_game_ptr, int new_rows, int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
    // Re-initializes rows, cols, and score
    (*_cur_game_ptr)->rows = new_rows;
    (*_cur_game_ptr)->cols = new_cols;
    (*_cur_game_ptr)->score = 0;

    // Caclulate the new total number of cells
    unsigned int numcells = new_rows * new_cols;
    // Reallocate memory for the new array of cells
    (*_cur_game_ptr)->cells = realloc((*_cur_game_ptr)->cells,
                                        numcells * sizeof(cell));

    for(int i = 0; i < numcells; i++) {
        (*_cur_game_ptr)->cells[i] = -1;
    }
}

/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        destroy_game(cur_game);
        return 0;
    }
    return 1;
}
