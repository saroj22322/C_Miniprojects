#include <stdio.h>
#include <stdlib.h>


typedef struct baum {
	int wert;
	struct baum *links;
	struct baum *rechts;
} knote;

knote* wurzel;


knote* addNodes(knote* ptr,int val) {
	if(ptr == NULL) {
		ptr = (knote*) malloc(sizeof(knote));
		if(ptr == NULL) {
			printf("Fehler bei Speicherplatz Reservierung !\n");
			exit(EXIT_FAILURE);
		}
		ptr->wert = val;
		ptr->links = NULL;
		ptr->rechts = NULL;
	} else if(ptr->wert >= val) {
		ptr->links = addNodes(ptr->links, val);
	} else if(ptr->wert < val) {
		ptr->rechts = addNodes(ptr->rechts, val);
	}
	return ptr;
}

void listNodes_struct(knote* ptr) {
	if(ptr != NULL) {
		printf("%d ",ptr->wert );
		listNodes_struct(ptr->links);
		listNodes_struct(ptr->rechts);
	}
}

void listNodes(knote* ptr) {
	if(ptr != NULL) {
		listNodes(ptr->links);
		printf("%d ",ptr->wert );
		listNodes(ptr->rechts);
	}
}

void listNodes_bottomToTop(knote* ptr) {
	if(ptr != NULL) {
		listNodes_bottomToTop(ptr->links);
		listNodes_bottomToTop(ptr->rechts);
		printf("%d ",ptr->wert );
	}
}

void suche_ersatz(int *neuwert, knote **zeiger) {
   knote *temp;

   if(*zeiger != NULL) {
      if((*zeiger)->links==NULL) {
         *neuwert=(*zeiger)->wert;
         temp=*zeiger;
         *zeiger=(*zeiger)->rechts;
         free(temp);
      }
      else
         suche_ersatz(neuwert, &((*zeiger)->links));
   }
}

void loeschen(knote** zeiger) {
	knote* temp;
	int tempWert;
	if((*zeiger)->wert == wurzel->wert) {
		printf("Wurzel kann nicht geloescht werden!\n");
		return;
	}

	if((*zeiger) != NULL) {
		if((*zeiger)->links == NULL && (*zeiger)->rechts == NULL) {
			free(*zeiger);
			*zeiger = NULL;
		} else if((*zeiger)->links == NULL) {
			temp = *zeiger;
			*zeiger = (*zeiger)->rechts;
			free(temp);
		} else if((*zeiger)->rechts == NULL) {
			temp = *zeiger;
			*zeiger = (*zeiger)->links;
			free(temp);
		} else {
			suche_ersatz(&tempWert, &((*zeiger)->rechts));
			(*zeiger)->wert = tempWert;
		}
	}
}

void loeschenNode(knote** zeiger, int val) {
	if((*zeiger) == NULL) {
		printf("Kein Wert gefunden !\n");
	} else if((*zeiger)->wert == val) {
		loeschen(zeiger);
	} else if((*zeiger)->wert >= val) {
		loeschenNode(&((*zeiger)->links),val);
	} else {
		loeschenNode(&((*zeiger)->rechts),val);
	}
}
	

int main(int argc, char* argv[]) {
	wurzel = NULL;
	int arr[] = {50,20,90,10,40,70,100,30,60,80,85,82,88,65,75};
	for (int i = 0; i < sizeof(arr)/sizeof(arr[i]); ++i)
	{
		wurzel = addNodes(wurzel,arr[i]);
	}
	listNodes(wurzel);
	printf("\n");
	listNodes_struct(wurzel);
	printf("\n");
	listNodes_bottomToTop(wurzel);
	printf("\n");
	loeschenNode(&(wurzel),70);
	listNodes(wurzel);
	printf("\n");
	listNodes_struct(wurzel);
	printf("\n");
	listNodes_bottomToTop(wurzel);
	printf("\n");
	printf("\n\n");
	return EXIT_SUCCESS;
}