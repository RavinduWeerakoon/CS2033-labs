// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "node.h"
#include <string.h>

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

void parse_add_nodes(list*lst){

    char buf[256];
    scanf("%s", buf);
    
    char* token;
    token = strtok(buf, ",");
    int i=-1;
   
    while (token != NULL)
    {
        char *word = token;
        
        char *temp = malloc(strlen(word)+1);

        strcpy(temp, word);
        
        insert_node_after(lst,i,temp);
        i++;
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
    free(lst);
	return 0;
}

// parse the input
void run(list *lst) 
{
    parse_add_nodes(lst);

    while(1){
    int num1, location;
    char word[MAX_LINE_LENGTH];


    scanf("%d", &num1);
    
    printf("%d\n", num1);
    if(num1==INSERT_BEFORE || num1 == INSERT_AFTER){
        // location = retNumber();
        scanf("%d", &location);

        scanf("%s", word);
        char * tok = malloc(strlen(word)+1);
        strcpy(tok, word);
        printf("%s\n", location);
        if(num1==INSERT_BEFORE){
            printf("Inserted before %s\n", tok);
            insert_node_before(lst,location, tok);
        }else if(num1==INSERT_AFTER){
            insert_node_after(lst, location, tok);
            printf("Inserted after %s\n", tok);
        }
    }else if(num1==DELETE_NODE){

        location = retNumber();

       delete_node(lst, location);

    }else if(num1==DELETE_LIST){
       delete_list(lst);
    }else if(num1==0){
        break;
    } 

    }

    print_list(lst);
}

//Print the list contents
void print_list(list * lst)
{

   
   printf("%s\n", list_to_sentence(lst));
   
}

