#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define D1 "datei1.txt"
#define D2 "datei2.txt"
#define LOG "log.sar"
#define SIZE 1000000L

FILE *fp1, *fp2, *lg;

int logopener() {
	if(lg == NULL) 
		if((lg=fopen(LOG,"a+"))== NULL) 
			fprintf(stderr,"Error : Error Opening the log file.");
		else
			return 1;
	else return 1;
	return 0;
}  

void openFile() {
	fp1 = fopen(D1,"r+");
	if(!ferror(fp1)) {

		if((fp2 = fopen(D2,"w+"))!= NULL) {
					
		}else{
			if(logopener()) {
				fprintf(lg,"Error: Error Opening Destination File\n");		
			}
			fprintf(stderr,"Error: Error Opening Destination File\n");
		}
 
	} else {
		if(logopener()) {
			fprintf(lg,"Error: Error Opening Source File\n");		
		}
		fprintf(stderr,"Error: Error Opening Source File\n");	
	}	
}

void closeFile() {
	fclose(fp1);fclose(fp2);
}

void copyNormal() {
	time_t time1 = time(NULL);
	openFile();
	int c;
	/*setbuf(fp1,puff);
	setbuf(fp2,puff1);*/	
	setvbuf(fp1,NULL,_IOLBF,80);
	setvbuf(fp2,NULL,_IOLBF,80);
	while((c = fgetc(fp1)) != EOF)
		{
			putc(c,fp2);
		}		
	closeFile();
	time_t time2 = time(NULL);
	printf("Time for Line Buffer Copy is %d sec.\n\n",time2-time1);
}

void copyBuffer() {
	time_t time1 = time(NULL);
	openFile();
	int c;
	char puff[BUFSIZ];
	char puff1[BUFSIZ];
	/*setbuf(fp1,puff);
	setbuf(fp2,puff1);*/	
	setvbuf(fp1,puff,_IOFBF,BUFSIZ);
	setvbuf(fp2,puff1,_IOFBF,BUFSIZ);
	while((c = fgetc(fp1)) != EOF)
		{
			putc(c,fp2);
		}		
	closeFile();
	time_t time2 = time(NULL);
	printf("Time for Full Buffer Copy is %d sec.\n\n",time2-time1);
}

void copyNoBuffer() {
	time_t time1 = time(NULL);
	openFile();
	int c;
	char puff[BUFSIZ];
	char puff1[BUFSIZ];
	/*setbuf(fp1,NULL);
	setbuf(fp2,NULL);*/
	setvbuf(fp1,puff,_IONBF,BUFSIZ);
	setvbuf(fp2,puff1,_IONBF,BUFSIZ);
	while((c = fgetc(fp1)) != EOF)
		{
			putc(c,fp2);
		}		
	closeFile();
	time_t time2 = time(NULL);
	printf("Time for No Buffer Copy is %d sec.\n\n",time2-time1);
}


void createFile() {
	if((fp1 = fopen(D1,"w+"))!=NULL) {
		fseek(fp1,SIZE,SEEK_SET);
		putc('x',fp1);	
		fclose(fp1);	
	} else {
		if(logopener()) {
			fprintf(lg,"Error: Error Creating a Example File\n");		
		}
		fprintf(stderr,"Error: Error Creating a Example File\n");
	}	
}

int main(int argc, char* argv[]) {
	createFile();
	copyNormal();
	copyBuffer();
	copyNoBuffer();
	if(lg) fclose(lg);
}
