/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/


/******************************************************************************
 ******* headers **************************************************************
 ******************************************************************************/
/*	*	*	*	*	*	*	*	*	*
 *	*	* Standard	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
	#include <stdbool.h>
		/* time_t & time() */
	#include <time.h>

/*	*	*	*	*	*	*	*	*	*
 *	*	* Other	*	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
		/* player_iface() */
	#include "player_iface.h"
		/* save_game_file() */
	#include "save.h"
		/* save_score() */
	#include "score.h"
		/* xyzzy_...() */
	#include "xyzzy.h"

		/* game_action() */
	#include "game.h"

	#include "game_iface.h"


/******************************************************************************
 ******* variables ************************************************************
 ******************************************************************************/
static	struct Game_Iface_Out	game_iface_out;
static	struct Game_Iface_In	game_iface_in;
static	struct Game_Iface_Score	game_iface_score;
static	time_t			tim_ini;


/******************************************************************************
 ******* static functions *****************************************************
 ******************************************************************************/
	/* Init */
static	void	game_iface_init_score	(int level);
static	void	game_iface_init_cheated	(void);
	/* Actions */
static	void	game_iface_act		(void);
static	void	game_iface_playing_act	(void);
static	void	game_iface_xyzzy_act	(void);
static	void	game_iface_cheated_act	(void);
static	void	game_iface_pause_act	(void);
static	void	game_iface_safe_act	(void);
static	void	game_iface_gameover_act	(void);
	/* Actions:  game */
static	void	game_iface_act_game	(void);
	/* Actions:  game_iface */
static	void	game_iface_pause	(void);
static	void	game_iface_unpause	(void);
static	void	game_iface_xyzzy_on	(void);
static	void	game_iface_xyzzy_off	(void);
static	void	game_iface_save_score	(void);
static	void	game_iface_quit		(void);
	/* Output */
static	void	game_iface_update_out	(void);
static	void	game_iface_update_board	(void);
static	void	game_iface_update_vis	(int r, int c);
static	void	game_iface_update_usr	(int r, int c);
	/* Score */
static	void	game_iface_update_score	(void);
	/* Prepare input */
static	void	game_iface_clean_in	(void);


/******************************************************************************
 ******* main *****************************************************************
 ******************************************************************************/
void	game_iface_init_rand	(int level, int pos_row, int pos_col)
{
	/* first step */
	game_action(GAME_ACT_STEP, pos_row, pos_col);

	game_iface_out.state	= GAME_IFACE_STATE_PLAYING;
	game_iface_init_score(level);

	game_iface_out.rows	= game_board.rows;
	game_iface_out.cols	= game_board.cols;
	game_iface_out.mines	= game_board.mines;
	game_iface_update_out();
	game_iface_update_score();
	game_iface_clean_in();
}

void	game_iface_init_load	(void)
{
	game_iface_init_cheated();

	game_iface_out.rows	= game_board.rows;
	game_iface_out.cols	= game_board.cols;
	game_iface_out.mines	= game_board.mines;
	game_iface_update_out();
	game_iface_clean_in();
}

void	game_iface		(void)
{
	while (game_iface_out.state != GAME_IFACE_STATE_QUIT) {
		game_iface_update_out();
		game_iface_update_score();
		game_iface_clean_in();

		player_iface(&game_iface_out, &game_iface_score, &game_iface_in);

		game_iface_act();
	}
}


/******************************************************************************
 ******* static functions *****************************************************
 ******************************************************************************/
