/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

		/* WINDOW & wgetch() & KEY_... & ... */
	#include <ncurses.h>
		/* clock_t & clock() & CLOCKS_PER_SEC */
	#include <time.h>
		/* wchar_t */
	#include <wchar.h>

		/* alx_..._curses() */
	#include "alx_ncur.h"

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
static	int	usr_input		(WINDOW *win);


/******************************************************************************
 ******| main |****************************************************************
 ******************************************************************************/
void	game_ui			(void)
{
	alx_resume_curses();

	/* Dimensions */
	WINDOW		*win;
	const int	h =	board.rows + 2;
	const int	w =	2 * board.cols + 3;
	const int	r =	0;
	const int	c =	10;
	win =	newwin(h, w, r, c);

	/* Activate keypad, and don't echo input */
	keypad(win, true);
	noecho();

	/* Board position */
	int	pos_row;
	int	pos_col;
	pos_row =	0;
	pos_col =	0;
									DBG_PRINT(4, show_board_cheat, 0);
	/* User action */
	int	action;

	/*
	 * If new map:
	 * First step
	 * game_action() detects first step and generates the map.
	 * This ensures first step is always safe.
	 */
	if (flag_s == START_NEW) {
		while (board.state == GAME_READY) {
			show_board_start(win, pos_row, pos_col);
			action = usr_input(win);
			game_action(action, &pos_row, &pos_col);
		}
	}

	/* Start timer */
	tim_ini =	time(NULL);
	game_update_time();

	/* Game loop */
	while (board.state == GAME_PLAYING) {
		show_board_play(win, pos_row, pos_col);
		action = usr_input(win);
		game_action(action, &pos_row, &pos_col);
		game_update_time();
	}

	/* Game end */
	show_board_end(win, pos_row, pos_col);

	/* Wait for any key & del win */
	wgetch(win);
	alx_win_del(win);

	alx_pause_curses();
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
		action =	ACT_STEP;
		break;

	case ' ':
		action =	ACT_FLAG;
		break;

	case 'x':
		action =	ACT_FLAG_POSSIBLE;
		break;

		/* ASCII 0x08 is BS */
	case KEY_BACKSPACE:
	case 0x08:
		action =	ACT_RM_FLAG;
		break;
/*
	case KEY_BREAK:
	case 'p':
		action =	ACT_PAUSE;
		break;
*/
	case 's':
		action =	ACT_SAVE;
		break;

	case 'q':
		action =	ACT_QUIT;
		break;
	}

	return	action;
}
