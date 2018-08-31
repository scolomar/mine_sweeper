/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/


/******************************************************************************
 ******* headers **************************************************************
 ******************************************************************************/
/*	*	*	*	*	*	*	*	*	*
 *	*	* Standard	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
		/* INFINITY */
	#include <math.h>
		/* srand() */
	#include <stdlib.h>

/*	*	*	*	*	*	*	*	*	*
 *	*	* Other	*	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
	#include "alx_getnum.h"

	#include "about.h"
	#include "game_iface.h"
//	#include "save.h"
	#include "start.h"

	#include "menu_iface.h"

	#include "menu_clui.h"


/******************************************************************************
 ******* macros ***************************************************************
 ******************************************************************************/
	# define	ROWS_CLUI_MAX	(99)
#if (ROWS_CLUI_MAX > ROWS_MAX)
#	error	"rows max (clui)"
#endif

	# define	COLS_CLUI_MAX	(99)
#if (COLS_CLUI_MAX > COLS_MAX)
#	error	"cols max (clui)"
#endif

	# define	BUFF_SIZE	(1024)


/******************************************************************************
 ******* static functions *****************************************************
 ******************************************************************************/
static	void	menu_clui_rand		(void);
static	void	menu_clui_custom	(void);
static	void	menu_clui_load		(void);
static	void	menu_clui_start		(void);


/******************************************************************************
 ******* main *****************************************************************
 ******************************************************************************/
void	menu_clui	(void)
{
	char	buff [BUFF_SIZE];
	char	ch;

	ch	= 'n';
	printf("Read 'Disclaimer of warranty'? (yes/NO): ");
	fgets(buff, BUFF_SIZE, stdin);
	sscanf(buff, " %c", &ch);
	if (ch == 'y' || ch == 'Y') {
		puts (" >yes");
		print_disclaim();
	} else {
		puts (" >NO");
	}

	ch	= 'n';
	printf("Read 'License'? (yes/NO): ");
	fgets(buff, BUFF_SIZE, stdin);
	sscanf(buff, " %c", &ch);
	if (ch == 'y' || ch == 'Y') {
		puts (" >yes");
		print_license();
	} else {
		puts (" >NO");
	}
#if 0
	printf("Game interface? (NCURSES/text): ");
	scanf(" %c%*s ", &ch);
	if (ch == 't' || ch == 'T') {
		puts (" >text");
		// FIXME
	} else {
		puts (" >NCURSES");
		// FIXME
	}
#endif
	ch	= 'n';
	printf("New game or load game? (NEW/load): ");
	fgets(buff, BUFF_SIZE, stdin);
	sscanf(buff, " %c", &ch);
	if (ch == 'l' || ch == 'L') {
		puts (" >load");
		menu_clui_load();
	} else {
		puts (" >NEW");
		menu_clui_rand();
	}
}


/******************************************************************************
 ******* static functions *****************************************************
 ******************************************************************************/
static	void	menu_clui_rand		(void)
{
	/* Random */
	start_mode	= START_RAND;

	char	buff [BUFF_SIZE];
	char	ch;

	ch	= 'n';
	printf("Set seed for random generator? (yes/NO): ");
	fgets(buff, BUFF_SIZE, stdin);
	sscanf(buff, " %c", &ch);
	int	seed;
	if (ch == 'y' || ch == 'Y') {
		puts (" >yes");
		seed	= alx_getint(-INFINITY, 1, INFINITY, "Seed:", NULL);
		srand(seed);
	} else {
		puts (" >NO");
	}

	ch	= 'b';
	printf("Level? (BEGINNER/intermediate/expert/custom): ");
	fgets(buff, BUFF_SIZE, stdin);
	sscanf(buff, " %c", &ch);
	if (ch == 'i' || ch == 'I') {
		puts (" >intermediate");
		menu_iface_variables.level	= GAME_IFACE_LEVEL_INTERMEDIATE;
		menu_clui_start();
	} else if (ch == 'e' || ch == 'E') {
		puts (" >expert");
		menu_iface_variables.level	= GAME_IFACE_LEVEL_EXPERT;
		menu_clui_start();
	} else if (ch == 'c' || ch == 'C') {
		puts (" >custom");
		menu_iface_variables.level	= GAME_IFACE_LEVEL_CUSTOM;
		menu_clui_custom();
	} else {
		puts (" >BEGINNER");
		menu_iface_variables.level	= GAME_IFACE_LEVEL_BEGINNER;
		menu_clui_start();
	}
}

static	void	menu_clui_custom	(void)
{
	/* Random */
	start_mode	= START_RAND;

	menu_iface_variables.rows	= alx_getint(2, menu_iface_variables.rows, ROWS_CLUI_MAX, "Rows:", NULL);
	menu_iface_variables.cols	= alx_getint(2, menu_iface_variables.cols, COLS_CLUI_MAX, "Columns:", NULL);
	menu_iface_variables.p		= alx_getdbl(0, menu_iface_variables.p, 1, "Proportion:", NULL);

	menu_clui_start();
}

static	void	menu_clui_load		(void)
{
	/* Load */
	start_mode	= START_LOAD;
#if 0
	/* File name */ // FIXME
	alx_w_getfname(USER_SAVED_DIR, saved_name, "File name:", saved_name, NULL);
#endif
	menu_clui_start();
}

static	void	menu_clui_start		(void)
{
	puts(" >>START:");
	start_switch();

	char	buff [BUFF_SIZE];
	char	ch;

	ch	= 'm';
	printf("Play again? (MENU/play/exit): ");
	fgets(buff, BUFF_SIZE, stdin);
	sscanf(buff, " %c", &ch);
	if (ch == 'p' || ch == 'P') {
		puts (" >play");
		menu_clui_start();
	} else if (ch == 'e' || ch == 'E') {
		puts (" >exit!");
	} else {
		puts (" >MENU");
		menu_clui();
	}
}


/******************************************************************************
 ******* end of file **********************************************************
 ******************************************************************************/
