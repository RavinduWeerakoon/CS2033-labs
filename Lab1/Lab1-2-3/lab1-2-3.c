// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "chain.h"

// function prototypes
void print_chain(chain * chn); 
void run(chain * chn);


int main()
{
    chain * chn = (chain *) malloc(sizeof(chain));
    chn->head = NULL;
	run(chn);
    print_chain(chn);
    free(chn);
	return 0;
}

//Print the chain
void print_chain(chain * chn)
{
    
    node * head = chn->head;
    print_matrix(head->mat);
    printf("\n");
    node *temp = head->next;
    while(temp!=head){
        print_matrix(temp->mat);
        printf("\n");
        temp = temp->next;
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

// parse the input
void run(chain *chn) 
{

    matrix * mat = mat_from_input();

    insert_node_after(chn,0,mat);
    
  
    int command;
    int index = 0;
    while(1){
        scanf("%d", &command);

        if(command==0){
            break;
        }else if(command==2){

            add_row(mat, get_stream(mat->num_cols));
        }else if(command==3){
            
            add_col(mat, get_stream(mat->num_rows));
            // add_col(mat, get_stream(rows));
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
    insert_node_after(chn,index,mat);
    index++;

        
    }


    
	
}



