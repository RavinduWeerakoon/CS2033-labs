#include <stdio.h>
#include <stdlib.h> // includes malloc(), free(), realloc()
#include <string.h> // includes memcpy()
#include <math.h>
// do not modify this file

// put your function prototypes for additional helper functions below:


// implementation

// This function creates a zero matrix (aka, all cells in the matrix are zero) with the 
// specified dimensions. It is up to you to decide how to allocate memory to store values in 
// int **data, but you must make sure matrix is stored in row-major order. That is, data[r1][c-1] contains the element of the matrix at rth row and cth column (the first 
// row/column is row/column zero).

//For Lab 1.2
typedef struct {
	int **data;
	int num_rows;
	int num_cols;
} matrix;

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
        mat->data[i] = realloc(mat->data[i], sizeof(int)*cols);
        mat->data[i][cols-1] = col[i];
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

int * get_stream(int count){
    int num;
    int * arr = malloc(sizeof(int)*count);

    for(int i=0; i<count;i++){
        scanf("%d", &num);
        arr[i] = num;
    }

    return arr;
}

matrix* mat_from_input(){
        int rows;

    scanf("%d", &rows);
    //printf("Enterd row number is %d\n", rows);
   
    int j = 0;
    char c;
    int* arr = malloc(sizeof(int));
    
    
    int col_count = 0;

    for(int i=0;c!='\n';i++){
        
        scanf("%d%c",&j,&c);
        arr[i] = j;
        arr = realloc(arr,sizeof(int)*(i+2)); 
        col_count++;

        
    }



    matrix * mat = create_matrix(rows,col_count);

    int ** data = mat->data;

    for(int i=0;i<col_count;i++){
        data[0][i] = arr[i];
    }

    int temp_num;
    for(int i=1;i<rows;i++){

        for(int j=0;j<col_count;j++){

            scanf("%d", &temp_num);
            //printf("The tempnum is %d\n", temp_num);
            data[i][j] = temp_num;
        }

    }

    return mat;
}

int get_num(){
    int num;
    scanf("%d", &num);
    return num;
}
int main(int argc, char const *argv[])
{


    matrix * mat = mat_from_input();
    int rows = mat ->num_rows;
    int cols = mat -> num_cols;
    int command;
    while(1){
        scanf("%d", &command);

        if(command==0){
            break;
        }else if(command==2){

            add_row(mat, get_stream(cols));
        }else if(command==3){
            add_col(mat, get_stream(rows));
        }else if(command==4){
           
            int num = get_num();
            increment(mat, num);
        }else if(command==5){
            int num = get_num();
            scalar_multiply(mat, num);
        }else if(command==6){
            int num = get_num();
            scalar_divide(mat, num);
        }else if(command==7){
            int num = get_num();
            scalar_power(mat, num);
        }
        else{
            printf("Invalid Command Try again\n");
        }
    }
    print_matrix(mat);
}
