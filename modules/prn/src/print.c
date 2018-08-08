/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

	#include <ncurses.h>
	#include <stdio.h>
	#include <wchar.h>

		/* alx_ncur_prn_title() */
	#include "alx_ncur.h"

		/* board & macros */
	#include "data.h"

	#include "print.h"


static	wchar_t	board_char	(int row, int col);
static	void	show_board	(WINDOW *win);


void	show_board_cheat	(void)
{
/*
*/
}

void	show_board_play		(WINDOW *win, int pos_row, int pos_col)
{
	box(win, 0, 0);

	show_board(win);
	wmove(win, 1 + pos_row, 2 + 2 * pos_col);
	wrefresh(win);
}

void	show_board_end		(void)
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

	/* Box & title */
	box(win, 0, 0);
	if (board.state == GAME_OVER) {
		alx_ncur_prn_title(win, "GAME OVER");
	} else {
		alx_ncur_prn_title(win, "You win!");
	}

	/* Board */
	show_board(win);
	wmove(win, 0, 0);
	wrefresh(win);

	/* Wait for any key & exit */
	wgetch(win);
	alx_win_del(win);
}

void	print_time		(void)
{
	printf("Total time: %.3f;   ", tim_tot);
}

void	print_verbose		(int verbose, void *print_func, int arg)
{

	if (arg != -1) {
		if (flag_V >= verbose) {
			(*(void (*)(bool)) print_func)(arg);
		}
	} else {
		if (flag_V >= verbose) {
			(*(void (*)()) print_func)();
		}
	}
}


static	void	show_board	(WINDOW *win)
{
	int	i;
	int	j;

	for (i = 0; i < board.rows; i++) {
		for (j = 0; j < board.cols; j++) {
			const int	k =	1 + i;
			const int	l =	2 + 2 * j;
			wchar_t		ch;
			ch =	board_char(i, j);
			mvwaddch(win, k, l, ch);
		}
	}
	wrefresh(win);
}

static	wchar_t	board_char	(int row, int col)
{
	wchar_t	ch;

	switch (board.state) {
	case GAME_PLAYING:
		switch (board.usr[row][col]) {
		case USR_HIDDEN:
			ch =	'+';
			break;
		case USR_CLEAR:
			if (board.gnd[row][col] == MINE_NO) {
				ch =	' ';
			} else {
				ch =	'0' + board.gnd[row][col];
			}
			break;
		case USR_FLAG:
			ch =	'!';
			break;
		case USR_POSSIBLE:
			ch =	'?';
			break;
		}
		break;
	case GAME_WIN:
		switch (board.usr[row][col]) {
		case USR_HIDDEN:
			ch =	'v';
			break;
		case USR_CLEAR:
			if (board.gnd[row][col] == MINE_NO) {
				ch =	' ';
			} else {
				ch =	'0' + board.gnd[row][col];
			}
			break;
		case USR_FLAG:
			ch =	'!';
			break;
		case USR_POSSIBLE:
			ch =	'?';
			break;
		}
		break;
	case GAME_OVER:
		switch (board.usr[row][col]) {
		case KBOOM:
			ch =	'#';
			break;
		case USR_HIDDEN:
			if (board.gnd[row][col] >= MINE_YES) {
				ch =	'*';
			} else {
				ch =	'-';
			}
			break;
		case USR_CLEAR:
			if (board.gnd[row][col] == MINE_NO) {
				ch =	' ';
			} else {
				ch =	'0' + board.gnd[row][col];
			}
			break;
		case USR_FLAG:
			if (board.gnd[row][col] >= MINE_YES) {
				ch =	'!';
			} else {
				ch =	'F';
			}
			break;
		case USR_POSSIBLE:
			if (board.gnd[row][col] >= MINE_YES) {
				ch =	'*';
			} else {
				ch =	'f';
			}
			break;
		}
		break;
	}

	return	ch;
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
