/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

		/* fflush(stdout) */
	#include <stdio.h>

		/* global variables */
	#include "data.h"
		/* game_ui() */
	#include "game_ui.h"
		/* init_...() */
	#include "init.h"
		/* print_...() & show_board_...() */
	#include "print.h"

	#include "start.h"


static	void	start		(void);
static	void	start_custom	(void);
static	void	start_rand	(void);


void	start_switch	(void)
{
	switch (flag_s) {
	case START_NEW:
		start_rand();
		break;
	case START_LOAD:
		start_custom();
		break;
	}

	fflush(stdout);
}


static	void	start_custom	(void)
{
	init_custom();
									print_verbose(3, show_board_cheat, -1);
	start();
									print_verbose(1, show_board_cheat, false);
									print_verbose(3, show_board_cheat, 0);
}

static	void	start_rand	(void)
{
	init_rand();
									print_verbose(2, show_board_cheat, -1);
	start();
									print_verbose(1, show_board_cheat, false);
									print_verbose(2, show_board_cheat, 0);
}


static	void	start		(void)
{
	game_ui();
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
