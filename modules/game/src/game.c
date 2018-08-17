/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

		/* macros */
	#include "data.h"
		/* init_board_rand() */
	#include "init.h"
		/* save_game_file() */
	#include "save.h"

	#include "game.h"


static	void	game_step		(int pos_row, int pos_col);
static	void	game_discover		(int pos_row, int pos_col);
static	void	game_discover_recursive	(int pos_row, int pos_col);
static	void	game_big_step		(int pos_row, int pos_col);
static	int	game_count_flags	(int pos_row, int pos_col);
static	void	game_step_recursive	(int pos_row, int pos_col);
static	void	game_flag		(int pos_row, int pos_col);
static	void	game_possible		(int pos_row, int pos_col);
static	void	game_rmflag		(int pos_row, int pos_col);
static	void	game_all_flags		(int pos_row, int pos_col);
static	int	game_count_nclear	(int pos_row, int pos_col);
static	void	game_flag_recursive	(int pos_row, int pos_col);


void	game_action		(int action, int *pos_row, int *pos_col)
{
	switch (action) {
	case ACT_FOO:
		break;

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

	case ACT_STEP:
		switch (board.state) {
		case GAME_READY:
			/* First step */
			init_board_rand(*pos_row, *pos_col);
			board.state = GAME_PLAYING;
			game_step(*pos_row, *pos_col);
			break;

		case GAME_PLAYING:
			game_step(*pos_row, *pos_col);
			break;
		}
		board.clicks++;
		break;

	case ACT_FLAG:
		game_flag(*pos_row, *pos_col);
		board.clicks++;
		break;

	case ACT_FLAG_POSSIBLE:
		game_possible(*pos_row, *pos_col);
		board.clicks++;
		break;

	case ACT_RM_FLAG:
		game_rmflag(*pos_row, *pos_col);
		board.clicks++;
		break;

	case ACT_SAVE:
		save_game_file();
		break;

	case ACT_QUIT:
		board.state =	GAME_OVER;
		break;
	}
}

void	game_update_time	(void)
{
	time_t		tim_now;
	tim_now =	time(NULL);
	board.time =	(int)(tim_now - tim_ini);
}


static	void	game_step		(int pos_row, int pos_col)
{
	switch (board.usr[pos_row][pos_col]) {
	case USR_HIDDEN:
	case USR_POSSIBLE:
		game_discover(pos_row, pos_col);
		break;

	case USR_CLEAR:
		game_big_step(pos_row, pos_col);
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

static	void	game_big_step		(int pos_row, int pos_col)
{
	int	cnt;
	cnt =	game_count_flags(pos_row, pos_col);

	if (cnt && (board.gnd[pos_row][pos_col] == cnt)) {
		game_step_recursive(pos_row, pos_col);
	}
}

static	int	game_count_flags	(int pos_row, int pos_col)
{
	int	cnt;
	int	i;
	int	j;

	cnt =	0;
	for (i = pos_row-1; i < pos_row+2; i++) {
		for (j = pos_col-1; j < pos_col+2; j++) {
			if (i >= 0 && i < board.rows && j >= 0 && j < board.cols) {
				if (board.usr[i][j] == USR_FLAG) {
					cnt++;
				}
			}
		}
	}

	return	cnt;
}

static	void	game_step_recursive	(int pos_row, int pos_col)
{
	int	i;
	int	j;

	for (i = pos_row-1; i < pos_row+2; i++) {
		for (j = pos_col-1; j < pos_col+2; j++) {
			if (i >= 0 && i < board.rows && j >= 0 && j < board.cols) {
				switch (board.usr[i][j]) {
				case USR_HIDDEN:
				case USR_POSSIBLE:
					game_discover(i, j);
					break;
				}
			}
		}
	}
}

static	void	game_flag		(int pos_row, int pos_col)
{
	switch (board.usr[pos_row][pos_col]) {
	case USR_HIDDEN:
		board.usr[pos_row][pos_col] =	USR_FLAG;
		board.flags++;
		break;

	case USR_FLAG:
		board.usr[pos_row][pos_col] =	USR_POSSIBLE;
		board.flags--;
		break;

	case USR_POSSIBLE:
		game_rmflag(pos_row, pos_col);
		break;

	case USR_CLEAR:
		game_all_flags(pos_row, pos_col);
		break;
	}
}

static	void	game_possible		(int pos_row, int pos_col)
{
	switch (board.usr[pos_row][pos_col]) {
	case USR_HIDDEN:
		board.usr[pos_row][pos_col] =	USR_POSSIBLE;
		break;

	case USR_POSSIBLE:
		game_rmflag(pos_row, pos_col);
		break;
	}
}

static	void	game_rmflag		(int pos_row, int pos_col)
{
	switch (board.usr[pos_row][pos_col]) {
	case USR_FLAG:
		board.usr[pos_row][pos_col] =	USR_HIDDEN;
		board.flags--;
		break;

	case USR_POSSIBLE:
		board.usr[pos_row][pos_col] =	USR_HIDDEN;
		break;
	}
}

static	void	game_all_flags		(int pos_row, int pos_col)
{
	int	cnt;
	cnt =	game_count_nclear(pos_row, pos_col);

	if (cnt && (board.gnd[pos_row][pos_col] == cnt)) {
		game_flag_recursive(pos_row, pos_col);
	}
}

static	int	game_count_nclear	(int pos_row, int pos_col)
{
	int	cnt;
	int	i;
	int	j;

	cnt =	0;
	for (i = pos_row-1; i < pos_row+2; i++) {
		for (j = pos_col-1; j < pos_col+2; j++) {
			if (i >= 0 && i < board.rows && j >= 0 && j < board.cols) {
				if (board.usr[i][j] != USR_CLEAR) {
					cnt++;
				}
			}
		}
	}

	return	cnt;
}

static	void	game_flag_recursive	(int pos_row, int pos_col)
{
	int	i;
	int	j;

	for (i = pos_row-1; i < pos_row+2; i++) {
		for (j = pos_col-1; j < pos_col+2; j++) {
			if (i >= 0 && i < board.rows && j >= 0 && j < board.cols) {
				switch (board.usr[i][j]) {
				case USR_HIDDEN:
				case USR_POSSIBLE:
					board.usr[i][j] =	USR_FLAG;
					board.flags++;
					break;
				}
			}
		}
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
