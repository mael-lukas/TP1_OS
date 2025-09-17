#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

#define N 10

typedef struct integer{
	int value;
    struct integer *next;
}INT_LINKED_LIST;

int length(INT_LINKED_LIST *list){
	if(list == NULL){
		perror("Error: list is NULL\n");
		exit(EXIT_FAILURE);
	}
	int count = 0;
	while (list != NULL){
		count++;
		list = list->next;
	}
	return count;
}

void display(INT_LINKED_LIST *list){
	if(list == NULL){
		perror("Error: list is NULL\n");
		exit(EXIT_FAILURE);
	}
	while (list != NULL){
		printf("<%p>   %d\n",list,list->value);
		list = list->next;
	}
}

void removeFirst(INT_LINKED_LIST *list){
	if(list == NULL){
		perror("Error: list is NULL\n");
		exit(EXIT_FAILURE);
	}
	*list = *list->next;
}

void removeLast(INT_LINKED_LIST *list){
	if(list == NULL){
		perror("Error: list is NULL\n");
		exit(EXIT_FAILURE);
	}
	while((list->next)->next != NULL){
          list = list->next;
    }
    list->next = NULL;
}

void addToLast(INT_LINKED_LIST *list){
  	if(list == NULL){
          perror("Error: list is NULL\n");
          exit(EXIT_FAILURE);
  	}
	int size = length(list);
    while(list->next != NULL){
		list = list->next;
    }
    INT_LINKED_LIST *new = malloc(sizeof(struct integer));
    new->value = list->value+1;
    new->next = NULL;
    list->next = new;
}

void addToFirst(INT_LINKED_LIST *list){
	if(list == NULL){
		perror("Error: list is NULL\n");
		exit(EXIT_FAILURE);
	}

}

int main(void) {
  	struct integer *following = NULL;
    for (int i = N-1; i >= 0; i--){
    	struct integer *current = malloc(sizeof(struct integer));
        current->value = i;
        current->next = following;
        following = current;
    }
    printf("%d\n", length(following));
    display(following);
    removeLast(following);
    removeFirst(following);
    printf("\n");
    display(following);
    addToLast(following);
    printf("\n");
    display(following);
	return 0;
}
