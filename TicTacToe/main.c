/*!
*	@Name : TicTacToe
*	@autor : Saroj Tripathi
*	@Reference : C von A bis Z (Galileo Computing)
*	@Version: 1.0 (Using row and column input)
*/

//! Checking if stdio library is already included or not.

#ifndef __STDIO_H__
	#include <stdio.h>
	#include <stdlib.h>
#endif

//! Setting a clear screen macro

#ifdef __unix__
	#define clrscr() printf("\033[2J")
#elif __BORLAND__ && __MSDOS__
	#include <conio.h>
#elif __WIN32__ || _MSC_VER
	#define clrscr() system("cls")
#else
	#define clrscr() printf("clrscr() - Error ! \n")
#endif

//! Game Constants

#define ROWS 3
#define COLS 3
#define WIN 1
#define GAMEOVER 0
#define CONTINUE 2
#define X 'X'
#define O 'O' 
#define NOTHING ' '

//! Global Variables

char TicTacToe[ROWS][COLS] = {  {' ',' ',' '},
				{' ',' ',' '},
				{' ',' ',' '}
						};
char P1 = X;
char P2 = O;
unsigned int feld = 9;

//! Function prototypes

void gameScr(void); //! This will print the game screen with updated moves after every moves.
char nextStep(char);//! This will be responsible for setting the turn, validating a move and deciding game end.
unsigned int checkWin(char);//! This will decide the game win situation.

int main(int argc, char* argv[]) {
	char turn = P1;
	char tempturn;
	do { 
		tempturn = turn;
		turn  = (turn == P1) ? nextStep(P1) : nextStep(P2);		
	} while(turn != GAMEOVER && turn != WIN);
	if(turn == GAMEOVER) {
		gameScr();
		printf("%10s"," "); printf("Game is over: Draw\n\n");
	}
	else if(turn == WIN) {
		gameScr();
		printf("%10s"," "); printf("Player %c has won.\n\n",tempturn);
	}
	return EXIT_SUCCESS;		
}

void gameScr(void) {
	unsigned int i = 0;
	unsigned int j;
	clrscr();
	fflush(stdout);
	for(i = 0; i <= ROWS; i++) {
		j = 0;
		printf("%10s"," "); printf("+ -- + -- + -- +\n");
		if(i == 3) break;
		printf("%10s"," "); printf("| ");printf("%2c",TicTacToe[i][j++]);
		printf(" | ");printf("%2c",TicTacToe[i][j++]);
		printf(" | ");printf("%2c",TicTacToe[i][j++]);
		printf(" | ");
		printf("\n");
	}	
	printf("\n\n");
}

char nextStep(char player) {
	unsigned int row;
	unsigned int col;
	gameScr();
	printf("%10s"," ");printf("It's now turn for %c player\n\n", player);
	printf("%10s"," ");printf("Give the row number [1-3]: ");scanf("%u",&row);
	fflush(stdin);
	printf("%10s"," ");printf("Give the col number [1-3]: ");scanf("%u",&col);
	fflush(stdin);
	if((row > 3 || row < 1) || (col > 3 || col < 1)) return player;
	if(TicTacToe[row-1][col-1] == NOTHING) {
		TicTacToe[row-1][col-1] = player;
		if(checkWin(player) == WIN) return WIN; //! Return win, if win condition is approached.
		if(--feld == 0) return GAMEOVER; //! If all felds are full, game is draw.
		return (player == X) ? O : X; //! Change the turn of player, if all goes normal.
	} else {
		return player;
	}
}

unsigned int checkWin(char player) {

/*! There are 8 possibilities to win the game, given the same player has *
* either vertical, horizontal or diagonal moves without a break from the *
* opposite player.							 *
*/
	if(TicTacToe[0][0] == player &&
	     TicTacToe[0][1] == player &&
	     TicTacToe[0][2] == player ||
	     TicTacToe[1][0] == player &&
	     TicTacToe[1][1] == player &&
	     TicTacToe[1][2] == player ||
	     TicTacToe[2][0] == player &&
	     TicTacToe[2][1] == player &&
	     TicTacToe[2][2] == player ||
	     TicTacToe[0][0] == player &&
	     TicTacToe[1][0] == player &&
	     TicTacToe[2][0] == player ||
	     TicTacToe[0][1] == player &&
	     TicTacToe[1][1] == player &&
	     TicTacToe[2][1] == player ||
	     TicTacToe[0][2] == player &&
	     TicTacToe[1][2] == player &&
	     TicTacToe[2][2] == player ||
	     TicTacToe[0][0] == player &&
	     TicTacToe[1][1] == player &&
	     TicTacToe[2][2] == player ||
	     TicTacToe[0][2] == player &&
	     TicTacToe[1][1] == player &&
	     TicTacToe[2][0] == player) {
		return WIN;
  	}
	return CONTINUE;
}	
