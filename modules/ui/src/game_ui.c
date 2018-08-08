/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

		/* WINDOW & wgetch() & KEY_... & ... */
	#include <ncurses.h>
		/* wchar_t */
	#include <wchar.h>

		/* ACT_... & GAME_PLAYING*/
	#include "data.h"
		/* game_action() & game_state() */
	#include "game.h"
		/* show_board() */
	#include "print.h"

	#include "game_ui.h"


/******************************************************************************
 ******| static |**************************************************************
 ******************************************************************************/
static	int	usr_input	(WINDOW *win);


/******************************************************************************
 ******| main |****************************************************************
 ******************************************************************************/
void	game_ui			(void)
{
	/* Dimensions */
	WINDOW		*win;
	const int	h =	board.rows + 2;
	const int	w =	2 * board.cols + 3;
	const int	r =	1;
	const int	c =	(80 - w) / 2;
	win =	newwin(h, w, r, c);

	/* Activate keypad, and don't echo input */
	keypad(win, true);
	noecho();

	/* Board position */
	int	pos_row;
	int	pos_col;
	pos_row =	0;
	pos_col =	0;
									DBG_PRINT(4, show_board, 0);


	/* Action */
	int	action;

	/* Game loop */
	int	state;
	do {
		show_board(win, pos_row, pos_col);
		action = usr_input(win);
		game_action(action, &pos_row, &pos_col);
		state = game_state();

	} while (state == GAME_PLAYING);
}


/******************************************************************************
 ******| static |**************************************************************
 ******************************************************************************/
static	int	usr_input		(WINDOW *win)
{
	wchar_t	ch;
	ch = wgetch(win);

	int	action;

	switch (ch) {
	case KEY_UP:
		action =	ACT_MOVE_UP;
		break;

	case KEY_DOWN:
		action =	ACT_MOVE_DOWN;
		break;

	case KEY_RIGHT:
		action =	ACT_MOVE_RIGHT;
		break;

	case KEY_LEFT:
		action =	ACT_MOVE_LEFT;
		break;

	case '\r':
		action =	ACT_DISCOVER;
		break;

	case ' ':
		action =	ACT_PLACE_FLAG;
		break;

	case KEY_BACKSPACE:
		action =	ACT_RM_FLAG;
		break;

	case 'q':
		action =	ACT_QUIT;
		break;
	}

	return	action;
}
