// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "node.h"
#include "string.h"

// macros

#define INSERT_BEFORE 1
#define INSERT_AFTER 2
#define DELETE_NODE 3
#define DELETE_LIST 4
#define MAX_LINE_LENGTH 256

// function prototypes
void print_list(list * lst); 
void run(list * lst);


char* clean_word(char* word){

        while(*word == ' '|| *word=='\t') word++;

        int len = strlen(word);

        while(len>0 && (word[len-1]==' '||word[len-1]=='\t')) word[--len]='\0';

        return word;

}

void parse_add_nodes(char* buf, list*lst){
    char* token;
    token = strtok(buf, ",");
    int i=-1;
    while (token != NULL)
    {
        char *word = token;

        word = clean_word(word);

        insert_node_after(lst,i,word);
        i++;
         //get the next token
        token = strtok(NULL, ",");
    }
}



int retNumber(){
    int n;
    char s_char;

    scanf("%c", &s_char);
    scanf("%d", &n);

    if(s_char=='-'){
        n = -n;
    }

    return n;
}
    





int main()
{
    list * lst = (list *) malloc(sizeof(list));
    lst->head = NULL;
	run(lst);
    print_list(lst);
    
    int num1, location;
    char word[MAX_LINE_LENGTH];


    scanf("%d", &num1);

    if(num1==INSERT_BEFORE || num1 == INSERT_AFTER){
        location = retNumber();

        scanf("%s", word);
        char *x = malloc(strlen(word)+1);
        x = strcpy(x, word);
        if(num1==INSERT_BEFORE){ 
            insert_node_before(lst,location, x);
            }
        else if(num1=INSERT_AFTER){
            insert_node_after(lst, location, x);
            }





    }else if(num1==3){

        location = retNumber();

        printf("%d\n", location);

    } 
}

// parse the input
void run(list *lst) 
{
	
    printf("Enter a line of data (or 'exit' to quit):\n");
    char word[MAX_LINE_LENGTH];
    fgets(word,MAX_LINE_LENGTH, stdin);

    
    

}

//Print the list contents
void print_list(list * lst)
{
   
}

