/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

# ifndef			MSW_PRINT_H
	# define		MSW_PRINT_H

	#include <ncurses.h>

void	show_board	(WINDOW *win, int pos_row, int pos_col);
void	show_board_win	(void);
void	show_board_lost	(void);
void	print_time	(void);
void	print_verbose	(int verbose, void *print_func, int arg);

# endif				/* print.h */
