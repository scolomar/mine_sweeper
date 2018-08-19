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
	# define		PROG_VERSION	"2.0"

	# define		OPT_LIST	"a:b:ef:hlp:r:s:uV:v"

	# define		ROWS_MAX	22
	# define		COLS_MAX	33

	# define		SAVE_DIR	"..//files/saved/"
	# define		DEFAULT_SAVE	"saved_000.mine"

	# define		CHEATED		(-1)


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
		ACT_HIGHLIGHT,
		ACT_PAUSE,
		ACT_SAVE,
		ACT_XYZZY_ON,
		ACT_XYZZY_OFF,
		ACT_XYZZY_LIN,
		ACT_XYZZY_SQ,
		ACT_QUIT
	};

	enum	Game_State {
		GAME_READY,
		GAME_PLAYING,
		GAME_PAUSE,
		GAME_CHEATED,
		GAME_XYZZY,
		GAME_WIN,
		GAME_OVER,
		GAME_QUIT
	};

	enum	Flag_s {
		START_FOO = 0,
		START_NEW,
		START_LOAD
	};

	enum	Flag_V {
		VERBOSE_FOO
	};

	enum	Color_Pairs {
		/* Clear */
		PAIR_1 = 1,
		PAIR_2,
		PAIR_3,
		PAIR_4,
		PAIR_5,
		PAIR_6,
		PAIR_7,
		PAIR_8,
		PAIR_BLANK,
		/* Hidden */
		PAIR_MINE,
		PAIR_HIDDEN,
		/* Possible */
		PAIR_fail,
		PAIR_POSSIBLE,
		/* Flag */
		PAIR_FAIL,
		PAIR_FLAG,
		/* kboom */
		PAIR_KBOOM,
		/* Highlight */
		PAIR_HILITE,

		/* Terminal colors */
		PAIR_TERM
	};

	enum	Eggs {
/* Stop blowing holes in my ship! */
		EGG_KBOOM,
/* Sticks and stones, love. I saved your life, you saved mine.  We’re square. */
		EGG_WIN,
/*
 * Do us a favor.  I know it’s difficult for you, but please,
 * stay here, and try not to do anything stupid.
 */
		EGG_PAUSE,
/* If you were waiting for the opportune moment, that was it. */
		EGG_UNPAUSE,
/* Nothing happens. */
		EGG_XYZZY,
/* Not a game. */
		EGG_QUIT
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
		bool	set;
		int	state;
		int	time;
		int	clicks;
	};


/******************************************************************************
 ******* variables ************************************************************
 ******************************************************************************/
	extern	char		prog_name [FILENAME_MAX];

	extern	struct Board	board;

	extern	enum Flag_s	flag_s;
	extern	enum Flag_V	flag_V;
	extern	bool		flag_exit;
	extern	bool		flag_color;

	extern	char		file_name [FILENAME_MAX];
	extern	char		file_path [FILENAME_MAX];
	extern	int		seed;

	extern	time_t		tim_ini;

	extern	bool		highlight;


/******************************************************************************
 ******* functions ************************************************************
 ******************************************************************************/
	void	init_values	(void);


# endif				/* data.h */
