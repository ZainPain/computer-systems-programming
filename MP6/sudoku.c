#include "sudoku.h"
/*This mp was not that difficult. This mp consisted of verifying if a solution
 * existed in a column and a row and the 3x3 box, after that we had to make sure
 * that if a valid solution was to be occurred then all three of the functions
 * didn't result trues. The solve sudoku was the tougher of the 4 functions
 * here.
*/
// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}

//-------------------------------------------------------------------------------------------------
// Start coding your MP here.
// ------------------------------------------------------------------------------------------------

// Function: is_val_in_row
// Return true if "val" already existed in i-th row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
    int k;
    int answer = 0;
        for(k = 0; k < 9; k++){                     //verifying if a solution is present in a given row
            if(val == sudoku[i][k])
               answer = 1;             
        }
        
    
  
  return answer;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  // i -> rows
  // j -> columns
  int l;
  int answer = 0;
  for(l = 0; l < 9; l++){                                  //verifying if the solution is present in a given column
          if(val == sudoku[l][j])
                  answer = 1;
  }         
  return answer;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  int l, k;
  int answer = 0;
  // This whole code walks through a given interval of row and column and checks
  // if that 3x3 box already had a solution present.
  // row 0-2, column 0-2
    if( i >= 0 && i < 3 && j >= 0 && j < 3){ 
            for(l = 0; l < 3; l ++){
                    for(k = 0; k < 3; k ++){
                           if( val == sudoku[l][k])
                            answer = 1;
                    }
            }           
    }
    // row 0-2 column 3-5
     if( i >= 0 && i < 3 && j >= 3 && j < 6){
            for(l = 0; l < 3; l ++){
                    for(k = 3; k < 6; k ++){
                           if( val == sudoku[l][k])
                            answer = 1;
                    }
            }
    }
    // row 0-2 column 6-8
     if( i >= 0 && i < 3 && j >= 6 && j < 9){
            for(l = 0; l < 3; l ++){
                    for(k = 6; k < 9; k ++){
                           if( val == sudoku[l][k])
                            answer = 1;
                    }
            }
    }
    // row 3-5 column 0-2
     if( i >= 3 && i < 6 && j >= 0 && j < 3){
            for(l = 3; l < 6; l ++){
                    for(k = 0; k < 3; k ++){
                           if( val == sudoku[l][k])
                            answer = 1;
                    }
            }
    }
    // row 3-5 column 3-5
     if( i >= 3 && i < 6 && j >= 3 && j < 6){
            for(l = 3; l < 6; l ++){
                    for(k = 3; k < 6; k ++){
                           if( val == sudoku[l][k])
                            answer = 1;
                    }
            }
    }
    // row 3-5 column 6-8
     if( i >= 3 && i < 6 && j >= 6 && j < 9){
            for(l = 3; l < 6; l ++){
                    for(k = 6; k < 9; k ++){
                           if( val == sudoku[l][k])
                            answer = 1;
                    }
            }
    }
     // row 6-8 column 0-2
     if( i >= 6 && i < 9 && j >= 0 && j < 3){
            for(l = 6; l < 9; l ++){
                    for(k = 0; k < 3; k ++){
                           if( val == sudoku[l][k])
                            answer = 1;
                    }
            }
    }
   // row 6-8 column 3-5
     if( i >= 6 && i < 9 && j >= 3 && j < 6){
            for(l = 6; l < 9; l ++){
                    for(k = 3; k < 6; k ++){
                           if( val == sudoku[l][k])
                            answer = 1;
                    }
            }
    }
    // row 6-8 column 6-8
     if( i >= 6 && i < 9 && j >= 6 && j < 9){
            for(l = 6; l < 9; l ++){
                    for(k = 6; k < 9; k ++){
                           if( val == sudoku[l][k])
                            answer = 1;
                    }
            }
    }

  return answer;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  // BEG TODO.
  // if there is 1 valid value in the row column and 3x3 box, the function
  // returns true
  return !is_val_in_row( val, i, sudoku) && !is_val_in_col(val, j, sudoku) && !is_val_in_3x3_zone( val, i, j, sudoku); 
  // END TODO.
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO
          int i, j;
          int k = 0 ;
        
//checking for an unassigned (empty) spot on the sudoku grid
               for(i = 0; i < 9; i++){
                    for( j = 0; j < 9; j++){
                           if( sudoku[i][j] == 0 ){
                                k = 1;         
                                break; 
                           }
        
                           }
                    if( k == 1)     // k=1 means there is empty spot
                        break;
                        }
              if(k == 0)        // k - 0 means all slots filled
                    return 1;
                    

                    
 
                      
                             
                                    
                                            
                      
                         // find a non-filled cell (i, j) 
                                    
                
                for (int num = 1; num <= 9; num++) { 
                            if (is_val_valid( num, i, j, sudoku)) { 
                                          sudoku[i][j] =  num; 
                                                if (solve_sudoku(sudoku)) {
                                                                return 1;
                                                                } 
                                                                }
                                                                }
                                                      sudoku[i][j] = 0; 
                                                        
                              
  return 0;
  // END TODO.
  }
  
