/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/


		/* clock_t & clock() & CLOCKS_PER_SEC */
	#include <time.h>
		/* wchar_t */
	#include <wchar.h>

		/* board & macros */
	#include "data.h"
		/* game_action() & game_state() & game_update_time() */
	#include "game.h"
		/* game_tui() */
	#include "game_clui.h"
		/* game_tui() */
	#include "game_tui.h"
		/* init_board_rand() */
	#include "init.h"
		/* save_game_file() */
	#include "save.h"
		/* xyzzy_...() */
	#include "xyzzy.h"

	#include "game_iface.h"


/******************************************************************************
 ******| static |**************************************************************
 ******************************************************************************/
static	void	game_iface_act		(int action, int *pos_row, int *pos_col);
static	void	game_iface_act_ready	(int action, int *pos_row, int *pos_col);
static	void	game_iface_act_playing	(int action, int *pos_row, int *pos_col);
static	void	game_iface_act_xyzzy	(int action, int *pos_row, int *pos_col);
static	void	game_iface_act_pause	(int action, int *pos_row, int *pos_col);
static	void	game_iface_act_end	(int action, int *pos_row, int *pos_col);

static	void	game_iface_first_step	(int pos_row, int pos_col);
static	void	game_iface_update_time	(void);
static	void	game_iface_pause	(void);
static	void	game_iface_quit		(void);

static	void	game_iface_xyzzy_on		(void);
static	void	game_iface_xyzzy_off		(void);

static	void	game_iface_visible_board	(void);
static	wchar_t	game_iface_visible_char		(int row, int col);


/******************************************************************************
 ******| main |****************************************************************
 ******************************************************************************/
void	game_iface	(void)
{
	/* Init interface */
	switch (flag_iface) {
	case IFACE_CLUI:
		/* Empty */
		break;

	case IFACE_TUI:
		game_tui_init();
		break;
	}

	/* Board position */
	int	pos_row;
	int	pos_col;
	pos_row =	0;
	pos_col =	0;

	/* User action */
	int	action;

	/* Game loop */
	while (board.state != GAME_QUIT) {
		game_iface_visible_board();
		switch (flag_iface) {
		case IFACE_CLUI:
			action	= game_clui(action, pos_row, pos_col);
			break;

		case IFACE_TUI:
			action	= game_tui(pos_row, pos_col);
			break;
		}

		game_iface_act(action, &pos_row, &pos_col);
		game_iface_update_time();
	}

	/* Cleanup interface */
	switch (flag_iface) {
	case IFACE_CLUI:
		/* Empty */
		break;

	case IFACE_TUI:
		game_tui_cleanup();
		break;
	}
}


/******************************************************************************
 ******| static |**************************************************************
 ******************************************************************************/
static	void	game_iface_act		(int action, int *pos_row, int *pos_col)
{
	switch (board.state) {
	case GAME_READY:
		game_iface_act_ready(action, pos_row, pos_col);
		break;

	case GAME_CHEATED:
	case GAME_PLAYING:
		game_iface_act_playing(action, pos_row, pos_col);
		break;

	case GAME_XYZZY:
		game_iface_act_xyzzy(action, pos_row, pos_col);
		break;

	case GAME_PAUSE:
		game_iface_act_pause(action, pos_row, pos_col);
		break;

	case GAME_WIN:
	case GAME_OVER:
		game_iface_act_end(action, pos_row, pos_col);
		break;
	}
}

static	void	game_iface_act_ready	(int action, int *pos_row, int *pos_col)
{
	switch (action) {
	case ACT_STEP:
		/* First step: gen map & set timer before stepping */
		if (!board.set) {
			game_iface_first_step(*pos_row, *pos_col);
		}
		game_action(action, pos_row, pos_col);
		break;

	case ACT_SAVE:
		save_game_file();
		break;
/*
	case ACT_XYZZY_ON:
		game_iface_xyzzy_on();
		break;
*/
	case ACT_QUIT:
		game_iface_quit();
		break;

	case ACT_FOO:
	case ACT_FLAG:
	case ACT_FLAG_POSSIBLE:
	case ACT_RM_FLAG:
	case ACT_PAUSE:
	case ACT_XYZZY_ON:
	case ACT_XYZZY_OFF:
	case ACT_XYZZY_LIN:
	case ACT_XYZZY_P:
	case ACT_XYZZY_NP:
		/* Empty */
		break;

	default:
		game_action(action, pos_row, pos_col);
		break;
	}
}

static	void	game_iface_act_playing	(int action, int *pos_row, int *pos_col)
{
	switch (action) {
	case ACT_PAUSE:
		game_iface_pause();
		break;

	case ACT_SAVE:
		save_game_file();
		break;

	case ACT_XYZZY_ON:
		game_iface_xyzzy_on();
		break;

	case ACT_QUIT:
		game_iface_quit();
		break;

	case ACT_FOO:
	case ACT_XYZZY_OFF:
	case ACT_XYZZY_LIN:
	case ACT_XYZZY_P:
	case ACT_XYZZY_NP:
		/* Empty */
		break;

	default:
		game_action(action, pos_row, pos_col);
		break;
	}
}

