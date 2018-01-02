
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

int main(){
	


	printf("Testing LIL functions\n");
	sp_lils * mat1 = load_lils("load_test.txt");
	printl(mat1);
	printf("+2 for load if the above matches\n");
	
	printf("gv: -0.0322: %lf, 0.537: %lf,0: %lf\n",gv_lils(mat1,0,5),gv_lils(mat1,5,2),gv_lils(mat1,30,4));
	printf("+5 if the above matches for gv\n");
	
	set_lils(mat1,0,5,0);
	set_lils(mat1,0,3,3.452);
	set_lils(mat1,23,3,0);
	set_lils(mat1,4,1,0);
	set_lils(mat1,30,3,0);
	set_lils(mat1,30,11,0);
	set_lils(mat1,31,12,2.44);
	set_lils(mat1,31,14,5.868);
	set_lils(mat1,4,4,0);
	set_lils(mat1,19,7,0);
	set_lils(mat1,23,3,0);
	set_lils(mat1,28,8,0);
	set_lils(mat1,0,0,234.3);
	set_lils(mat1,533,232,12.9);
	printl(mat1);
	printf("+20 for set_lil above matches\n");
	
	
	sp_lils * a_A = load_lils("a_A.txt");
	sp_lils * a_B = load_lils("a_B.txt");
	printf("a_C = a_A+a_B addition in LIL:\n");
	sp_lils * a_C = add_lils(a_A,a_B);
	printl(a_C);
	printf("+5 for add_lils if the above matches\n");
	
	sp_lils * m_A = load_lils("m_A.txt");
	sp_lils * m_B = load_lils("m_B.txt");
	sp_lils * m_C = mult_lils(m_A,m_B);
	printl(m_C);
	printf("+5 for mult_lils if the above matches\n");
	
	sp_lils * matsave = load_lils("load_test.txt");
    printf("saving save_test_lils.txt\n");
	save_lils("save_test_lils.txt",matsave);
	printf("+2 if saved txt matches gold\n");
	
	sp_tuples * t1 = lil2tuples(mat1);
	printt(t1);
	printf("+2 for lil2tuples if above matches\n");
	
	sp_tuples * t2 = load_tuples("a_A.txt");
	sp_lils * l2 = tuples2lil(t2);
	printl(l2);
	printf("+2 for tuples2lil if above matches\n");
	
	
	destroy_lils(mat1);
	destroy_lils(a_A);
	destroy_lils(a_B);
	destroy_lils(a_C);
	
	
	destroy_lils(m_A);
	destroy_lils(m_B);
	destroy_lils(m_C);
	destroy_lils(matsave);
	destroy_lils(l2);
	
	destroy_tuples_gold(t1);
	destroy_tuples_gold(t2);
	printf("check valgrind for +2");
	return 0;
}
	
