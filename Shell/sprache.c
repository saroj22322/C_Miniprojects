/*! Choose the language the give the output in terminal or shell
* and depending on the flag used
* @autor : Saroj
* @theme : Multidimensional Array
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#ifndef TRUE
	#define TRUE 1
#endif
#ifndef FALSE
	#define FALSE -1
#endif

#define LAN langVal

#if(LAN == 0)
	char* lang[] = {"Hallo, Ich bin Saroj.","Alles gut bei mir.","Ich bin Student","Danke schoen","Tschuess"};
#elif(LAN == 1)
	char* lang[] = {"Hello, I am Saroj,","Everthing is going well.","I am a Student","Thank you","Bye"};
#elif(LAN == 2)
	char* lang[] = {"Namaste, Mero naam Saroj ho.","Sabei thikai xa","Ma bidhyarthi hoon.","Dhandyabad","Bye"};
#endif

int langVal = 0;

void showHelp(void) {
	printf("\n\tWelcome to our program. Help Version:\n"\
		"\n\tSyntax: lang --[OPTIONS] [Language]\n\n"\
		"\t\t --welcome  : Shows the welcome and name in compiled language\n"\
		"\t\t --status   : Shows the current status of the program.\n"\
		"\t\t --identity : Shows the current identity of the programmer.\n"\
		"\t\t --thank    : Shows the Thank you message in compiled language\n"\
		"\t\t --depart   : Shows the Departing message in compiled language\n"\
		"\t\t --help     : Shows this help content.\n"\
		/*"\n\tLanguage 0 => Deutsch(Default) 1 => English 2 => Nepali\n"*/"\n");
}

int checkPos(char* string) {
	char* options[] = {"welcome","status","identity","thank","depart","help",NULL};
	int pos = 0;
	while(*(options+(pos++)) != NULL) {
		if(strcmp(*(options+pos-1),string) == 0) return pos-1;	
	}
	return FALSE;	
}

int checkFlag(char* string) {
	if(*string != '-' || *(string+1) != '-') return FALSE;
	return checkPos(string+2);
}

int main(int argc, char* argv[]) {
	char* ch; int check;
	if(argc < 2) showHelp();
	/*if(argc > 2){
		if(isalpha(argv[2][0]) == 0) {
			check = strtol(argv[2],&ch,10);
			if(check >= 0 && check <3) langVal = check;
			else printf("\n\tError :: Invalid value of language [0-2] (See help with --help option.)\n");
		}else printf("\n\tError :: Int expected : Invalid value of language (See help with --help option.)\n");
	}*/
	int pos = checkFlag(*(argv+1));
	if(pos>= 0 && pos <5) printf("\n\t%s\n\n", *(lang+pos));
	else if(pos == 6) showHelp();
	else {
		printf("\n\tError :: Error in Parameter \033[4m\033[1m%s\033[21m\033[24m\n",*(argv+1));
		showHelp();
	}
	return EXIT_SUCCESS;
}
