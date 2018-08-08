/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

# ifndef			PRINT_H
	# define		PRINT_H

	#include <ncurses.h>

void	show_board	(WINDOW *win, int pos_row, int pos_col);
void	print_fail	(void);
void	print_victory	(void);
void	print_time	(void);
void	print_verbose	(int verbose, void *print_func, int arg);

# endif				/* print.h */
