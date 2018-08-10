/*!
*	@autor Saroj Tripathi
*	reference: WIKIPEDIA
*	More Information : https://en.wikipedia.org/wiki/ANSI_escape_code
*/

#ifndef _STDIO_H
#include <stdio.h>
#endif

#define _HTC_ANSI_H


#define CUR_UP(VAL) printf("\033[%dA",VAL)
#define CUR_DOWN(VAL) printf("\033[%dB",VAL)
#define CUR_FORW(VAL) printf("\033[%dC",VAL)
#define CUR_BACK(VAL) printf("\033[%dD",VAL)
#define NXTLINE(VAL) printf("\033[%dE",VAL)
#define PREVLINE(VAL) printf("\033[%dF",VAL)
#define CUR_COL(VAL) printf("\033[%dG",VAL)
#define CUR_LOCATE(VAL1,VAL2) printf("\033[%d;%dH",VAL1,VAL2)

#define CLEAR_SCREEN(VAL) printf("\033[%dJ",VAL)
/*!
*	VAL = 0 -> Clear from cursor to end of screen (DEFAULT)
*	VAL = 1 -> Clear from cursor to beginnnig of screen
*	VAL = 2 -> Clear entire screen
*	VAL = 3 -> Clear entire screen and delete all lines 
*	saved in the scrollback buffer
*/

#define CLEAR_LINE(VAL) printf("\033[%dK",VAL)
/*!
*	VAL = 0 -> Clear from cursor to end of line (DEFAULT)
*	VAL = 1 -> Clear from cursor to beginnnig of line
*	VAL = 2 -> Clear entire line
*/

#define SCROLL_UP(VAL) printf("\033[%dS",VAL)
#define SCROLL_DOWN(VAL) printf("\033[%dT",VAL)
#define CUR_LOCATE1(VAL1,VAL2) printf("\033[%d;%df",VAL1,VAL2)
#define AUX_ON printf("\033[5i")
#define AUX_OFF printf("\033[4i")
#define CUR_REPORT printf("\033[6n")
#define CUR_SAVE printf("\033[s")
#define CUR_RESTORE printf("\033[u")

#define FORMAT(VAL) printf("\033[%dm",VAL)
#define SET_FBCOLOR(VAL1,VAL2) printf("\033[%d;%dm",VAL1,VAL2);
/*!
*	For more format and colors information,
*	click the Wikipedia link mentioned above.
*/
