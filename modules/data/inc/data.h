/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

# ifndef			MSW_DATA_H
	# define		MSW_DATA_H

		/* bool */
	#include <stdbool.h>
		/* FILENAME_MAX */
	#include <stdio.h>
		/* clock_t */
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
	# define		PROG_VERSION	"v2.b.1"

	# define		OPT_LIST	"a:b:f:hi:j:k:lo:p:r:s:V:vx"

	# define		DIM_MAX		64

	# define		DEFAULT_SAVE	"..//files/saved/saved_0.mine"


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
		ACT_MOVE_UP,
		ACT_MOVE_DOWN,
		ACT_MOVE_RIGHT,
		ACT_MOVE_LEFT,
		ACT_DISCOVER,
		ACT_PLACE_FLAG,
		ACT_PLACE_POSSIBLE,
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


/******************************************************************************
 ******* structs **************************************************************
 ******************************************************************************/
	struct	Board {
		int	rows;
		int	cols;
		double	p;
		int	mines;
		int	gnd [DIM_MAX] [DIM_MAX];
		int	usr [DIM_MAX] [DIM_MAX];
		int	flags;
		int	cleared;
		int	state;
	};


/******************************************************************************
 ******* variables ************************************************************
 ******************************************************************************/
	extern	struct Board	board;

	extern	clock_t		tim_0;
	extern	clock_t		tim_1;
	extern	double		tim_tot;

	extern	enum Flag_s	flag_s;
	extern	enum Flag_V	flag_V;
	extern	enum Flag_x	flag_x;

	extern	char		file_path [FILENAME_MAX];
	extern	int		seed;


/******************************************************************************
 ******* functions ************************************************************
 ******************************************************************************/
	void	init_values	(void);


# endif				/* data.h */
