#include <time.h>
#include <stdio.h>
#include <math.h>

#include "cmp_mat.h"
#ifndef SP_MAT
#define SP_MAT
#include "sparsemat.h"
#endif

void destroy_tuples_gold(sp_tuples * mat_t){
	sp_tuples_node * cnode = mat_t->tuples_head;
	
	while(cnode != NULL){
		//printf("(%d,%d)\n",cnode->row,cnode->col);
		sp_tuples_node * nnode = cnode->next;
		free(cnode);
		cnode = nnode;
	}
	
	free(mat_t);
	
}

void delete_tuple_node_gold(sp_tuples * mat_t, int row, int col){
	//int mat_rows = mat_t->m;
	int mat_cols = mat_t->n;
	int idx = row*mat_cols + col;
	
	sp_tuples_node * curr_node = mat_t->tuples_head;
	
	if (curr_node == NULL)
		return;
		
	if (idx == (curr_node->row * mat_cols + curr_node->col)){ //delete head
		
		curr_node = curr_node->next;
		free(mat_t->tuples_head);
		mat_t->tuples_head = curr_node;
		mat_t->nz -= 1;
		return;
	}
		
	while(curr_node->next != NULL ){
		if (idx == (curr_node->next->row * mat_cols + curr_node->next->col)){ //found node to delete
			sp_tuples_node * temp = curr_node->next;
			curr_node->next = curr_node->next->next;
			free(temp);
			mat_t->nz -= 1;
			return;
		}
		curr_node = curr_node->next;
	}
}

void set_tuples_gold(sp_tuples * mat_t, int row, int col, double value)
{
	if (mat_t == NULL)
		return;
	
	if (value == 0)
	{
		delete_tuple_node_gold(mat_t,row,col);	
	}
	else
	{
		int mat_rows = mat_t->m;
		int mat_cols = mat_t->n;
		int idx = row*mat_cols + col;
		
		if ( row < 0 || col < 0 || row >= mat_rows || col >= mat_cols)
		{
			//printf("set_tuples: invalid index (%d,%d)\n",row,col);
			return;
		}

		sp_tuples_node * new_node = malloc(sizeof(sp_tuples_node));
		new_node->row = row;
		new_node->col = col;
		new_node->value = value;
		

		sp_tuples_node * curr_node; 
		

		curr_node = mat_t->tuples_head;

		if (curr_node == NULL || idx < curr_node->row * mat_cols + curr_node->col){ // Insert before head
		   new_node->next = curr_node;
		   mat_t->tuples_head = new_node;
		   mat_t->nz += 1;
		}
		else if( idx == curr_node->row * mat_cols + curr_node->col){ // value exists at head
			curr_node->value = value;
			free(new_node);
		}
		else
		{ 
			while(curr_node->next != NULL &&  // look for node to insert
				idx > (curr_node->next->row * mat_cols + curr_node->next->col )) 
			{
					curr_node = curr_node->next;
			}
			
		
			if(curr_node->next != NULL && idx == (curr_node->next->row * mat_cols + curr_node->next->col ))
			{ // node already has value
				//printf("wowooO!!!");
				curr_node->next->value = value;
				free(new_node);
			}
			else 
			{ //node doesn't have value
				//printf("yeah..\n");
				new_node->next = curr_node->next;
				curr_node->next = new_node;
				mat_t->nz += 1;
			}
			
		}       

	}
    return;
}



sp_tuples * load_tuples_gold(char* input_file)
{
    FILE *f;
    
    if((f = fopen(input_file, "r")) == NULL) /*attempt to open input stream*/
    {
        printf("UNABLE TO OPEN FILE");
        exit(1);
    }
    
    sp_tuples * new_mat_t = malloc(sizeof(sp_tuples));
    
    int rows = -1;
    int cols = -1;
    
    
    fscanf(f, "%i %i\n", &rows, &cols); /*read file*/

    new_mat_t->m = rows;
    new_mat_t->n = cols;
    new_mat_t->tuples_head = NULL;
	new_mat_t->nz = 0;
 //   printf("%i %i\n", rows,cols);
    int i = -1; //new row
    int j = -1; //new column

    double val = 0;
//    printf("scanf output: %i \n",fscanf(f, "%i %i %f\n", &i, &j, &val));
//    printf("%i %i %f\n", i, j, val);

    
    while ( fscanf(f, "%i %i %lf\n", &i, &j, &val) == 3 ){
			
   //         printf("%i %i %f\n", i, j, val);
            set_tuples_gold(new_mat_t, i, j, val);

    }
   
	fclose(f);
	
    return new_mat_t;
}

