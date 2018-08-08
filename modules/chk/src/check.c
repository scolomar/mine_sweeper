/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

		/* board & GAME_OVER*/
	#include "data.h"
		/* print_t...() */
	#include "print.h"

	#include "check.h"


void	game_end		(void)
{
	if (board.state == GAME_OVER) {
		show_board_lost();
	} else {
		show_board_win();
	}
}