static	void	game_iface_act_xyzzy	(int action, int *pos_row, int *pos_col)
{
	switch (action) {
	case ACT_SAVE:
		save_game_file();
		break;

	case ACT_XYZZY_LIN:
		xyzzy_lin();
		break;

	case ACT_XYZZY_P:
		xyzzy_p();
		break;

	case ACT_XYZZY_OFF:
		game_iface_xyzzy_off();
		break;

	case ACT_QUIT:
		game_iface_quit();
		break;

	case ACT_FOO:
	case ACT_PAUSE:
	case ACT_XYZZY_ON:
	case ACT_XYZZY_NP:
		/* Empty */
		break;

	default:
		game_action(action, pos_row, pos_col);
		break;
	}
}

static	void	game_iface_act_pause	(int action, int *pos_row, int *pos_col)
{
	switch (action) {
	case ACT_PAUSE:
		game_iface_pause();
		break;

	case ACT_SAVE:
		save_game_file();
		break;

	case ACT_QUIT:
		game_iface_quit();
		break;
	}
}

static	void	game_iface_act_end	(int action, int *pos_row, int *pos_col)
{
	switch (action) {
	case ACT_QUIT:
		board.state =	GAME_QUIT;
		break;
	}
}


static	void	game_iface_first_step	(int pos_row, int pos_col)
{
	/* Generate map */
	init_board_rand(pos_row, pos_col);
	board.set	= true;

	/* Play */
	if (board.state == GAME_READY) {
		board.state = GAME_PLAYING;
	}

	/* Start timer */
	tim_ini		= time(NULL);
	game_iface_update_time();
}

static	void	game_iface_update_time	(void)
{
	time_t		tim_now;

	switch (board.state) {
	case GAME_PLAYING:
		tim_now =	time(NULL);
		board.time =	(int)(tim_now - tim_ini);
		break;

	case GAME_XYZZY:
		board.time =	CHEATED;
		board.clicks =	CHEATED;
		break;
	}
}

static	void	game_iface_pause		(void)
{
	time_t	tim_now;

	switch (board.state) {
	case GAME_PLAYING:
		tim_now		= time(NULL);
		board.time	= (int)(tim_now - tim_ini);
		board.state	= GAME_PAUSE;
		break;

	case GAME_PAUSE:
		tim_now		= time(NULL);
		tim_ini		= tim_now - (time_t)board.time;
		board.state	= GAME_PLAYING;
		break;
	}
}

static	void	game_iface_xyzzy_on		(void)
{
	board.state	= GAME_XYZZY;
}

static	void	game_iface_xyzzy_off		(void)
{
	board.state	= GAME_CHEATED;
}

static	void	game_iface_quit		(void)
{
	board.state	= GAME_QUIT;
}


static	void	game_iface_visible_board	(void)
{
	int	i;
	int	j;
	wchar_t	ch;

	for (i = 0; i < board.rows; i++) {
		for (j = 0; j < board.cols; j++) {
			ch =	game_iface_visible_char(i, j);
			board.visible[i][j] =	ch;
		}
	}
}

static	wchar_t	game_iface_visible_char		(int row, int col)
{
	wchar_t	ch;

	switch (board.state) {
	case GAME_READY:
		switch (board.usr[row][col]) {
		case USR_HIDDEN:
			ch =	'+';
			break;

		case USR_FLAG:
			ch =	'!';
			break;

		case USR_POSSIBLE:
			ch =	'?';
			break;
		}
		break;

	case GAME_CHEATED:
	case GAME_XYZZY:
	case GAME_PLAYING:
		switch (board.usr[row][col]) {
		case USR_HIDDEN:
			ch =	'+';
			break;
		case USR_CLEAR:
			if (board.gnd[row][col] == MINE_NO) {
				ch =	' ';
			} else {
				ch =	'0' + board.gnd[row][col];
			}
			break;
		case USR_FLAG:
			ch =	'!';
			break;
		case USR_POSSIBLE:
			ch =	'?';
			break;
		}
		break;

	case GAME_WIN:
		switch (board.usr[row][col]) {
		case USR_HIDDEN:
			ch =	'v';
			break;

		case USR_CLEAR:
			if (board.gnd[row][col] == MINE_NO) {
				ch =	' ';
			} else {
				ch =	'0' + board.gnd[row][col];
			}
			break;

		case USR_FLAG:
			ch =	'!';
			break;

		case USR_POSSIBLE:
			ch =	'?';
			break;
		}
		break;

	case GAME_OVER:
		switch (board.usr[row][col]) {
		case KBOOM:
			ch =	'#';
			break;

		case USR_HIDDEN:
			if (board.gnd[row][col] >= MINE_YES) {
				ch =	'*';
			} else {
				ch =	'-';
			}
			break;

		case USR_CLEAR:
			if (board.gnd[row][col] == MINE_NO) {
				ch =	' ';
			} else {
				ch =	'0' + board.gnd[row][col];
			}
			break;

		case USR_FLAG:
			if (board.gnd[row][col] >= MINE_YES) {
				ch =	'!';
			} else {
				ch =	'F';
			}
			break;

		case USR_POSSIBLE:
			if (board.gnd[row][col] >= MINE_YES) {
				ch =	'*';
			} else {
				ch =	'f';
			}
			break;
		}
		break;

	default:
		ch =	'0';
		break;
	}

	return	ch;
}
