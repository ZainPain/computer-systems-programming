#include "game.h"
#include "getch_fun.h"
#include "test_src/game_test.h"
#include <string.h>

int main(int argc, char *argv[]){
    if(argc != 2){  
        printf("error: Invalid number of Arguments (%d)\n", argc);
        return 0;
    }

    int m = -1;
    
    if (sscanf(argv[1], "%i", &m) != 1) {
        
        printf("error: Input is not an number\n");
        return 0;
    }
    
    int grade = 0;
    int flag;
    int i,j;
    game * game_orig;
    cell * cell_ptr_orig;
    
    if( m == 7)
        goto CASE7;
    

    cell * ptr1;
    cell * ptr2;
    cell * ptr3;
    cell * ptr_ne;
    cell * ptr_e;
    
    game_orig = _make_game(3,2);
    game * game_cpy1 = _make_game(3,2);
    game * game_cpy2 = _make_game(3,2);
    game * game_cpy3 = _make_game(4,2);
    game * no_end_game = _make_game(3,2);
    game * end_game = _make_game(3,2);
    
    cell_ptr_orig = game_orig->cells;
    ptr1 = game_cpy1->cells;
    ptr2 = game_cpy2->cells;
    ptr3 = game_cpy3->cells;
    ptr_ne = no_end_game->cells;
    ptr_e = end_game->cells;
    
    cell temparray[6] = {-1, 2,4,2, -1, 2};
    cell no_end_fullarray[6] = {2,16,4,8,2,8};
    cell end_fullarray[6] = {2,16,4,8,8,2};
    for( i =0; i<6;i++){
        *cell_ptr_orig = temparray[i];
        *ptr1 = temparray[i];
        *ptr2 = temparray[i];
        *ptr3 = temparray[i];
        *ptr_ne = no_end_fullarray[i];
        *ptr_e = end_fullarray[i];
        
        
        cell_ptr_orig++;
        ptr1++;
        ptr2++;
        ptr3++;
        ptr_ne++;
        ptr_e++;
    }
    
    *ptr3 = -1;
    ptr3++;
    *ptr3 = 2;
    
    
    cell * temp_cell;

    switch(m){
        case 0 :
            goto CASE0; 
            break;
        case 1 :
            goto CASE1; 
            break;
        case 2 :
            goto CASE2;
            break;
        case 3 :
            goto CASE3;
            break;
        case 4 :
            goto CASE4;
            break;  
        case 5 :
            goto CASE5;
            break;  
        case 6 :
            goto CASE6;
            break;
        case 8 :
            goto CASE8;
            break;
    }
    



    CASE0: printf("test - make_game() pointer: ");
    game * game1 = make_game(11,32);
    
    if( game1 == NULL){
        printf("fail - invalid pointer\n");
        exit(0);
    }
    else{
        printf("Pass [+5]\n");
        grade += 5;
    }
    
    cell * cell_ptr1;
    cell_ptr1 = game1->cells;

    
    
    printf("test - cells pointer: ");
    if( cell_ptr1 == NULL){
        printf("fail - cells pointer is not initialized\n");
        exit(0);
    }
    else{
        printf("pass [+5]\n");
        grade += 5;
    }
    
    
    printf("test - initialized cells: ");
    flag = 0;
    for(i = 0; i < 11*32;i++){
        if(*cell_ptr1 != -1){
            flag = 1;
            printf("fail - cells are not initialized\n");
            break;
        }
        cell_ptr1++;
    }
    
    if( flag == 0){
        printf("pass [+10]\n");
        grade +=10;
    }
    
    
    printf("test - num rows and cols: ");
    if(( game1->rows == 11 )&&  (game1->cols == 32 )){
        printf("pass [+5]\n");
        grade +=5;
    }
    else{
        printf("fail - number of rows and cols stored incorrectly\n");
    }
    
    _destroy_game(game1);
    printf("Grade: %d / 25\n",grade);
    
    return 0; 
    
    

    
    
    CASE1: printf("test - get_cell(): ");
    flag = 1;
    for( i = 0; i < 3; i++){
        for(j = 0; j<2; j++){
            temp_cell = get_cell(game_orig,i,j);
            if (temp_cell == NULL){
                flag = 2;
                break;
            }
            if ( *get_cell(game_orig,i,j) != temparray[i*2+j]){
                flag = 0;
                break;
            }
        }
        if (flag == 0 || flag == 2)
            break;
    }
    if (flag == 2)
        printf("fail. no points\n");
    else if (flag == 0){
        printf("fail. pts for no NULLS [+2/5] \n");
        grade += 2;
    }
    else{
        printf("[+3]");
        grade += 3;
        
        if(get_cell(game_orig,3,3) == NULL){
            printf("[+2]\n");
            grade +=2;
        }
        else{
            printf("fail to ret null for out of bounds\n");
        }
    }
    
    printf("Grade: %d / 5\n",grade);
    return(0);
    
    CASE2: printf("test - move_d ret: ");
    int move_ret = move_d(game_cpy1);
    
    
    
    if( move_ret == 0){
        printf("pass [+1] \n");
        grade += 1;
    }
    else
        printf("fail - move_d returns the incorrect value\n");
    
    
    printf("test - move_d tiles move correctly: ");
    
    ptr1 = game_cpy1->cells;
    ptr2 = game_cpy2->cells;
    
    flag = 1;
    for( i = 0; i < 6; i ++){
        if (*ptr1 != *ptr2){
            printf("fail\n");
            flag = 0;
            break;
        }
        ptr1++;
        ptr2++;
    }
    if (flag == 1) {
        printf("pass [+5] \n");
        grade +=5;
    }
    
    printf("test - move_d retest for segfault: ");
    move_d(game_cpy1);
    
    printf("pass [+1]\n");
    grade += 1;
    
    printf("Grade: %d / 7\n",grade);
    return(0);

    CASE3: printf("test - move_a tiles: ");
    move_ret = move_a(game_cpy2);
    
    
    cell cv8[6] = {2,-1,4,2,2,-1};
    
    ptr1 = game_cpy2->cells;
    flag = 1;
    for( i = 0; i < 6; i ++){
        if (*ptr1 != cv8[i]){
            printf("fail - move_a does not move tiles correctly\n");
            flag = 0;
            break;
        }
        ptr1++;
    }
    if (flag == 1) {
        printf("pass [+5] \n");
        grade += 5;
    }
    
    printf("test - move_a ret val + 2nd call: ");
    
    if ((move_ret == 1) && (move_a(game_cpy2) == 0)){
        printf("pass [+1]\n");
        grade+=1;
    }
    else{
        printf("fail\n");
    }
    
    printf("Grade: %d / 6\n",grade);
    return(0);

    CASE4: printf("test - move_w with merge logic: ");
    move_ret = move_w(game_cpy3);
    
    
    cell cv10[8] = {4,4,-1,4,-1,-1,-1,-1};
    
    ptr3 = game_cpy3->cells;
    flag = 1;
    for( i = 0; i < 8; i ++){
        if (*ptr3 != cv10[i]){
            printf("fail - move_w does not move tiles correctly\n");
            flag = 0;
            break;
        }
        ptr3++;
    }
    if (flag == 1) {
        printf("pass [+5]\n");
        grade+=5;
    }
    
    printf("test - move_w ret val + 2nd call: ");
    
    if ((move_ret == 1) && (move_w(game_cpy3) == 1)){
        printf("pass [+1]\n");
        grade+=1;
    }
    else{
        printf("fail\n");
    }


    printf("test - move_w 2nd call + merge: ");
    
    
    cell cv11[8] = {4,8,-1,-1,-1,-1,-1,-1};
    ptr3 = game_cpy3->cells;
    flag = 1;
    for( i = 0; i < 8; i ++){
        if (*ptr3 != cv11[i]){
            printf("fail - move_w does not move tiles correctly\n");
            flag = 0;
            break;
        }
        ptr3++;
    }
    if (flag == 1) {
        printf("pass [+5]\n");
        grade +=5;
    }
    printf("Grade: %d / 11\n",grade);
    return(0);


    CASE5: printf("test - move_s with merge logic: ");
    move_ret = move_s(game_cpy1);
    
    
    cell cv12[6] = {-1,-1,-1,2,4,4};
    
    ptr1 = game_cpy1->cells;
    flag = 1;
    for( i = 0; i < 6; i ++){
        if (*ptr1 != cv12[i]){
            printf("fail - move_s does not move tiles correctly\n");
            flag = 0;
            break;
        }
        ptr1++;
    }
    if (flag == 1) {
        printf("pass [+5]\n");
        grade+=5;
    }

    printf("test - move_s ret val + 2nd call: ");
    
    if ((move_ret == 1) && (move_s(game_cpy1) == 0)){
        printf("pass [+1]\n");
        grade+=1;
    }
    else{
        printf("fail\n");
    }
    printf("Grade: %d / 6\n",grade);
    return(0);


    CASE6: printf("test - legal move check: ");
    if( legal_move_check(no_end_game) == 1 ){
        printf("[+2]");
        grade += 2;
    }
    if ( legal_move_check(end_game) == 0){
        printf("[+8]");
        grade += 8;
    }
    else{
        printf("failed to detect end game");
    }
    printf("\n");
    
    printf("Grade: %d / 10\n",grade);
    return(0);


    CASE7: printf("RUN WITH VALGRIND! +5 if no invalid reads or memory leaks\n test - remake game: ");
    game_orig = _make_game(7,2);
    
    remake_game(&game_orig,5,5);
    
    if (game_orig == NULL){
        printf("fail, game ptr is NULL. ");
        goto FAIL_RM;
    }
    else{
        printf("[+2]");
        grade+=2;
    }
    cell_ptr_orig = game_orig->cells;
    
    if( cell_ptr_orig == NULL){
        printf("fail, cells pointer is NULL.\n");
        goto FAIL_RM;
    }
    else{
        printf("[+2]\n");
        grade += 2;
    }
    
    
    printf(" test - rm game rows and cols:   ");
    if(game_orig->rows == 5 && game_orig->cols == 5){
        printf("[+2]");
        grade+=2;
    }
    else{
        printf("fail - not reinitualized.\n");
    }

    flag = 0;
    for(i = 0;i < 25; i++){
            if (*cell_ptr_orig != -1){
                printf("cells not reinitialized.");
                flag = 1;
                break;
            }
            cell_ptr_orig++;
    }
    
    if(flag == 0){
        printf("[+4]");
        grade+=4;
    }
    
    FAIL_RM: printf("\n");
    
    _destroy_game(game_orig);
    
    printf("Grade: %d / 10\n",grade);
    return(0);
    

    
    CASE8: printf("RUN WITH VALGRIND! \n test - destroy game : +5 if no memory leaks\n");
    destroy_game(game_cpy1);
    destroy_game(game_cpy2);
    destroy_game(game_cpy3);
    destroy_game(game_orig);
    destroy_game(no_end_game);
    destroy_game(end_game);

    
    return(0);

    
    return 0;
}
