#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct liste {
	int value;
	struct liste *next;
} node;

typedef node* node_ptr;
node_ptr head = NULL;

int main(int argc, char* argv[]) {
	printf("\nGeben Sie 5 Werte ein :\n");
	printf("-----------------------\n\n");
	node_ptr new, help = head;
	char a; int m = 0;	
	node nnode[5];
	do {
		new = &nnode[m];
		new->next = NULL;	
		printf("Geben Sie %d. Nummer ein : ", m+1);
		scanf("%d", &new->value);
		if(head == NULL) {
			head = new;
			new->next = NULL;
		} else {
			help = head;
			while(help->next != NULL) {
				help = help->next;
			}
			help->next = new;
			new->next = NULL;
		}
	} while(m++ < 4);
	help = head;
	int n = 1;	
	printf("\nGegebene Werte sind :\n");
	printf("---------------------\n\n");
	while(help != NULL) {
		printf("%d. Wert gespeichert in %u ist %d \n", n,help,help->value);
		help = help->next;
		n++;
	}
	int hilfe;
	printf("\nWelche Nummer Elemente wollen Sie loeschen ? ");
	scanf("%d", &hilfe);
	if(hilfe < 1 || hilfe > 5) {
		printf("\nKein Element gefunden !\n");
		exit(EXIT_FAILURE);
	}
	if(hilfe == 1) {
		help = head->next;
		head = help;
	} else {
		int n = 1;
		help = head;
		node_ptr help2 = NULL;
		while(++n < hilfe) {
			help = help->next;
		}
		help2 = help->next;
		help->next = help2->next;
	}

	help = head;
	n = 1;	
	printf("\nWerte am Ende sind :\n");
	printf("---------------------\n");
	while(help != NULL) {
		printf("%d. Wert gespeichert in %u ist %d \n", n,help,help->value);
		help = help->next;
		n++;
	}

	return EXIT_SUCCESS;
}