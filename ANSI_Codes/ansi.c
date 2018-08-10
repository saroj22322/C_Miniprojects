/*!
*	@autor Saroj Tripathi
*	Testing ANSI-Codes
*/

#ifndef _HTC_ANSI_H
#include "htc_ansi.c"
#endif

#ifndef EXIT_SUCCESS
#include <stdlib.h>
#endif

int main(int argc, char* argv[] ){
	CLEAR_SCREEN(2); //! Clear entire screen
	CUR_LOCATE(0,0); //! Set cursor position to top left (0,0);
	SET_FBCOLOR(97,100); //!Background changed to light Black and foreground to white
	FORMAT(3); //! Italic
	FORMAT(4); //! Underline
	CUR_UP(1); //! Cursor moved 1 line up
	CLEAR_LINE(1); //! Current line clear to beginnning of the line
	CUR_COL(2); //! Move the cursor by 2 column forward
	printf("Hello World!");
	NXTLINE(2); //! Goto the beginning of 2nd line
	CUR_SAVE; //! Save the current cursor position
	printf("This is not visible.");
	CLEAR_LINE(1); 
	CUR_RESTORE; //! Restore the saved cursor position
	CUR_COL(2);
	FORMAT(24); //! Clear underline effect
	FORMAT(23); //! Clear italic effect
	
	return EXIT_SUCCESS;
}

