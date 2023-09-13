#include <stdio.h>
#include <stdlib.h> // includes malloc(), free(), realloc()
#include <string.h> // includes memcpy()

#include "chain.h" // do not modify this file

// put your function prototypes for additional helper functions below:
#include <math.h>

// implementation


matrix * copy_matrix(matrix *mat){
    matrix *copy = create_matrix(mat->num_rows, mat->num_cols);
    for(int i=0;i<mat->num_rows;i++){
        for(int j=0;j<mat->num_cols;j++){
            copy->data[i][j] = mat->data[i][j];
        }
    }
    return copy;
}

matrix *create_matrix(int num_rows, int num_cols)
{


    matrix *mat = malloc(sizeof(matrix));
    mat ->num_rows = num_rows;
    mat ->num_cols = num_cols;

    mat ->data = (int**) malloc(sizeof(int*) * num_rows);

    for(int i=0;i<num_rows;i++){
        mat ->data[i] = (int*) calloc(num_cols, sizeof(int));
    }
    
    return mat;
}

void add_row(matrix *mat, int *row)
{
    int rows = mat ->num_rows +1;

    mat ->num_rows = rows;

    mat -> data = (int **)realloc(mat->data, sizeof(int *) * rows);

    mat->data[rows-1] = (int *) malloc(sizeof(int)* mat->num_cols);

    for(int j=0;j<mat->num_cols;j++){
        mat->data[rows-1][j] = row[j];
    }

    free(row);

}

void add_col(matrix *mat, int *col)
{

    int cols = mat ->num_cols + 1;
    mat ->num_cols = cols;

    for(int i=0;i<mat->num_rows;i++){
        int *x = (int *) realloc(mat->data[i], sizeof(int)*cols);
        mat->data[i] = x;
        x[cols-1] = col[i];
    }

    free(col);
    
}

void increment(matrix *mat, int num)
{
    for(int i=0;i<mat->num_rows;i++){
        for(int j=0;j<mat->num_cols;j++){
            mat->data[i][j] += num;
        }
    }
}

void scalar_multiply(matrix *mat, int num)
{
    for(int i=0;i<mat->num_rows;i++){
        for(int j=0;j<mat->num_cols;j++){
            mat->data[i][j] *= num;
        }
    }
}

void scalar_divide(matrix *mat, int num)
{
    if(num == 0){
        printf("Error: Cannot divide by zero\n");
        return;
    }
    for(int i=0;i<mat->num_rows;i++){
        for(int j=0;j<mat->num_cols;j++){
            mat->data[i][j] /= num;
        }
    }
}

void scalar_power(matrix *mat, int num)
{
    for(int i=0;i<mat->num_rows;i++){
        for(int j=0;j<mat->num_cols;j++){
            mat->data[i][j] = pow(mat->data[i][j], num);
        }
    }
}

void delete_matrix(matrix *mat)
{
    for(int i=0;i<mat->num_rows;i++){
        free(mat->data[i]);
    }
    free(mat->data);

}


/*
    DO NOT MODIFY BELOW
*/
// print out matrix in row-major order
// elements in the same row are space-separated
// each row starts in a new line
void print_matrix(matrix *mat) 
{
    int row_idx, col_idx;
    for(row_idx = 0; row_idx < mat->num_rows; ++row_idx) {
        for(col_idx = 0; col_idx < mat->num_cols; ++col_idx) {
            if (col_idx == mat->num_cols-1) {
                printf("%d\n", mat->data[row_idx][col_idx]);
            } else {
                printf("%d ", mat->data[row_idx][col_idx]);
            }
        }
    }
}

//Add the rest of the functions needed for the chain below


void insert_node_before(chain *chn, int index, matrix* mat)
{	
	node *new_node = malloc(sizeof(node));
	new_node->mat = copy_matrix(mat);

	if (chn->head == NULL) {
		new_node->next = new_node;
		new_node->prev = new_node;

		chn->head = new_node;
		return;
	}
	
	int temp_index = index;
	node *temp = chn->head;

	if (temp_index<0) {
		while (temp_index<0) {
			temp = temp->prev;
			temp_index++;
		}
		new_node->next = temp;
		new_node->prev = temp->prev;
		temp->prev->next = new_node;
		temp->prev = new_node;
		return;
	}

	else if (temp_index>0) {
		while (temp_index>1) {
			temp = temp->next;
			temp_index--;
		}
		new_node->next = temp->next;
		temp->next->prev = new_node;
		temp->next = new_node;
		new_node->prev = temp;
		return;
	}

	else {
		temp->prev->next = new_node;
		new_node->prev = temp->prev;
		temp->prev = new_node;
		new_node->next = temp;
	}
}
void insert_node_after(chain* chn, int index, matrix* mat)
{   
    //after = before +1
    insert_node_before(chn, index+1, mat);
}



void delete_node(chain *chn, int index)
{
	if(index==0){
		node *n_next = chn -> head ->next;
		if (n_next){
		n_next -> prev = chn->head -> prev;
        chn->head -> prev -> next = n_next;
		}
		free(chn->head);

		chn-> head = n_next;
		return;
	}else if(index>0){

	    int i = 0;
        node* current = chn->head;
        while (i < index) {
            current = current->next;
            i++;
        }

		current->next->prev = current -> prev;
		current -> prev -> next  = current->next;
        free(current);
	}else{
		int i = 0;
		node * current = chn->head;

		while(i>index){
			current = current ->prev;
			i--;
		}

		current->next->prev = current->prev;
		current->prev->next = current->next;
		free(current);
	}
}

void delete_list(chain* chn)
{
	node* current = chn -> head;

	while(current->next){
		current = current -> next;

		free(current -> prev);

	}

    
    chn->head = NULL;
}