///////////////////////
int is_different(sp_tuples * matA, sp_tuples * matB){ // return 1 if same, 0 else.
    if (matA == NULL || matB == NULL){
        printf("one or both matrix are NULL\n");
        return 0;
    }

    if (matA->m != matB->m || matB->n != matB->n){
        printf("dimensions don't match\n");
        return 0;
    }

    if(matA->nz != matB->nz){
        printf("nz doesn't match\n");
        return 0;
    }

    sp_tuples_node * currA = matA->tuples_head;
    sp_tuples_node * currB = matB->tuples_head;
    while(currA != NULL){
        if(currB == NULL) {
            printf("number of nodes don't match\n");
            return 0;
        }
		//double diff = fabs(currA->value - currB->value);
        if (currA->row != currB->row || currA->col != currB->col || fabs(currA->value - currB->value) > .0001){
            printf("values in node does not match\n");
            return 0;
        }

        currA = currA->next;
        currB = currB->next;

    }
    if (currB != NULL){
        printf("num of nodes don't match\n");
        return 0;
    }

    return 1;
}


int main(int argc, char *argv[]){
	    
		
	sp_tuples * matA;
		sp_tuples * matB;
    if (argc == 2){
        int s = atoi(argv[1]);
        switch (s){
            case 1:
                printf("Test 1: load tuple\n");
                goto TEST1;
                break;
            case 2:
                printf("Test 2: gv\n");
                goto TEST2;
                break;
		    case 3:
                printf("Test 3: set\n");
                goto TEST3;
                break;
            case 4:
                printf("Test 4: add\n");
                goto TEST4;
                break;
			case 5:
                printf("Test 5: mult\n");
                goto TEST5;
                break;
			case 6:
                printf("Test 6: sparse\n");
                goto TEST6;
                break;
			case 7:
                printf("Test 7: save\n");
                goto TEST7;
                break;
			case 8:
                printf("Test 8: delete_tuples\n");
                goto TEST8;
                break;
            default:
                printf("Error: Valid arguments are 1-8\n");
                return 0;
        }        
        printf("%s\n",argv[1]);
    }
	else{
		printf("invalid # args\n");
		return 0;
	}
	// load test
	
	TEST1:
	matA = load_tuples("load_test.txt");
	matB = load_tuples_gold("load_test.txt");
	if (matA != NULL && matB != NULL){
		if( matA->m == matB->m && matA->n == matB->n &&matA->nz == matB->nz)
			printf("+5: load_tuples: m,n,nnz match\n");
	}
	if (is_different(matA,matB)){
		printf("+5: load_tuples: nodes match\n");
	}
	destroy_tuples_gold(matA);
	destroy_tuples_gold(matB);
	return 0;
	
	//gv_tuples test
	TEST2: 
	matA = load_tuples_gold("load_test.txt");
	if(gv_tuples(matA,1,1) == 0 && gv_tuples(matA,4,1) == -0.82910 && gv_tuples(matA,29,3) == 0.4723 && gv_tuples(matA,31,2) == 0){
		printf("+5: gv_tuples\n");
	}
	
	destroy_tuples_gold(matA);
    return 0;	
	//set_tuples test
	//changevalue anywhere
	TEST3:
	matA = load_tuples_gold("load_test.txt");
	matB = load_tuples_gold("load_test.txt");
	set_tuples_gold(matA,27,9,14);
	set_tuples(matB,27,9,14);
	if (is_different(matA,matB)){
		printf("+5: set_tuples: delete node at tail\n");
	}
	destroy_tuples_gold(matA);
	destroy_tuples_gold(matB);
	
	
	//set at head
	matA = load_tuples_gold("load_test.txt");
	matB = load_tuples_gold("load_test.txt");
	set_tuples_gold(matA,1,1,4.3);
	set_tuples(matB,1,1,4.3);
	if (is_different(matA,matB)){
		printf("+5: set_tuples: add node at head\n");
	}
	destroy_tuples_gold(matA);
	destroy_tuples_gold(matB);
	
	//Add in middle
	matA = load_tuples_gold("load_test.txt");
	matB = load_tuples_gold("load_test.txt");
	set_tuples_gold(matA,5,3,14.3);
	set_tuples(matB,5,3,14.3);
	if (is_different(matA,matB)){
		printf("+5: set_tuples: add node in the middle\n");
	}
	destroy_tuples_gold(matA);
	destroy_tuples_gold(matB);
	
	//Add at end
	matA = load_tuples_gold("load_test.txt");
	matB = load_tuples_gold("load_test.txt");
	set_tuples_gold(matA,5,3,12.53);
	set_tuples(matB,5,3,12.53);
	if (is_different(matA,matB)){
		printf("+5: set_tuples: add node at tail\n");
	}
	destroy_tuples_gold(matA);
	destroy_tuples_gold(matB);
		
	//delete at head
	matA = load_tuples_gold("load_test.txt");
	matB = load_tuples_gold("load_test.txt");
	set_tuples_gold(matA,0,5,0);
	set_tuples(matB,0,5,0);
	if (is_different(matA,matB)){
		printf("+5: set_tuples: delete node at head\n");
	}
	destroy_tuples_gold(matA);
	destroy_tuples_gold(matB);
	
	//delete anywhere else
	matA = load_tuples_gold("load_test.txt");
	matB = load_tuples_gold("load_test.txt");
	set_tuples_gold(matA,0,5,0);
	set_tuples(matB,0,5,0);
	if (is_different(matA,matB)){
		printf("+5: set_tuples: delete node middle\n");
	}
	destroy_tuples_gold(matA);
	destroy_tuples_gold(matB);
	
	//delete end
	matA = load_tuples_gold("load_test.txt");
	matB = load_tuples_gold("load_test.txt");
	set_tuples_gold(matA,30,11,0);
	set_tuples(matB,30,11,0);
	if (is_different(matA,matB)){
		printf("+5: set_tuples: delete node at tail\n");
	}
	destroy_tuples_gold(matA);
	destroy_tuples_gold(matB);
	return 0;
	
	
	TEST4: printf(" ");
	sp_tuples * a_At = load_tuples_gold("a_A.txt");
	sp_tuples * a_Bt = load_tuples_gold("a_B.txt");
	sp_tuples * a_Ct_gold = load_tuples_gold("a_C_gold.txt");
	
	sp_tuples * a_Ct = add_tuples(a_At,a_Bt);
	if (is_different(a_Ct,a_Ct_gold)){
		printf("+5: add_tuples pass\n");
	}
	destroy_tuples_gold(a_At);
	destroy_tuples_gold(a_Bt);
	destroy_tuples_gold(a_Ct);
	destroy_tuples_gold(a_Ct_gold);
	return 0;
	//mult
	TEST5: printf(" ");
	sp_tuples * m_At = load_tuples_gold("m_A.txt");
	sp_tuples * m_Bt = load_tuples_gold("m_B.txt");
	sp_tuples * m_Ct_gold = load_tuples_gold("m_C_gold.txt");
	
	sp_tuples * m_Ct = mult_tuples(m_At,m_Bt);
	
	if (is_different(m_Ct,m_Ct_gold)){
		printf("+10: mult_tuples pass\n");
	}
	destroy_tuples_gold(m_At);
	destroy_tuples_gold(m_Bt);
	destroy_tuples_gold(m_Ct);
	destroy_tuples_gold(m_Ct_gold);
	return 0;
	
	//sparse_tests
	TEST6: printf(" ");
	clock_t start,end;
	start = clock();
	sp_tuples * s_A = load_tuples_gold("s_A.txt");
	sp_tuples * s_B = load_tuples_gold("s_B.txt");
	
	sp_tuples * sm_C_gold = load_tuples_gold("sm_C.txt");
	sp_tuples * sa_C_gold = load_tuples_gold("sa_C.txt");
	sp_tuples * sm_C = mult_tuples(s_A,s_B);
	sp_tuples * sa_C = add_tuples(s_A,s_B);
	
	end = clock();
	if (is_different(sa_C,sa_C_gold)){
		printf("time taken: [%lf]. Only give points for test6 if time is <= 4 seconds\n+5: add_tuples sparse pass\n",(double)(end-start)/CLOCKS_PER_SEC);
	}
	
	if (is_different(sm_C,sm_C_gold)){
		printf("+5: mult_tuples sparse pass\n");
	}
	return 0;
	
	//save
	TEST7:
	printf("testing save_tuples, saving to save_test_tuples.txt\n");
	matA = load_tuples_gold("load_test.txt");
	save_tuples("save_test_tuples.txt",matA);
	return 0;
	
	//
	
	//memory
	TEST8:
	printf("testing destroy_tuples, check valgrind for +5\n");
	sp_tuples * m1 = load_tuples_gold("load_test.txt");
	sp_tuples * m2 = load_tuples_gold("load_test.txt");
	sp_tuples * m4 = add_tuples(m1,m2);
	destroy_tuples(m1);
	destroy_tuples(m2);
	destroy_tuples(m4);
	return 0;
	

}


