#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 20
#define INSERT_BEFORE 1
#define INSERT_AFTER 2
#define DELETE_NODE 3
#define DELETE_LIST 4
#define MAX_LINE_LENGTH 256

typedef struct NODE {
	struct NODE *prev;
	struct NODE *next;
    char *word;
} node;

typedef struct {
	node *head;
} list;

// implementation
void insert_node_before(list *lst, int index, char *word)
{	
	node *new_node = malloc(sizeof(node));
	new_node->word = word;

	if (lst->head == NULL) {
		new_node->next = new_node;
		new_node->prev = new_node;

		lst->head = new_node;
		return;
	}
	
	int temp_index = index;
	node *temp = lst->head;

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


void insert_node_after(list *lst, int index, char *word)
{   


    insert_node_before(lst, index+1, word);

}



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
    node *n;
    while (token != NULL)
    {
        char *word = token;


        char *tk = strdup(word);
        
        
        insert_node_after(lst,i,strdup(word));

       
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
   
void print_list(list * lst)
{

    node * head = lst ->head;

    printf("%s\n", head->word);

    node * n = head->next;

    while(n != head && n!=NULL){
        printf("word from the list-%s\n", n->word);
        n = n->next;
    }

   
}

char *list_to_sentence(list *lst)
{
	
    node * head = lst ->head;

    char * sentence = strdup(head->word);

    

    node * n = head->next;

    while(n != head && n!=NULL){
        strcat(sentence, " ");
        strcat(sentence, n->word);
        n = n->next;
    }

    return sentence;

}

void delete_node(list *lst, int index)
{
	if(index==0){
		node *n_next = lst -> head ->next;
		if (n_next){
		n_next -> prev = lst->head -> prev;
        lst->head -> prev -> next = n_next;
		}
		free(lst->head);

		lst-> head = n_next;
		return;
	}

	    int i = 0;
        node* current = lst->head;
        while (i < index) {
            current = current->next;
            i++;
        }

		current->next->prev = current -> prev;
		current -> prev -> next  = current->next;
        free(current);

}

void delete_list(list *lst)
{
	node* current = lst -> head;

	while(current->next){
		current = current -> next;

		free(current -> prev);

	}

    free(current);
    lst->head = NULL;
}




int main(int argc, char const *argv[])
{
    list * lst = malloc(sizeof(lst));
    lst ->head = NULL;



    parse_add_nodes(lst);
    insert_node_before(lst,4,"Small");
    insert_node_after(lst,-1,"in");
    insert_node_after(lst,-1,"South");
    insert_node_after(lst,-1,"Asia");
    delete_node(lst, 5);
    insert_node_before(lst,5,"nation");
    printf("%s\n", list_to_sentence(lst));
    delete_list(lst);
    return 0;


    
}
