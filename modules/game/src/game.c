/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/


/******************************************************************************
 ******* headers **************************************************************
 ******************************************************************************/
/*	*	*	*	*	*	*	*	*	*
 *	*	* Standard	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
		/* rand() */
	#include <stdlib.h>
		/* time_t & clock() & time() */
	#include <time.h>
		/* getpid() */
	#include <unistd.h>

/*	*	*	*	*	*	*	*	*	*
 *	*	* Other	*	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
		/* seedf() */
	#include "alx_seed.h"

	#include "save.h"

	#include "game.h"


/******************************************************************************
 ******* variables ************************************************************
 ******************************************************************************/
struct Game_Board	game_board;


/******************************************************************************
 ******* static functions *****************************************************
 ******************************************************************************/
	/* Init */
static	void	game_init_clr		(void);
static	void	game_init_mines		(int pos_row, int pos_col);
static	void	game_init_adjnums	(void);
	/* Step */
static	void	game_step		(int r, int c);
static	void	game_first_step		(int r, int c);
static	void	game_discover		(int r, int c);
static	void	game_discover_recursive	(int r, int c);
static	void	game_big_step		(int r, int c);
static	int	game_count_flags	(int r, int c);
static	void	game_step_recursive	(int r, int c);
	/* Flag */
static	void	game_flag		(int r, int c);
static	void	game_possible		(int r, int c);
static	void	game_rmflag		(int r, int c);
static	void	game_all_flags		(int r, int c);
static	int	game_count_nclear	(int r, int c);
static	void	game_flag_recursive	(int r, int c);


/******************************************************************************
 ******* main *****************************************************************
 ******************************************************************************/
void	game_init		(void)
{
	int	seed;
	seed	= seedf(clock(), time(NULL), getpid());
	srand(seed);
}

void	game_init_rand		(int rows, int cols, int mines,
				int pos_row, int pos_col)
{
	/* size & mines */
	game_board.rows		= rows;
	game_board.cols		= cols;
	game_board.mines	= mines;

	/* clear */
	game_init_clr();

	/* place mines */
	game_init_mines(pos_row, pos_col);

	/* calc adjacency numbers */
	game_init_adjnums();
}

void	game_init_load		(int *rows, int *cols)
{
	load_game_file();

	game_board.state	= GAME_STATE_PLAYING;

	*rows	= game_board.rows;
	*cols	= game_board.cols;
}

void	game_action		(int action, int row, int col)
{
	switch (action) {
	case GAME_ACT_STEP:
		game_step(row, col);
		break;

	case GAME_ACT_FLAG:
		game_flag(row, col);
		break;

	case GAME_ACT_FLAG_POSSIBLE:
		game_possible(row, col);
		break;

	case GAME_ACT_RM_FLAG:
		game_rmflag(row, col);
		break;
	}
}


/******************************************************************************
 ******* static functions *****************************************************
 ******************************************************************************/
/*	*	*	*	*	*	*	*	*	*
 *	*	* Init	*	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
static	void	game_init_clr		(void)
{
	int	i;
	int	j;
	for (i = 0; i < game_board.rows; i++) {
		for (j = 0; j < game_board.cols; j++) {
			game_board.gnd[i][j]	= GAME_MINE_NO;
			game_board.usr[i][j]	= GAME_USR_HIDDEN;
		}
	}
	game_board.flags	= 0;
	game_board.clr		= 0;
	game_board.state	= GAME_STATE_PLAYING;
}

static	void	game_init_mines		(int pos_row, int pos_col)
{
	/* place mines */
	int	i;
	int	r;
	int	c;
	i	= 0;
	while (i < game_board.mines) {
		r	= (rand() % game_board.rows);
		c	= (rand() % game_board.cols);

		if (game_board.gnd[r][c] == GAME_MINE_NO) {
			/* first step is safe */
			if (!((r == pos_row) && (c == pos_col))) {
				game_board.gnd[r][c]	= GAME_MINE_YES;
				i++;
			}
		}
	}
}

static	void	game_init_adjnums	(void)
{
	int	r;
	int	c;
	int	i;
	int	j;
	for (r = 0; r < game_board.rows; r++) {
	for (c = 0; c < game_board.cols; c++) {
		if (game_board.gnd[r][c] >= GAME_MINE_YES) {
			for (i = r-1; i < r+2; i++) {
			for (j = c-1; j < c+2; j++) {
				if (i >= 0 && i < game_board.rows) {
				if (j >= 0 && j < game_board.cols) {
					game_board.gnd[i][j]++;
				}
				}
			}
			}
		}
	}
	}
}

