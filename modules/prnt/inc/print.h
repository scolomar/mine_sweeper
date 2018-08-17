/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

# ifndef			MSW_PRINT_H
	# define		MSW_PRINT_H

	#include <ncurses.h>

void	show_board_cheat	(void);
void	show_board_start	(WINDOW *win, int pos_row, int pos_col);
void	show_board_play		(WINDOW *win, int pos_row, int pos_col);
void	show_board_end		(WINDOW *win, int pos_row, int pos_col);
void	print_time		(void);
void	print_verbose		(int verbose, void *print_func, int arg);

# endif				/* print.h */
