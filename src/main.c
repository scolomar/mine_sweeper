/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/


/******************************************************************************
 ******* headers **************************************************************
 ******************************************************************************/
/*	*	*	*	*	*	*	*	*	*
 *	*	* Standard	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
		/* getchar() */
	#include <stdio.h>

/*	*	*	*	*	*	*	*	*	*
 *	*	* Other	*	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
	#include "alx_ncur.h"

		/* about_init() & print_cpright() */
	#include "about.h"
	#include "game.h"
	#include "menu_iface.h"
	#include "player_iface.h"
	#include "parser.h"
	#include "save.h"
	#include "start.h"


/******************************************************************************
 ******* static functions *****************************************************
 ******************************************************************************/
void	init_all	(void);
void	cleanup		(void);


/******************************************************************************
 ******* main *****************************************************************
 ******************************************************************************/
int	main	(int argc, char *argv[])
{
	init_all();
	
	/* Parse command line options */
	parser(argc, argv);

	/* Print copyright () and wait for any key to continue */
	print_cpright();
	getchar();

	/* Start () */
	start_switch();

	/* Menu () */
	menu_iface();

	cleanup();

	return	0;
}


/******************************************************************************
 ******* static functions *****************************************************
 ******************************************************************************/
void	init_all	(void)
{
	/* Init modules */
	alx_start_curses();
	menu_iface_init();
	alx_pause_curses();
	game_init();
	about_init();
	save_init();

	/* Modes */
	start_mode		= START_FOO;
	flag_exit		= false;
	menu_iface_mode		= MENU_IFACE_TUI;
	player_iface_mode	= PLAYER_IFACE_TUI;
}

void	cleanup		(void)
{
	/* End curses */
	alx_resume_curses();
	alx_end_curses();
}


/******************************************************************************
 ******* end of file **********************************************************
 ******************************************************************************/
