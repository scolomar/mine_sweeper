/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/


/******************************************************************************
 ******* headers **************************************************************
 ******************************************************************************/
/*	*	*	*	*	*	*	*	*	*
 *	*	* Standard	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
		/* errno */
	#include <errno.h>
		/* fflush(stdout) */
	#include <stdio.h>

/*	*	*	*	*	*	*	*	*	*
 *	*	* Other	*	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
		/* game() */
	#include "game.h"
		/* game_iface() */
	#include "game_iface.h"
		/* menu_iface_board() */
	#include "menu_iface.h"
		/* player_iface() */
	#include "player_iface.h"

	#include "start.h"


/******************************************************************************
 ******* variables ************************************************************
 ******************************************************************************/
int	start_mode;


/******************************************************************************
 ******* static functions *****************************************************
 ******************************************************************************/
static	void	start_foo	(void);
static	void	start_rand	(void);
static	void	start_load	(void);


/******************************************************************************
 ******* main *****************************************************************
 ******************************************************************************/
void	start_switch	(void)
{
	switch (start_mode) {
	case START_FOO:
		start_foo();
		break;

	case START_RAND:
		start_rand();
		break;

	case START_LOAD:
		start_load();
		break;
	}
}


/******************************************************************************
 ******* static functions *****************************************************
 ******************************************************************************/
static	void	start_foo	(void)
{
	/* empty */
}

static	void	start_rand	(void)
{
	/* size & mines */
	int	level;
	int	rows;
	int	cols;
	int	mines;
	menu_iface_board(&level, &rows, &cols, &mines);

	/* user iface init */
	player_iface_init(rows, cols);

	/* start position */
	int	r;
	int	c;
	player_iface_start(&r, &c);

	/* game init */
	game_init_rand(rows, cols, mines, r, c);

	/* game iface init */
	game_iface_init_rand(level, r, c);

	/* game loop */
	game_iface();

	/* user iface cluanup */
	player_iface_cleanup();
	fflush(stdout);
}

static	void	start_load	(void)
{
	/* size & game init (sets errno) */
	int	rows;
	int	cols;
	game_init_load(&rows, &cols);

	/* player iface init */
	player_iface_init(rows, cols);

	if (!errno) {
		/* game iface init */
		game_iface_init_load();

		/* game loop */
		game_iface();
	}

	/* user iface cluanup */
	player_iface_cleanup();
	fflush(stdout);
}


/******************************************************************************
 ******* end of file **********************************************************
 ******************************************************************************/