/*	*	*	*	*	*	*	*	*	*
 *	*	* Step	*	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
static	void	game_step		(int r, int c)
{
	switch (game_board.usr[r][c]) {
	case GAME_USR_HIDDEN:
	case GAME_USR_POSSIBLE:
		game_discover(r, c);
		break;

	case GAME_USR_CLEAR:
		game_big_step(r, c);
		break;
	}
}

static	void	game_discover		(int r, int c)
{
	int	safe_fields;
	safe_fields	= (game_board.rows * game_board.cols) - game_board.mines;

	if (game_board.gnd[r][c] >= GAME_MINE_YES) {
		game_board.usr[r][c]	= GAME_USR_KBOOM;
		game_board.state	= GAME_STATE_GAMEOVER;

	} else if (game_board.usr[r][c] != GAME_USR_CLEAR) {
		game_board.usr[r][c]	= GAME_USR_CLEAR;
		game_board.clr++;

		if (game_board.clr == safe_fields) {
			game_board.state	= GAME_STATE_SAFE;

		} else if (game_board.gnd[r][c] == GAME_MINE_NO) {
			game_discover_recursive(r, c);
		}
	}
}

static	void	game_discover_recursive	(int r, int c)
{
	int	i;
	int	j;

	for (i = r - 1; i < r + 2; i++) {
		for (j = c - 1; j < c + 2; j++) {
			if (i >= 0 && i < game_board.rows &&
						j >= 0 && j < game_board.cols) {
				game_discover(i, j);
			}
		}
	}
}

static	void	game_big_step		(int r, int c)
{
	int	cnt;
	cnt	= game_count_flags(r, c);

	if (cnt && (game_board.gnd[r][c] == cnt)) {
		game_step_recursive(r, c);
	}
}

static	int	game_count_flags	(int r, int c)
{
	int	cnt;
	int	i;
	int	j;

	cnt =	0;
	for (i = r - 1; i < r + 2; i++) {
		for (j = c - 1; j < c + 2; j++) {
			if (i >= 0 && i < game_board.rows &&
						j >= 0 && j < game_board.cols) {
				if (game_board.usr[i][j] == GAME_USR_FLAG) {
					cnt++;
				}
			}
		}
	}

	return	cnt;
}

static	void	game_step_recursive	(int r, int c)
{
	int	i;
	int	j;

	for (i = r - 1; i < r + 2; i++) {
		for (j = c - 1; j < c + 2; j++) {
			if (i >= 0 && i < game_board.rows &&
						j >= 0 && j < game_board.cols) {
				switch (game_board.usr[i][j]) {
				case GAME_USR_HIDDEN:
				case GAME_USR_POSSIBLE:
					game_discover(i, j);
					break;
				}
			}
		}
	}
}

/*	*	*	*	*	*	*	*	*	*
 *	*	* Flag	*	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
static	void	game_flag		(int r, int c)
{
	switch (game_board.usr[r][c]) {
	case GAME_USR_HIDDEN:
		game_board.usr[r][c]	= GAME_USR_FLAG;
		game_board.flags++;
		break;

	case GAME_USR_FLAG:
		game_board.usr[r][c]	= GAME_USR_POSSIBLE;
		game_board.flags--;
		break;

	case GAME_USR_POSSIBLE:
		game_rmflag(r, c);
		break;

	case GAME_USR_CLEAR:
		game_all_flags(r, c);
		break;
	}
}

static	void	game_possible		(int r, int c)
{
	switch (game_board.usr[r][c]) {
	case GAME_USR_HIDDEN:
		game_board.usr[r][c]	= GAME_USR_POSSIBLE;
		break;

	case GAME_USR_POSSIBLE:
		game_rmflag(r, c);
		break;
	}
}

static	void	game_rmflag		(int r, int c)
{
	switch (game_board.usr[r][c]) {
	case GAME_USR_FLAG:
		game_board.usr[r][c]	= GAME_USR_HIDDEN;
		game_board.flags--;
		break;

	case GAME_USR_POSSIBLE:
		game_board.usr[r][c]	= GAME_USR_HIDDEN;
		break;
	}
}

static	void	game_all_flags		(int r, int c)
{
	int	cnt;
	cnt =	game_count_nclear(r, c);

	if (cnt && (game_board.gnd[r][c] == cnt)) {
		game_flag_recursive(r, c);
	}
}

static	int	game_count_nclear	(int r, int c)
{
	int	cnt;
	int	i;
	int	j;

	cnt =	0;
	for (i = r - 1; i < r + 2; i++) {
		for (j = c - 1; j < c + 2; j++) {
			if (i >= 0 && i < game_board.rows &&
						j >= 0 && j < game_board.cols) {
				if (game_board.usr[i][j] != GAME_USR_CLEAR) {
					cnt++;
				}
			}
		}
	}

	return	cnt;
}

static	void	game_flag_recursive	(int r, int c)
{
	int	i;
	int	j;

	for (i = r - 1; i < r + 2; i++) {
		for (j = c - 1; j < c + 2; j++) {
			if (i >= 0 && i < game_board.rows &&
						j >= 0 && j < game_board.cols) {
				switch (game_board.usr[i][j]) {
				case GAME_USR_HIDDEN:
				case GAME_USR_POSSIBLE:
					game_board.usr[i][j]	= GAME_USR_FLAG;
					game_board.flags++;
					break;
				}
			}
		}
	}
}


/******************************************************************************
 ******* end of file **********************************************************
 ******************************************************************************/
