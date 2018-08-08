#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define DATEI "datei3.txt"

FILE *fp;

typedef struct informationen {
	char name[30];
	char addresse[50];
	unsigned int PLZ;
	char stadt[30];
	struct informationen *next;
}person;

typedef struct container {
	unsigned int count;
	person *head;
}c_person;

c_person* init_Container() {
	c_person* c = malloc(sizeof(c_person));
	if(c == NULL) {
		printf("Kein frei Speicherplatz 2\n");
		exit(EXIT_FAILURE);
	}
	c->head = NULL;
	c->count = 0;
	return c;
}

void add_Person(c_person* con, int pos, person p) {
	person *help, *new, *last = NULL;
	int i = 0;
	if((new = malloc(sizeof(person))) == NULL) {
		printf("Kein Speicherplatz 1\n");
		exit(EXIT_FAILURE);
	}
	strcpy(new->name, p.name);
	strcpy(new->addresse,p.addresse);
	new->PLZ = p.PLZ;
	strcpy(new->stadt,p.stadt);

	help = con->head;
	if(con->count == 0) {
		con->head = new;
		new->next = NULL;
	} else {
		while(help != NULL && pos != i) {
			last = help;
			help = help->next;
			i++;
		}
		last->next = new;
		new->next = help;
	}
	con->count++;
}

void add_Personen(c_person* con, int num,...) {
	va_list ptr;
	va_start(ptr, num);
	while(num-- >0) {
		add_Person(con,con->count,va_arg(ptr,person));
	}
	va_end(ptr);
}

void show_nodes(c_person *iptr) {
	person *help = iptr->head; int i = 0;
	if(help == NULL) {
		printf("Keine Elementen anzuzeigen.\n");
	} else {
		do {
			printf("%d. Wert ist von %s\n",i+1,help->name);
			help = help->next;
			i++;
		} while(help != NULL);
	}
}

void free_nodes(c_person *iptr) {
	person *help = iptr->head, *last; int i = 0;
	if(help == NULL) {
		return;
	} else {
		do {
			last = help;
			help = help->next;
			free(last);
			i++;
		} while(help != NULL);
	}
	iptr->count = 0;
	iptr->head = NULL;
}

void save_nodes(c_person *iptr) {
	person p;
	fp = fopen(DATEI, "w+");
	if(fp == NULL) {
		printf("Fehler bei Oeffnung der Datei 1\n");
		exit(EXIT_FAILURE);
	}
	person *help = iptr->head;
	if(iptr->count > 0) {	
		for (int i = 0; i < iptr->count; ++i)
		{
			strcpy(p.name,help->name);
			strcpy(p.addresse,help->addresse);
			strcpy(p.stadt,help->stadt);
			p.next = 0;
			p.PLZ = help->PLZ;
			fwrite(&p,sizeof(p),1,fp);
			help = help->next;
		}
	}

	if(fclose(fp) != 0) {
		printf("Fehler bei Abschluss der Datei 1\n");
		exit(EXIT_FAILURE);
	}
}

void read_nodes_from_data(c_person *iptr) {
	free_nodes(iptr);
	if((fp = fopen(DATEI, "r")) == NULL) {
		printf("Fehler bei Oeffnung der Datei 2\n");
	}

	person p;
	while(fread(&p,sizeof(p),1,fp)){
		fprintf(stdout, "%s, %s, %u, %s\n",p.name,p.addresse,p.PLZ,p.stadt);
	}

	if(fclose(fp) != 0) {
		printf("Fehler bei Abschluss der Datei 2\n");
		exit(EXIT_FAILURE);
	}
}

void add_nodes_from_data(c_person *iptr) {
	if((fp = fopen(DATEI, "r")) == NULL) {
		printf("Fehler bei Oeffnung der Datei 2\n");
	}

	person p;
	while(fread(&p,sizeof(p),1,fp)){
		add_Person(iptr,iptr->count,p);
	}

	if(fclose(fp) != 0) {
		printf("Fehler bei Abschluss der Datei 2\n");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char* argv[]) {
	person p1 = {"Saroj Tripathi", "Dorotheenstr. 5B", 30419, "Hannover"};
	person p2 = {"Jay Ojha", "Mohoriya, Lekhnath-11", 33702, "Kaski"};
	person p3 = {"Santosh Tripathi", "Landsteiner Str. 3", 97074, "Wuerzburg"};
	person p4 = {"Sagar Poudel", "Mohoriya, Lekhnath-8", 33702, "Kaski"};
	c_person* con = init_Container();
	add_Personen(con,3,p1,p2,p3);
	add_Personen(con,1,p4);
	show_nodes(con);
	save_nodes(con);
	printf("\n");
	read_nodes_from_data(con);
	printf("\n");
	add_nodes_from_data(con);
	show_nodes(con);
	free_nodes(con);
	free(con);
	return EXIT_SUCCESS;
}