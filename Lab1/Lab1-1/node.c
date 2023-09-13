// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <string.h> // includes strlen(), memcpy()
#include <ctype.h> // includes toupper(), tolower()

// user-defined header files
#include "node.h" // do not modify this file

// put your function prototypes for additional helper functions below:

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
    //after = before +1
    insert_node_before(lst, index+1, word);
}

char *list_to_sentence(list *lst)
{
	
    node * head = lst ->head;
    char *sentence = malloc(strlen(head->word) + 1);
    strcpy(sentence, head->word);
   
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

    
    lst->head = NULL;
}
