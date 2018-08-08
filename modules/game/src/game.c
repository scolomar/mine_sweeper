/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

		/* macros */
	#include "data.h"

	#include "game.h"


static	void	game_discover		(int pos_row, int pos_col);
static	void	game_discover_recursive	(int pos_row, int pos_col);
static	void	game_flag		(int pos_row, int pos_col);
static	void	game_possible		(int pos_row, int pos_col);
static	void	game_rmflag		(int pos_row, int pos_col);


void	game_action		(int action, int *pos_row, int *pos_col)
{
	switch (action) {
	case ACT_MOVE_UP:
		if (*pos_row) {
			(*pos_row)--;
		} else {
			*pos_row = board.rows - 1;
		}
		break;

	case ACT_MOVE_DOWN:
		if (*pos_row != board.rows - 1) {
			(*pos_row)++;
		} else {
			*pos_row = 0;
		}
		break;

	case ACT_MOVE_RIGHT:
		if (*pos_col != board.cols - 1) {
			(*pos_col)++;
		} else {
			*pos_col = 0;
		}
		break;

	case ACT_MOVE_LEFT:
		if (*pos_col) {
			(*pos_col)--;
		} else {
			*pos_col = board.cols - 1;
		}
		break;

	case ACT_DISCOVER:
		game_discover(*pos_row, *pos_col);
		break;

	case ACT_PLACE_FLAG:
		game_flag(*pos_row, *pos_col);
		break;

	case ACT_PLACE_POSSIBLE:
		game_possible(*pos_row, *pos_col);
		break;

	case ACT_RM_FLAG:
		game_rmflag(*pos_row, *pos_col);
		break;

	case ACT_QUIT:
		board.state =	GAME_OVER;
		break;
	}
}


static	void	game_discover		(int pos_row, int pos_col)
{
	const int	total_safe_fields = board.rows * board.cols -
								board.mines;

	if (board.gnd[pos_row][pos_col] >= MINE_YES) {
		board.usr[pos_row][pos_col] =	KBOOM;
		board.state =	GAME_OVER;

	} else if (board.usr[pos_row][pos_col] != USR_CLEAR) {
		board.usr[pos_row][pos_col] =	USR_CLEAR;
		board.cleared++;

		if (board.cleared == total_safe_fields) {
			board.state =	GAME_WIN;
		} else if (board.gnd[pos_row][pos_col] == MINE_NO) {
			game_discover_recursive(pos_row, pos_col);
		}
	}
}

static	void	game_discover_recursive	(int pos_row, int pos_col)
{
	int	i;
	int	j;

	for (i = pos_row-1; i < pos_row+2; i++) {
		for (j = pos_col-1; j < pos_col+2; j++) {
			if (i >= 0 && i < board.rows && j >= 0 && j < board.cols) {
				game_discover(i, j);
			}
		}
	}
}

static	void	game_flag		(int pos_row, int pos_col)
{
	if (board.usr[pos_row][pos_col] == USR_HIDDEN) {
		board.usr[pos_row][pos_col] =	USR_FLAG;
		board.flags++;
	}
}

static	void	game_possible		(int pos_row, int pos_col)
{
	if (board.usr[pos_row][pos_col] == USR_HIDDEN) {
		board.usr[pos_row][pos_col] =	USR_POSSIBLE;
	}
}

static	void	game_rmflag		(int pos_row, int pos_col)
{
	if (board.usr[pos_row][pos_col] == USR_FLAG) {
		board.usr[pos_row][pos_col] =	USR_HIDDEN;
		board.flags--;
	} else if (board.usr[pos_row][pos_col] == USR_POSSIBLE) {
		board.usr[pos_row][pos_col] =	USR_HIDDEN;
	}
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
