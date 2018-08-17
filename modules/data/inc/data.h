/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

# ifndef			MSW_DATA_H
	# define		MSW_DATA_H

		/* bool */
	#include <stdbool.h>
		/* FILENAME_MAX */
	#include <stdio.h>
		/* time_t */
	#include <time.h>


/******************************************************************************
 ******* macros ***************************************************************
 ******************************************************************************/
	# define		DBG	true
	# if (DBG)
	# 	define		DBG_PRINT(x, y, z)	print_verbose(x, y, z)
	# else
	# 	define		DBG_PRINT(x, y, z)	do {} while (0)
	# endif

	# define		PROG_NAME	"mine-sweeper"
	# define		PROG_YEAR	"2015"
	# define		PROG_VERSION	"v2.b"

	# define		OPT_LIST	"a:b:f:hi:j:k:lo:p:r:s:V:vx"

	# define		ROWS_MAX	22
	# define		COLS_MAX	39

	# define		SAVE_DIR	"..//files/saved/"
	# define		DEFAULT_SAVE	"saved_000.mine"


/******************************************************************************
 ******* enums ****************************************************************
 ******************************************************************************/
	enum	Mine_Board {
		MINE_NO = 0,
		MINE_YES = 9
	};

	enum	Usr_Board {
		KBOOM = -1,
		USR_HIDDEN,
		USR_CLEAR,
		USR_FLAG,
		USR_POSSIBLE
	};

	enum	Actions {
		ACT_FOO,
		ACT_MOVE_UP,
		ACT_MOVE_DOWN,
		ACT_MOVE_RIGHT,
		ACT_MOVE_LEFT,
		ACT_STEP,
		ACT_FLAG,
		ACT_FLAG_POSSIBLE,
		ACT_RM_FLAG,
		ACT_SAVE,
		ACT_QUIT
	};

	enum	Game_State {
		GAME_PLAYING,
		GAME_WIN,
		GAME_OVER
	};

	enum	Flag_s {
		START_FOO,
		START_NEW,
		START_LOAD
	};

	enum	Flag_V {
		VERBOSE_FOO
	};

	enum	Flag_x {
		X_FOO
	};

	enum	Color_Pairs {
		/* clear */
		PAIR_1 = 1,
		PAIR_2,
		PAIR_3,
		PAIR_4,
		PAIR_5,
		PAIR_6,
		PAIR_7,
		PAIR_8,
		PAIR_BLANK,
		/* hidden */
		PAIR_MINE,
		PAIR_HIDDEN,
		/* possible */
		PAIR_fail,
		PAIR_POSSIBLE,
		/* flag */
		PAIR_FAIL,
		PAIR_FLAG,
		/* kboom */
		PAIR_KBOOM
	};


/******************************************************************************
 ******* structs **************************************************************
 ******************************************************************************/
	struct	Board {
		int	rows;
		int	cols;
		double	p;
		int	mines;
		int	gnd [ROWS_MAX] [COLS_MAX];
		int	usr [ROWS_MAX] [COLS_MAX];
		int	flags;
		int	cleared;
		int	state;
		int	time;
		int	clicks;
	};


/******************************************************************************
 ******* variables ************************************************************
 ******************************************************************************/
	extern	char		prog_name [FILENAME_MAX];

	extern	struct Board	board;

	extern	bool		color;

	extern	time_t		tim_ini;

	extern	enum Flag_s	flag_s;
	extern	enum Flag_V	flag_V;
	extern	enum Flag_x	flag_x;

	extern	char		file_name [FILENAME_MAX];
	extern	char		file_path [FILENAME_MAX];
	extern	int		seed;


/******************************************************************************
 ******* functions ************************************************************
 ******************************************************************************/
	void	init_values	(void);


# endif				/* data.h */
