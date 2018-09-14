#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE 255
#define ALLOC_LINE 10

#ifdef __unix__
	#define clrscr() printf("\033[2J")
#elif __BORLAND__ && __MSDOS__
	#include <conio.h>
#elif __WIN32__ || _MSC_VER
	#define clrscr() system("cls")
#else
	#define clrscr() printf("clrscr() - Error ! \n")
#endif

enum { SUCCESS, ERROR };

int readFile(char ***, char *, int *);
char **allocStringArray(int, int);
int addLines(char  ***, int, int, int);
int manageString(char **, int *, int);
int manageStringSize(char **, int, int);
void freeStringArray(char**, int*);
void clean_stdin(void);
void myGet(char*, int);

int main() {
	char **array;
	int line_n = 0, i, auswahl;
	char datei[LINE];
	clrscr();
	do {
		printf("\n\n\t\t Main Menu\n\n"
				"\t\t 1.Read file\n"
				"\t\t 2.Show file\n"
				"\t\t 3.Clear Memory\n"
				"\t\t 4.Exit\n"
				"\n\t\t Select a Option : ");
		auswahl = getchar(); clean_stdin();
		switch(auswahl-48) {
			case 1:
				printf("\n\t\t Geben Sie den Dateiname ein : ");
				scanf("%254s",datei); clean_stdin();
				if(line_n > 0) {
					freeStringArray(array, &line_n);
				}
				if(readFile(&array, datei, &line_n) == SUCCESS)
					printf("\n\t\t Read file Successful!\n\n");
				else
					printf("\n\t\t Read file Error!!\n\n");
				break;
			case 2:
				if(line_n > 0) {
					printf("\n\n");
					for (int i = 0; i < line_n; ++i)
					{
						printf("\t\t");
						printf("%s\n", array[i]);
					}
				}else {
					printf("\n\t\t No file in memory!");
				}
				break;
			case 3:
				if(line_n > 0) {
					freeStringArray(array, &line_n);
					if(line_n == 0) {
						printf("\n\t\t Memory cleared!\n");
					}
				} else {
					printf("\n\t\t No file in memory to clear!");
				}
			default:
					printf("\n\t\t Please select a valid option!\n");
					break;
		}
	}while (auswahl-48 != 4);
	if(line_n > 0) {
		freeStringArray(array, &line_n);
	}
	if(line_n == 0) {
		printf("\n\t\t Exiting....\n\n");
	}
	return EXIT_SUCCESS;
}

int readFile(char ***array, char *fileName, int *line_n) {
	int status = SUCCESS;
	char puff[LINE] = {0};
	char *newline = NULL;
	int line = 0;
	int line_len = 1;
	FILE *ptr;
	if((*array = allocStringArray(ALLOC_LINE,LINE)) != NULL) {
		*line_n = ALLOC_LINE;
		if((ptr = (fopen(fileName, "r"))) != NULL) {
			while(status != ERROR && (fgets(puff, LINE, ptr) != NULL)){
				newline = strchr(puff, '\n');
				if(newline != NULL)
					*newline = '\0';
				strcat((*array)[line],puff);
				if(newline != NULL) {
					line_len = 1;
					line++;
					if(line >= *line_n) {
						int temp;
						*line_n += ALLOC_LINE;
						*array = realloc(*array,(*line_n)*sizeof(**array));
						if(*array != NULL) {
							for (temp = line; temp < *line_n; ++temp)
							{
								(*array)[temp] = (char*) malloc(LINE * sizeof(***array));
								if((*array)[temp] != NULL) {
									(*array)[temp][0] = '\0'; 
								} else {
									status = ERROR;
								}
							}
						} else {
							status = ERROR;
						}

					}
				} else {
					line_len++;
					if(manageStringSize(*array, line, LINE * line_len) != SUCCESS) {
						status = ERROR;
					}
				}
			}
			fclose(ptr);
			if(manageString(*array, line_n, line)!= SUCCESS) {
				status = ERROR;
			}
		} else {
			status = ERROR;
		}
		if(status == ERROR && *line_n > 0) {
			freeStringArray(*array, line_n);
		}
	} else {
		status = ERROR;
	}
	return status;
}

char **allocStringArray(int line_n, int cInLine) {
	char **array;
	int status = SUCCESS;
	int line;
	if(line_n > 0 && cInLine > 0) {
		array = (char**) malloc(line_n * sizeof(*array));
		if(array != NULL) {
			for (line = 0; line < line_n; ++line)
			{
				array[line] = (char*) malloc(cInLine * sizeof(**array));
				if(array[line] != NULL) {
					array[line][0] = '\0'; 
				} else {
					status = ERROR;
				}
			}
		} else {
			status = ERROR;
		}
		if(status == ERROR) {
			freeStringArray(array, &line_n);
		}
	} else {
		return NULL;
	}
	return array;
}

void freeStringArray(char **array, int *line_n) {
	for (int line = 0; line < *line_n; ++line)
	{
		free(array[line]);
	}
	free(array);
	array = NULL;
	*line_n = 0;
}

int manageString(char **array, int *line_n, int line) {
	if(*line_n > line) {
		for (int i = line+1; i < *line_n; ++i)
		{
			free(array[i]);
		}
	}
	*line_n = line+1;
	for (int i = 0; i <= line; ++i)
	{
		if(manageStringSize(array, i, strlen(array[i])+1) != SUCCESS) {
			return ERROR;
		}
	}
	return SUCCESS;
}

int manageStringSize(char **array, int line, int size) {
	if((array[line] = realloc(array[line], size)) != NULL) 
		return SUCCESS;
	else
		return ERROR;

}

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
    fflush(stdin);
}

void myGet(char *str, int max) {
	fgets(str,LINE,stdin);
	char* a;
	for (a = str; *a != '\n'; ++a);
	*a = '\0';
}
