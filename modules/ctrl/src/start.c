/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

		/* fflush(stdout) */
	#include <stdio.h>

		/* global variables */
	#include "data.h"
		/* game_ui() */
	#include "game_ui.h"
		/* init_board_...() */
	#include "init.h"
		/* print_...() & show_board_...() */
	#include "print.h"

	#include "start.h"


static	void	start		(void);
static	void	start_foo	(void);
static	void	start_custom	(void);
static	void	start_rand	(void);


void	start_switch	(void)
{
	switch (flag_s) {
	case START_FOO:
		start_foo();
		break;

	case START_NEW:
		start_rand();
		break;

	case START_LOAD:
		start_custom();
		break;
	}

	fflush(stdout);
}


static	void	start_foo	(void)
{
	/* foo */
}

static	void	start_custom	(void)
{
	init_board_custom();

	start();
}

static	void	start_rand	(void)
{
	/* clear */
	init_board_clr();

	start();
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
