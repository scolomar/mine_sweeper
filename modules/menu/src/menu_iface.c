/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/


/******************************************************************************
 ******* headers **************************************************************
 ******************************************************************************/
/*	*	*	*	*	*	*	*	*	*
 *	*	* Standard	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
	#include <math.h>
	#include <stdbool.h>

/*	*	*	*	*	*	*	*	*	*
 *	*	* Other	*	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
	#include "start.h"

//	#include "menu_clui.h"
	#include "menu_tui.h"

	#include "menu_iface.h"


/******************************************************************************
 ******* variables ************************************************************
 ******************************************************************************/
bool				flag_exit;
int				menu_iface_mode;
struct Menu_Iface_Variables	menu_iface_variables;


/******************************************************************************
 ******* main *****************************************************************
 ******************************************************************************/
void	menu_iface_init		(void)
{
	menu_iface_variables.rows	= 8;
	menu_iface_variables.cols	= 8;
	menu_iface_variables.p		= 0.16;
}

void	menu_iface_board	(int *rows, int *cols, int *mines)
{
	*rows	= menu_iface_variables.rows;
	*cols	= menu_iface_variables.cols;

	/* calc number of mines */
	*mines	= menu_iface_variables.p * (*rows) * (*cols);

	/* at least one safe field */
	if ((*mines) == (*rows) * (*cols)) {
		(*mines)--;
	}
}

void	menu_iface		(void)
{
	start_mode	= START_RAND;

	if (!flag_exit) {
		switch (menu_iface_mode) {
		case MENU_IFACE_FOO:
			break;

		case MENU_IFACE_CLUI:
			break;

		case MENU_IFACE_TUI:
			menu_tui();
			break;

		case MENU_IFACE_GUI:
			break;
		}
	}
}


/******************************************************************************
 ******* end of file **********************************************************
 ******************************************************************************/
