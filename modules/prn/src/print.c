/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

	#include <ncurses.h>
	#include <stdio.h>

		/* alx_ncur_prn_title() */
	#include "alx_ncur.h"

		/* board & macros */
	#include "data.h"

	#include "print.h"


void	show_board	(WINDOW *win, int pos_row, int pos_col)
{
	int	i;
	int	j;

	box(win, 0, 0);

	for (i = 0; i < board.rows; i++) {
		for (j = 0; j < board.cols; j++) {
			const int	k =	1 + i;
			const int	l =	2 + 2 * j;

			switch (board.usr[i][j]) {
			case USR_HIDDEN:
				mvwaddstr(win, k, l, "+");
				break;
			case USR_CLEAR:
				if (board.gnd[i][j] == MINE_NO) {
					mvwaddstr(win, k, l, " ");
				} else {
					mvwprintw(win, k, l, "%i", board.gnd[i][j]);
				}
				break;
			case USR_FLAG:
				mvwaddstr(win, k, l, "!");
				break;
			}
		}
	}

	wmove(win, 1 + pos_row, 2 + 2 * pos_col);
	wrefresh(win);
}

void	show_board_win	(void)
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
	alx_ncur_prn_title(win, "You win!");

	/* Board */
	int	i;
	int	j;
	for (i = 0; i < board.rows; i++) {
		for (j = 0; j < board.cols; j++) {
			const int	k =	1 + i;
			const int	l =	2 + 2 * j;

			switch (board.usr[i][j]) {
			case USR_HIDDEN:
				mvwaddstr(win, k, l, "m");
				break;
			case USR_CLEAR:
				if (board.gnd[i][j] == MINE_NO) {
					mvwaddstr(win, k, l, " ");
				} else {
					mvwprintw(win, k, l, "%i", board.gnd[i][j]);
				}
				break;
			case USR_FLAG:
				mvwaddstr(win, k, l, "!");
				break;
			}
		}
	}

	wrefresh(win);
}

void	show_board_lost	(void)
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
	alx_ncur_prn_title(win, "K-Boom!");

	/* Board */
	int	i;
	int	j;
	for (i = 0; i < board.rows; i++) {
		for (j = 0; j < board.cols; j++) {
			const int	k =	1 + i;
			const int	l =	2 + 2 * j;

			switch (board.usr[i][j]) {
			case USR_HIDDEN:
				mvwaddstr(win, k, l, "M");
				break;
			case USR_CLEAR:
				if (board.gnd[i][j] == MINE_NO) {
					mvwaddstr(win, k, l, " ");
				} else {
					mvwprintw(win, k, l, "%i", board.gnd[i][j]);
				}
				break;
			case USR_FLAG:
				mvwaddstr(win, k, l, "!");
				break;
			}
		}
	}

	wrefresh(win);
}

void	print_fail	(void)
{
	printf("Fail!\n");
}

void	print_victory	(void)
{
	printf("Victory!\n");
}


void	print_time	(void)
{
	printf("Total time: %.3f;   ", tim_tot);
}

void	print_verbose	(int verbose, void *print_func, int arg)
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
