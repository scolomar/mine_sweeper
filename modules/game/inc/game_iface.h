/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/


/******************************************************************************
 ******* include guard ********************************************************
 ******************************************************************************/
# ifndef		MSW_GAME_IFACE_H
	# define	MSW_GAME_IFACE_H


/******************************************************************************
 ******* macros ***************************************************************
 ******************************************************************************/
	# define	ROWS_MAX	(22)
	# define	COLS_MAX	(33)
	# define	CHEATED		(-1)


/******************************************************************************
 ******* enums ****************************************************************
 ******************************************************************************/
	enum	Game_Iface_Visible_Board {
		GAME_IFACE_VIS_KBOOM,
		GAME_IFACE_VIS_HIDDEN_FIELD,
		GAME_IFACE_VIS_HIDDEN_MINE,
		GAME_IFACE_VIS_HIDDEN_SAFE,
		GAME_IFACE_VIS_SAFE_MINE,
		GAME_IFACE_VIS_0,
		GAME_IFACE_VIS_1,
		GAME_IFACE_VIS_2,
		GAME_IFACE_VIS_3,
		GAME_IFACE_VIS_4,
		GAME_IFACE_VIS_5,
		GAME_IFACE_VIS_6,
		GAME_IFACE_VIS_7,
		GAME_IFACE_VIS_8,
		GAME_IFACE_VIS_FLAG,
		GAME_IFACE_VIS_FLAG_FALSE,
		GAME_IFACE_VIS_POSSIBLE,
		GAME_IFACE_VIS_POSSIBLE_FALSE
	};

	/* Needs to be the same as 'enum Game_Usr_Board' in 'game.h' */
	enum	Game_Iface_Usr_Board {
		GAME_IFACE_USR_KBOOM = -1,
		GAME_IFACE_USR_HIDDEN,
		GAME_IFACE_USR_CLEAR,
		GAME_IFACE_USR_FLAG,
		GAME_IFACE_USR_POSSIBLE
	};

	/* Needs to be the same as 'enum Game_Action' in 'game.h' */
	enum	Game_Iface_Action_Play {
		GAME_IFACE_GAME_ACT_FOO = 0,
		GAME_IFACE_GAME_ACT_STEP,
		GAME_IFACE_GAME_ACT_FLAG,
		GAME_IFACE_GAME_ACT_FLAG_POSSIBLE,
		GAME_IFACE_GAME_ACT_RM_FLAG
	};

	enum	Game_Iface_Action {
		GAME_IFACE_ACT_FOO,
		GAME_IFACE_ACT_PLAY,
		GAME_IFACE_ACT_PAUSE,
		GAME_IFACE_ACT_SAVE,
		GAME_IFACE_ACT_XYZZY_ON,
		GAME_IFACE_ACT_XYZZY_OFF,
		GAME_IFACE_ACT_XYZZY_LIN,
		GAME_IFACE_ACT_XYZZY_P,
		GAME_IFACE_ACT_XYZZY_NP,
		GAME_IFACE_ACT_QUIT
	};

	enum	Game_Iface_State {
		GAME_IFACE_STATE_PLAYING = 0,
		GAME_IFACE_STATE_SAFE,
		GAME_IFACE_STATE_GAMEOVER,

		GAME_IFACE_STATE_PAUSE,
		GAME_IFACE_STATE_CHEATED,
		GAME_IFACE_STATE_XYZZY,
		GAME_IFACE_STATE_QUIT
	};


/******************************************************************************
 ******* structs **************************************************************
 ******************************************************************************/
	struct	Game_Iface_Out {
		int	rows;
		int	cols;
		int	mines;
		int	visible [ROWS_MAX] [COLS_MAX];
		int	usr [ROWS_MAX] [COLS_MAX];
		int	flags;
		int	clr;
		int	state;
	};

	struct	Game_Iface_Score {
		int	time;
		int	clicks;
	};

	struct	Game_Iface_In {
		int	action;
		int	act_game [ROWS_MAX] [COLS_MAX];
	};


/******************************************************************************
 ******* functions ************************************************************
 ******************************************************************************/
	void	game_iface_init_rand	(int pos_row, int pos_col);
	void	game_iface_init_load	(void);
	void	game_iface		(void);


/******************************************************************************
 ******* include guard ********************************************************
 ******************************************************************************/
# endif			/* game_iface.h */


/******************************************************************************
 ******* end of file **********************************************************
 ******************************************************************************/
