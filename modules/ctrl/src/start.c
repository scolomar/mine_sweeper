/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

		/* fflush(stdout) */
	#include <stdio.h>
		/* time() & CLOCKS_PER_SEC */
	#include <time.h>

		/* game_end() */
	#include "check.h"
		/* global variables */
	#include "data.h"
		/* game_ui() */
	#include "game_ui.h"
		/* init_...() */
	#include "init.h"
		/* print_...() */
	#include "print.h"

	#include "start.h"


static	void	start		(void);
static	void	start_custom	(void);
static	void	start_rand	(void);


void	start_switch	(void)
{
	switch (flag_s) {
	case 1:
		start_custom();
		break;
	case 2:
		start_rand();
		break;
	}

	fflush(stdout);
}


static	void	start_custom	(void)
{
	init_custom();
									print_verbose(3, show_board, -1);
	start();
									print_verbose(1, show_board, false);
									print_verbose(3, show_board, 0);
}

static	void	start_rand	(void)
{
	init_rand();
									print_verbose(2, show_board, -1);
	start();
									print_verbose(1, show_board, false);
									print_verbose(2, show_board, 0);
}


static	void	start		(void)
{
	double	tim_i;

	tim_0 =		clock();
	game_ui();
	tim_1 =		clock();

	tim_i =		((double) tim_1 - tim_0) / CLOCKS_PER_SEC;
	tim_tot +=	tim_i;

	game_end();
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