/*	*	*	*	*	*	*	*	*	*
 *	*	* Init	*	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
static	void	game_iface_init_score	(int level)
{
	game_iface_score.level	= level;
	tim_ini			= time(NULL);
	game_iface_score.clicks	= 1;
}

static	void	game_iface_init_cheated	(void)
{
	game_iface_out.state	= GAME_IFACE_STATE_CHEATED;
	game_iface_score.level	= GAME_IFACE_LEVEL_CUSTOM;
	game_iface_score.time	= CHEATED;
	game_iface_score.clicks	= CHEATED;
}

/*	*	*	*	*	*	*	*	*	*
 *	*	* Actions	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
static	void	game_iface_act		(void)
{
	switch (game_iface_out.state) {
	case GAME_IFACE_STATE_PLAYING:
		game_iface_playing_act();
		break;

	case GAME_IFACE_STATE_CHEATED:
		game_iface_cheated_act();
		break;

	case GAME_IFACE_STATE_XYZZY:
		game_iface_xyzzy_act();
		break;

	case GAME_IFACE_STATE_PAUSE:
		game_iface_pause_act();
		break;

	case GAME_IFACE_STATE_SAFE:
		game_iface_safe_act();
		break;

	case GAME_IFACE_STATE_GAMEOVER:
		game_iface_gameover_act();
		break;
	}
}

static	void	game_iface_playing_act	(void)
{
	switch (game_iface_in.action) {
	case GAME_IFACE_ACT_PLAY:
		game_iface_act_game();
		break;

	case GAME_IFACE_ACT_PAUSE:
		game_iface_pause();
		break;

	case GAME_IFACE_ACT_XYZZY_ON:
		game_iface_xyzzy_on();
		break;

	case GAME_IFACE_ACT_SAVE:
		save_game_file(saved_path);
		break;

	case GAME_IFACE_ACT_QUIT:
		game_iface_quit();
		break;
	}
}

static	void	game_iface_xyzzy_act	(void)
{
	xyzzy_init();

	bool	wh;
	wh	= true;
	while (wh) {
		switch (game_iface_in.action) {
		case GAME_IFACE_ACT_PLAY:
			game_iface_act_game();
			wh	= false;
			break;

		case GAME_IFACE_ACT_XYZZY_OFF:
			game_iface_xyzzy_off();
			wh	= false;
			break;

		case GAME_IFACE_ACT_XYZZY_LIN:
			wh	= xyzzy_lin(&game_iface_out, &game_iface_in);
			game_iface_act_game();
			break;

		case GAME_IFACE_ACT_XYZZY_P:
			wh	= xyzzy_p(&game_iface_out, &game_iface_in);
			game_iface_act_game();
			game_iface_update_out();
			break;

		case GAME_IFACE_ACT_SAVE:
			save_game_file(saved_path);
			wh	= false;
			break;

		case GAME_IFACE_ACT_QUIT:
			game_iface_quit();
			wh	= false;
			break;

		default:
			wh	= false;
			break;
		}
	}
}

static	void	game_iface_cheated_act	(void)
{
	switch (game_iface_in.action) {
	case GAME_IFACE_ACT_PLAY:
		game_iface_act_game();
		break;

	case GAME_IFACE_ACT_XYZZY_ON:
		game_iface_xyzzy_on();
		break;

	case GAME_IFACE_ACT_SAVE:
		save_game_file(saved_path);
		break;

	case GAME_IFACE_ACT_QUIT:
		game_iface_quit();
		break;
	}
}

static	void	game_iface_pause_act	(void)
{
	switch (game_iface_in.action) {
	case GAME_IFACE_ACT_PAUSE:
		game_iface_unpause();
		break;

	case GAME_IFACE_ACT_XYZZY_ON:
		game_iface_xyzzy_on();
		break;

	case GAME_IFACE_ACT_SAVE:
		save_game_file(saved_path);
		break;

	case GAME_IFACE_ACT_QUIT:
		game_iface_quit();
		break;
	}
}

static	void	game_iface_safe_act	(void)
{
	switch (game_iface_in.action) {
	case GAME_IFACE_ACT_SAVE:
		game_iface_save_score();
		game_iface_quit();
		break;

	case GAME_IFACE_ACT_QUIT:
		game_iface_quit();
		break;
	}
}

static	void	game_iface_gameover_act	(void)
{
	switch (game_iface_in.action) {
	case GAME_IFACE_ACT_QUIT:
		game_iface_quit();
		break;
	}
}

/*	*	*	*	*	*	*	*	*	*
 *	*	* Actions:  game	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
static	void	game_iface_act_game	(void)
{
	int	i;
	int	j;

	for (i = 0; i < game_board.rows; i++) {
		for (j = 0; j < game_board.cols; j++) {
			if (game_iface_in.act_game[i][j]) {
				game_action(game_iface_in.act_game[i][j], i, j);
				game_iface_score.clicks++;
			}
		}
	}
}

/*	*	*	*	*	*	*	*	*	*
 *	*	* Actions:  game_iface	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
static	void	game_iface_pause	(void)
{
	time_t	tim_now;

	tim_now			= time(NULL);
	game_iface_score.time	= (int)(tim_now - tim_ini);
	game_iface_out.state	= GAME_IFACE_STATE_PAUSE;
}

static	void	game_iface_unpause	(void)
{
	time_t	tim_now;

	tim_now			= time(NULL);
	tim_ini			= tim_now - (time_t)game_iface_score.time;
	game_iface_out.state	= GAME_IFACE_STATE_PLAYING;
}

static	void	game_iface_xyzzy_on	(void)
{
	game_iface_out.state	= GAME_IFACE_STATE_XYZZY;
}

static	void	game_iface_xyzzy_off	(void)
{
	game_iface_out.state	= GAME_IFACE_STATE_CHEATED;
}

static	void	game_iface_save_score	(void)
{
	switch (game_iface_score.level) {
	case GAME_IFACE_LEVEL_BEGINNER:
		save_game_file(var_boards_beginner_path);
		save_score(&game_iface_score);
		break;

	case GAME_IFACE_LEVEL_INTERMEDIATE:
		save_game_file(var_boards_intermediate_path);
		save_score(&game_iface_score);
		break;

	case GAME_IFACE_LEVEL_EXPERT:
		save_game_file(var_boards_expert_path);
		save_score(&game_iface_score);
		break;

	case GAME_IFACE_LEVEL_CUSTOM:
		save_game_file(var_boards_custom_path);
		break;
	}
}

static	void	game_iface_quit		(void)
{
	game_iface_out.state	= GAME_IFACE_STATE_QUIT;
}

/*	*	*	*	*	*	*	*	*	*
 *	*	* Output	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
static	void	game_iface_update_out	(void)
{
	game_iface_out.flags	= game_board.flags;
	game_iface_out.clr	= game_board.clr;

	switch (game_board.state) {
	case GAME_STATE_SAFE:
		game_iface_out.state	= GAME_IFACE_STATE_SAFE;
		break;

	case GAME_STATE_GAMEOVER:
		game_iface_out.state	= GAME_IFACE_STATE_GAMEOVER;
		break;
	}

	game_iface_update_board();
}

static	void	game_iface_update_board	(void)
{
	int	i;
	int	j;

	for (i = 0; i < game_board.rows; i++) {
		for (j = 0; j < game_board.cols; j++) {
			game_iface_update_vis(i, j);
			game_iface_update_usr(i, j);
		}
	}
}

static	void	game_iface_update_vis	(int r, int c)
{
	int	field_vis;

	switch (game_iface_out.state) {
	case GAME_IFACE_STATE_SAFE:
	case GAME_IFACE_STATE_CHEATED:
	case GAME_IFACE_STATE_XYZZY:
	case GAME_IFACE_STATE_PLAYING:
		switch (game_board.usr[r][c]) {
		case GAME_USR_HIDDEN:
			field_vis	= GAME_IFACE_VIS_HIDDEN_FIELD;
			break;

		case GAME_USR_CLEAR:
			field_vis	= GAME_IFACE_VIS_0 + game_board.gnd[r][c];
			break;

		case GAME_USR_FLAG:
			field_vis	= GAME_IFACE_VIS_FLAG;
			break;

		case GAME_USR_POSSIBLE:
			field_vis	= GAME_IFACE_VIS_POSSIBLE;
			break;
		}
		break;

	case GAME_IFACE_STATE_GAMEOVER:
		switch (game_board.usr[r][c]) {
		case GAME_USR_KBOOM:
			field_vis	= GAME_IFACE_VIS_KBOOM;
			break;

		case GAME_USR_HIDDEN:
			if (game_board.gnd[r][c] >= GAME_MINE_YES) {
				field_vis	= GAME_IFACE_VIS_HIDDEN_MINE;
			} else {
				field_vis	= GAME_IFACE_VIS_HIDDEN_SAFE;
			}
			break;

		case GAME_USR_CLEAR:
			field_vis	= GAME_IFACE_VIS_0 + game_board.gnd[r][c];
			break;

		case GAME_USR_FLAG:
			if (game_board.gnd[r][c] >= GAME_MINE_YES) {
				field_vis	= GAME_IFACE_VIS_FLAG;
			} else {
				field_vis	= GAME_IFACE_VIS_FLAG_FALSE;
			}
			break;

		case GAME_USR_POSSIBLE:
			if (game_board.gnd[r][c] >= GAME_MINE_YES) {
				field_vis	= GAME_IFACE_VIS_POSSIBLE;
			} else {
				field_vis	= GAME_IFACE_VIS_POSSIBLE_FALSE;
			}
			break;
		}
		break;

	default:
		field_vis	= GAME_IFACE_VIS_HIDDEN_FIELD;
		break;
	}

	game_iface_out.visible[r][c]	= field_vis;
}

static	void	game_iface_update_usr	(int r, int c)
{
	int	field_usr;

	switch (game_board.usr[r][c]) {
	case GAME_USR_KBOOM:
		field_usr	= GAME_IFACE_USR_KBOOM;
		break;

	case GAME_USR_HIDDEN:
		field_usr	= GAME_IFACE_USR_HIDDEN;
		break;

	case GAME_USR_CLEAR:
		field_usr	= GAME_IFACE_USR_CLEAR;
		break;

	case GAME_USR_FLAG:
		field_usr	= GAME_IFACE_VIS_FLAG;
		break;

	case GAME_USR_POSSIBLE:
		field_usr	= GAME_IFACE_VIS_POSSIBLE;
		break;
	}

	game_iface_out.usr[r][c]	= field_usr;
}

/*	*	*	*	*	*	*	*	*	*
 *	*	* Score	*	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
static	void	game_iface_update_score	(void)
{
	time_t		tim_now;

	switch (game_iface_out.state) {
	case GAME_IFACE_STATE_PLAYING:
		tim_now			= time(NULL);
		game_iface_score.time	= (int)(tim_now - tim_ini);
		break;

	case GAME_IFACE_STATE_XYZZY:
	case GAME_IFACE_STATE_CHEATED:
		game_iface_score.level	= GAME_IFACE_LEVEL_CUSTOM;
		game_iface_score.time	= CHEATED;
		game_iface_score.clicks	= CHEATED;
		break;
	}
}

/*	*	*	*	*	*	*	*	*	*
 *	*	* Prepare input	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
static	void	game_iface_clean_in	(void)
{
	int	i;
	int	j;
	for (i = 0; i < game_board.rows; i++) {
		for (j = 0; j < game_board.cols; j++) {
			game_iface_in.act_game[i][j]	= GAME_IFACE_GAME_ACT_FOO;
		}
	}

	game_iface_in.action	= GAME_IFACE_ACT_FOO;
}


/******************************************************************************
 ******* end of file **********************************************************
 ******************************************************************************/
