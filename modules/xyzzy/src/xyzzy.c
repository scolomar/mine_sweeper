/******************************************************************************
 *	Copyright (C) 2018	Alejandro Colomar Andrés		      *
 ******************************************************************************/


/******************************************************************************
 ******* headers **************************************************************
 ******************************************************************************/
/*	*	*	*	*	*	*	*	*	*
 *	*	* Standard	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
	#include <stdbool.h>

/*	*	*	*	*	*	*	*	*	*
 *	*	* Other	*	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
		/* game_action() */
	#include "game_iface.h"

	#include "xyzzy.h"


/******************************************************************************
 ******* variables ************************************************************
 ******************************************************************************/
static	int	x;
static	bool	step_notflag;


/******************************************************************************
 ******* static functions *****************************************************
 ******************************************************************************/
void	xyzzy_step_all	(const struct Game_Iface_Out	*game_iface_out,
			struct Game_Iface_In		*game_iface_in);
void	xyzzy_flag_all	(const struct Game_Iface_Out	*game_iface_out,
			struct Game_Iface_In		*game_iface_in);


/******************************************************************************
 ******* main *****************************************************************
 ******************************************************************************/
void	xyzzy_init	(void)
{
	x		= 0;
	step_notflag	= true;
}

int	xyzzy_lin	(const struct Game_Iface_Out	*game_iface_out,
			struct Game_Iface_In		*game_iface_in)
{
	if (!x) {
		x	= 1;
	}

	if (step_notflag) {
		xyzzy_step_all(game_iface_out, game_iface_in);
	} else {
		xyzzy_flag_all(game_iface_out, game_iface_in);
		x--;
	}

	step_notflag	= !step_notflag;

	return	x;
}

int	xyzzy_p		(const struct Game_Iface_Out	*game_iface_out,
			struct Game_Iface_In		*game_iface_in)
{
	int	fields;
	fields	= game_iface_out->rows * game_iface_out->cols;

	if (!x) {
		x	= fields / 2;
	}

	xyzzy_lin(game_iface_out, game_iface_in);

	return	x;
}


/******************************************************************************
 ******* static functions *****************************************************
 ******************************************************************************/
void	xyzzy_step_all	(const struct Game_Iface_Out	*game_iface_out,
			struct Game_Iface_In		*game_iface_in)
{
	int	i;
	int	j;

	for (i = 0; i < game_iface_out->rows; i++) {
		for (j = 0; j < game_iface_out->cols; j++) {
			if (game_iface_out->usr[i][j] == GAME_IFACE_USR_CLEAR) {
				game_iface_in->act_game[i][j]	= GAME_IFACE_GAME_ACT_STEP;
			}
		}
	}
}

void	xyzzy_flag_all	(const struct Game_Iface_Out	*game_iface_out,
			struct Game_Iface_In		*game_iface_in)
{
	int	i;
	int	j;

	for (i = 0; i < game_iface_out->rows; i++) {
		for (j = 0; j < game_iface_out->cols; j++) {
			if (game_iface_out->usr[i][j] == GAME_IFACE_USR_CLEAR) {
				game_iface_in->act_game[i][j]	= GAME_IFACE_GAME_ACT_FLAG;
			}
		}
	}
}


/******************************************************************************
 ******* end of file **********************************************************
 ******************************************************************************/
