/*
Programm mit Doppelt verkettete Listen und Stack Algorithem.
@autor : Saroj Tripathi
@Version : 1.0.0
*/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> // Für offsetof()
#include <string.h>
#define MAXNAME 40

#ifndef uint
	typedef unsigned int uint;
#endif

//Struct definition
typedef struct person {
	uint id; // Kennungsnummer, unterscheiden von anderen.
	char name[MAXNAME]; //Name
	uint alter; // Alter
	struct person *next; 
	struct person *prev;
} per;

//SUCCESS = 0 und FAILURE = 1
enum {SUCCESS, FAILURE};

per *anfang, *end, *stack_ptr;

//Static id wert
uint _id;

//Funktionen Prototypes
int anhaengen(uint,char*,uint);
int comp(per*, per*, uint, int);
int sortieren(uint, int);

int main(int argc, char* argv[]) {
	anfang = NULL;
	end = NULL;
	_id = (end == NULL) ? 1 : end->id;
	anhaengen(_id,"Saroj Tripathi",21);
	anhaengen(_id,"Suman Khanal",26);
	anhaengen(_id,"Manish Bhatt",23);
	anhaengen(_id,"Bimal Adhikari",29);
	anhaengen(_id,"Santosh Tripathi",24);
	sortieren(2,1);
	per *zeiger = anfang;
	while(zeiger != NULL) {
		printf("%u  %s  %u\n", zeiger->id, zeiger->name, zeiger->alter);
		zeiger = zeiger->next;
	}
	printf("\n");
	sortieren(0,1);
	zeiger = anfang;
	while(zeiger != NULL) {
		printf("%u  %s  %u\n", zeiger->id, zeiger->name, zeiger->alter);
		zeiger = zeiger->next;
	}
	return EXIT_SUCCESS;
}

/*Eine Datei hinzufügen. Immer wird am Ende hinzugefügt.
@param : id, Name, und Alter.
@return : SUCCESS wenn erfolgt sonst FAILURE;
*/
int anhaengen(uint pid, char *pname, uint palter) {
	if(end == NULL) {
		if((end = malloc(sizeof(per))) == NULL) {
			fprintf(stderr,"Fehler: Datei hinzufuegen !\n");
			return FAILURE;
		}
	}

	if(anfang == NULL) {
		if((anfang = malloc(sizeof(per))) == NULL) {
			free(end);
			fprintf(stderr,"Fehler: Datei hinzufuegen !\n");
			return FAILURE;
		}
		anfang->id = pid;
		strncpy(anfang->name,pname,MAXNAME);
		anfang->alter = palter;
		anfang->next = NULL;
		anfang->prev = NULL;
		end = anfang;
		_id++;
		return SUCCESS;
	} else {
		per *zeiger, *zeiger1;
		if((zeiger = malloc(sizeof(per))) == NULL) {
			fprintf(stderr, "Fehler: Datei hinzufuegen !\n");
			return FAILURE;
		}
		zeiger->id = pid;
		strncpy(zeiger->name,pname,MAXNAME);
		zeiger->alter = palter;
		zeiger->next = NULL;
		zeiger->prev = end;
		end->next = zeiger;
		end = zeiger;
		_id++;
		return SUCCESS;
	}
}

/*sortiert die gesamte Liste
@param : basis-> 0 für id, 1 für name, 2 für alter ; mode -> 1 für aufsteigende, -1 für absteigende
@return : SUCCESS wenn erfolgt sonst FAILURE;
*/
int sortieren(uint basis, int mode) {
	if(anfang == NULL) {
		fprintf(stderr, "Fehler: Keine Angaben zu sortieren !\n");
		return FAILURE;
	}
	per *zeiger, *zeiger1, *copyhelp, *zeigersave;
	zeiger = anfang;
	while(zeiger != NULL) {
		zeiger1 = zeiger;
		zeigersave = zeiger;		
		zeiger = zeiger->next;
		while(zeiger1 != NULL) {
			if(zeiger1 != zeigersave)
			comp(zeigersave,zeiger1,basis,mode);
			zeiger1 = zeiger1->next;
		}
	}
	return SUCCESS;
}

/* Vergleich zwei Knoten gegeben mithilfe gegeben Basis.
@param : zeiger, zeiger1 -> 2 Blocks zu vergleichen. Basis und mode -> gleich wie bei Sortieren
@return : SUCCESS wenn erfolgt sonst FAILURE;
*/
int comp(per* zeiger, per* zeiger1, uint basis, int mode) {
	uint cmp = 0;
	switch(basis) {
		case 1 :
			cmp = (strcmp(zeiger->name,zeiger1->name) > 1) ? 1 : -1;
			break;
		case 2 :
			cmp = (zeiger->alter > zeiger1->alter) ? 1 : -1;
			break;		
		default:
			cmp = (zeiger->id > zeiger1->id) ? 1 : -1;
	}
	cmp = cmp * mode; // Mode -1 für Absteigen kann Vorzeichen wechseln
	per help;
	if(cmp == 1) {
		uint memToCopy = offsetof(per,next);
		memcpy(&help,zeiger1,memToCopy);
		memcpy(zeiger1,zeiger,memToCopy);
		memcpy(zeiger,&help,memToCopy);
	}
	return SUCCESS;
}


