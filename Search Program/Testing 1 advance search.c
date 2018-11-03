#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>

//Global Variable:
COORD coordinate={0,0};
int pre,post,hitent,place,count22322,found;
char names[][30]={"Max mustermann","Cristiano Ronaldo", "Lionel Messi", "Neymar","Mesut Oezil","Pogba","Sergio Ramos",
				"Isco","Iniesta","Gerade Pique", "Wagyne Rooney","Steven Gerade","Mbappe","Miroslav Klose","Pepe",
				"Toni Kross","Luka Modric"};

void gotoxy(int x,int y)
{
    coordinate.X=x;
    coordinate.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinate);
}

void htc_fieldclr(int x1,int x2,int y1,int y2)
{
	int i,j;
	for (i=x1;i<=x2;i++)
	for (j=y1;j<=y2;j++)
	{
		gotoxy(i,j);
		printf("%c",32);
	}
}
int htc_gfs(char ch[],int,int);
int htc_pfs(char cha[],int,int,char);
int htc_mmfs(char hair[],int,int,int,char,int pos[]);

int main()
{
	start:
	system("cls");
	char name[30];int out;
	gotoxy(1,1);printf("Enter your name : ");
	out=htc_gfs(name,1,2);
	system("cls");
	if(out!=-1)
	{
	gotoxy(1,2);
	printf("You have selected : %s",names[out]);
	}
	else
	{
			gotoxy(1,2);
			printf("\a Search first");
	}
	char conf=getch();
	if(conf!='n') goto start;
	return EXIT_SUCCESS;
}

int htc_gfs(char ch[],int x1,int y1)
{
	char c;
	pre=post=count22322=0;
	int i=0,top;
	do
	{
		gotoxy(x1+i,y1);c=getch();
		if(c==9) continue;
		if((int)c==-32||c==13)
		{
			i--;
			goto new;
		}
		if (c==8)
		{
			if(i!=0)
			{
				i--;
				printf("\b \b");
			}			
		}
		if(c==0||c==224)
		{
			continue;
		}
	if(c!=8)ch[i]=c;else ch[i]='\0';
		new:ch[i+1]='\0';
		if(count22322==0&&c==13)
	{
		return -1;		
	}
		count22322++;
		top=htc_pfs(ch,x1,y1,c);
	if(c!=8)i++;
	}while (hitent!=1);
	return (top);	
}

int htc_pfs(char cha[],int x1,int y1,char r)
{
	found=0;
	hitent=0;
	pre=post;
	int len,pos[20],i,j,k=0,top;
	gotoxy(x1,y1);printf("%s",cha);
	len=strlen(cha);
	char temp[30],temp2[30];
	strcpy(temp2,cha);
	for (i=0;i<(sizeof(names)/sizeof(names[0]));i++)
	{
		for (j=0;j<len;j++)
		{
			temp[j]=names[i][j];
		}
		temp[j]='\0';
		if(strcmp(strupr(temp),strupr(temp2))==0)
		{
		pos[k]=i;		
		k++;
		found=1;
		}
	}
	top=htc_mmfs(temp2,k,x1,y1,r,pos);
	return (top);
}

int htc_mmfs(char hair[],int num,int x2,int y2,char r,int pos[])
{
	int x_fix=x2,y_initial=y2,i;
    char ch=r,newch;
	gotoxy(x_fix,y_initial+5);
 	while(1)
	{
		if ((int)ch==-32)
		 newch=getch();
 	 	switch((int)newch)
		{
	   		case 80: //Code for DOWN arrow equivalent to P
	    	place++;
	    	if (place==num) place=0;
		   	 break;
	   		case 72: //Code for UP arrow quivalent to H
	    	place--;
	   		 if(place<0) place=num-1;
	    	break;
		}
		if(post!=num) place=0;
		post=num;
		if((int)newch!=72&&(int)newch!=80)
		{
		htc_fieldclr(x2,30,y2+2,y2+2+pre);
		}
		if(found!=1)
		{
			gotoxy(x_fix,y_initial+2);printf("No result!!");
			if(r==13){
				printf("\a");
				return 0;
			}
		}
		if(hair[0])
		{
		for(i=0;i<num;i++)
		{
			gotoxy(x_fix,y_initial+2+i);printf("  %s",names[pos[i]]);
			gotoxy(x_fix,y_initial+2+i);printf("  %s",hair);
		}
		for (i=0;i<num;i++)
			if (place==i)
			{
				gotoxy(x_fix,y_initial+2+i);printf("->%s",names[pos[i]]);
				gotoxy(x_fix,y_initial+2+i);printf("->%s",hair);
		
				break;
			}
		}
		else	
		{
			gotoxy(x_fix,y_initial+2);printf("Enter something!!");
			if(r==13){
				printf("\a");
				return 0;
			}
		}
		if(ch==13)
		{
			hitent=1;
			break;
		}
		break;
	}	
	return (pos[i]);
}

