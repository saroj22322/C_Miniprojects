#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <stdarg.h>

typedef struct liste {
	int val;
	struct liste *next;
} elem;

typedef struct container {
	int count;
	struct liste *first;
} iliste;

iliste *iliste_init(void) {
	iliste *new;

	new = malloc(sizeof(iliste));
	if(new == NULL) {
		printf("%s","Kein Speicherplatz frei");
		exit(EXIT_FAILURE);
	}

	new->count = 0;
	new->first = NULL;
	return new;
}

void insert_node(iliste *iptr, int pos, int value) {
	elem *new, *help, *last=NULL;
	int i = 0;
	new = malloc(sizeof(elem));
	if(new == NULL) {
		printf("%s","Kein Speicherplatz frei");
		exit(EXIT_FAILURE);
	}
	new->val = value;
	help = iptr->first;
	if(help == NULL) {
		new->next = NULL;
		iptr->first = new;
	} else {
		while(help!=NULL && pos!=i) {
			last = help;
			help = help->next;
			i++;
		}
		last->next = new;
		new->next = help;
	}
	iptr->count++;
}

void delete_node(iliste *iptr,int pos) {
	if(pos >= iptr->count) {
		printf("Err : %d. Stelle (Kein Node gefunden)\n\n",pos);
		return;
	}
	elem *help, *last=NULL;
	int i = 0;
	help = iptr->first;
	if(help == NULL) {
		printf("Nothing to delete\n");
		return;
	} else {
		while(help!=NULL && pos!=i) {
			last = help;
			help = help->next;
			i++;
		}
		last->next = help->next;
		iptr->count--;
	}
}

void show_nodes(iliste *iptr) {
	elem *help = iptr->first; int i = 0;
	if(help == NULL) {
		printf("Keine Elementen anzuzeigen.\n");
	} else {
		do {
			printf("%d. Wert ist %d\n",i,help->val);
			help = help->next;
			i++;
		} while(help != NULL);
	}
}

void free_nodes(iliste *iptr) {
	elem *help = iptr->first, *last; int i = 0;
	if(help == NULL) {
		printf("Kein Speicherplatz zu befreien.\n");
	} else {
		do {
			last = help;
			help = help->next;
			free(last);
			i++;
		} while(help != NULL);
	}
	iptr->count = 0;
	iptr->first = NULL;
}

void add_nodes(iliste *iptr, int num, ...) {
	va_list ptr;
	va_start(ptr,num);
	while(num-- >0) {
		insert_node(iptr,iptr->count,va_arg(ptr,int));
	}
	va_end(ptr);
}



int main(int argc, char* argcv[]) {
	iliste *new = iliste_init();
	insert_node(new,0,20);
	insert_node(new,1,30);
	insert_node(new,2,40);
	insert_node(new,3,50);
	show_nodes(new);
	printf("\nJetzt bei 1 ist 25\n\n");
	insert_node(new,1,25);
	show_nodes(new);
	printf("\nJetzt 1 ,2 und 3 loeschen\n\n");
	delete_node(new,1);
	delete_node(new,2);
	delete_node(new,3);
	add_nodes(new,5,100,200,300,400,500);
	show_nodes(new);
	printf("Anzahl des Nodes : %d\n",new->count);
	free_nodes(new);
	printf("Anzahl des Nodes : %d\n",new->count);
	free_nodes(new);
	free(new);
	return EXIT_SUCCESS;
}