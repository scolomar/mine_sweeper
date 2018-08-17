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


static	void	show_char	(WINDOW *win, int row, int col, wchar_t ch);
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

void	show_board_end		(WINDOW *win)
{

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
	int	k;
	int	l;

	for (i = 0; i < board.rows; i++) {
		k =	1 + i;

		/* clear */
		for (j = 0; j < board.cols; j++) {
			l =	2 + 2 * j;
			wchar_t		ch;
			if (board.usr[i][j] == USR_CLEAR) {
				ch =	board_char(i, j);
				show_char(win, k, l, ch);
			}
		}
		/* hidden */
		for (j = 0; j < board.cols; j++) {
			l =	2 + 2 * j;
			wchar_t		ch;
			if (board.usr[i][j] != USR_CLEAR) {
				ch =	board_char(i, j);
				show_char(win, k, l, ch);
			}
		}
		/* kboom */
		for (j = 0; j < board.cols; j++) {
			l =	2 + 2 * j;
			wchar_t		ch;
			if (board.usr[i][j] == KBOOM) {
				ch =	board_char(i, j);
				show_char(win, k, l, ch);
			}
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

static	void	show_char	(WINDOW *win, int row, int col, wchar_t ch)
{
	int	pair;
	switch (ch) {
	case '1':
		pair =	PAIR_1;
		break;

	case '2':
		pair =	PAIR_2;
		break;

	case '3':
		pair =	PAIR_3;
		break;

	case '4':
		pair =	PAIR_4;
		break;

	case '5':
		pair =	PAIR_5;
		break;

	case '6':
		pair =	PAIR_6;
		break;

	case '7':
		pair =	PAIR_7;
		break;

	case '8':
		pair =	PAIR_8;
		break;

	case ' ':
		pair =	PAIR_BLANK;
		break;

	case '*':
	case 'v':
		pair =	PAIR_MINE;
		break;

	case '+':
	case '-':
		pair =	PAIR_HIDDEN;
		break;

	case 'f':
		pair =	PAIR_fail;
		break;

	case '?':
		pair =	PAIR_POSSIBLE;
		break;

	case 'F':
		pair =	PAIR_FAIL;
		break;

	case '!':
		pair =	PAIR_FLAG;
		break;

	case '#':
		pair =	PAIR_KBOOM;
		break;
	}



	if (color) {
		wattron(win, A_BOLD | COLOR_PAIR(pair));
	}
	mvwaddch(win, row, col - 1, ' ');
	mvwaddch(win, row, col, ch);
	mvwaddch(win, row, col + 1, ' ');
	if (color) {
		wattroff(win, A_BOLD | COLOR_PAIR(pair));
	}
	wrefresh(win);
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
