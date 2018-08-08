/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

		/* WINDOW & wgetch() & KEY_... */
	#include <ncurses.h>
		/* bool */
	#include <stdbool.h>
		/* wchar_t */
	#include <wchar.h>

		/* macros */
	#include "data.h"
		/* show_board() */
	#include "print.h"

	#include "game.h"


static	int	usr_input		(WINDOW *win);
static	void	game_action		(int action, int *pos_row, int *pos_col);
static	void	game_discover		(int pos_row, int pos_col);
static	void	game_discover_recursive	(int pos_row, int pos_col);
static	void	game_flag		(int pos_row, int pos_col);
static	void	game_rmflag		(int pos_row, int pos_col);


void	game_main	(void)
{

	const int	total_safe_fields = board.rows * board.cols - board.mines;

									DBG_PRINT(4, show_board, 0);
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

	/* Action */
	int	action;

	/* Game loop */
	while (USR_CLEARED != KBOOM && USR_CLEARED < total_safe_fields) {
		show_board(win, pos_row, pos_col);
		action = usr_input(win);
		game_action(action, &pos_row, &pos_col);
	}
}


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

static	void	game_action		(int action, int *pos_row, int *pos_col)
{
	switch (action) {
	case ACT_MOVE_UP:
		if (*pos_row) {
			(*pos_row)--;
		} else {
			*pos_row = board.rows - 1;
		}
		break;

	case ACT_MOVE_DOWN:
		if (*pos_row != board.rows - 1) {
			(*pos_row)++;
		} else {
			*pos_row = 0;
		}
		break;

	case ACT_MOVE_RIGHT:
		if (*pos_col != board.cols - 1) {
			(*pos_col)++;
		} else {
			*pos_col = 0;
		}
		break;

	case ACT_MOVE_LEFT:
		if (*pos_col) {
			(*pos_col)--;
		} else {
			*pos_col = board.cols - 1;
		}
		break;

	case ACT_DISCOVER:
		game_discover(*pos_row, *pos_col);
		break;

	case ACT_PLACE_FLAG:
		game_flag(*pos_row, *pos_col);
		break;

	case ACT_RM_FLAG:
		game_rmflag(*pos_row, *pos_col);
		break;

	case ACT_QUIT:
		board.cleared =	KBOOM;
		break;
	}
}

static	void	game_discover		(int pos_row, int pos_col)
{
	if (board.gnd[pos_row][pos_col] >= MINE_YES) {
		board.usr[pos_row][pos_col] =	KBOOM;
		board.cleared =	KBOOM;

	} else if (board.usr[pos_row][pos_col] != USR_CLEAR) {
		board.usr[pos_row][pos_col] =	USR_CLEAR;
		board.cleared++;

		if (board.gnd[pos_row][pos_col] == MINE_NO) {
			game_discover_recursive(pos_row, pos_col);
		}
	}
}

static	void	game_discover_recursive	(int pos_row, int pos_col)
{
	int	i;
	int	j;

	for (i = pos_row-1; i < pos_row+2; i++) {
		for (j = pos_col-1; j < pos_col+2; j++) {
			if (i >= 0 && i < board.rows && j >= 0 && j < board.cols) {
				game_discover(i, j);
			}
		}
	}
}

static	void	game_flag		(int pos_row, int pos_col)
{
	if (board.usr[pos_row][pos_col] == USR_HIDDEN) {
		board.usr[pos_row][pos_col] =	USR_FLAG;
		board.flags++;
	}
}

static	void	game_rmflag		(int pos_row, int pos_col)
{
	if (board.usr[pos_row][pos_col] == USR_FLAG) {
		board.usr[pos_row][pos_col] =	USR_HIDDEN;
		board.flags--;
	}
}

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*--| END OF FILE |-----------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*--| END OF FILE |-----------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
