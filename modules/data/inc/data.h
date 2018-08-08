/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

# ifndef			DATA_H
	# define		DATA_H

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

	# define		VERSION		"v2.a1"
	# define		OPT_LIST	"a:b:f:hi:j:k:lo:p:r:s:V:vx"
	# define		DIM_MAX		64

	# define		P_SOL		prb_sol
	# define		P_LEN		prb_lvl[0]
	# define		P_LVL		prb_lvl[1]
	# define		P_MAT		prb_mtx[0]
	# define		P_ROWS		prb_mtx_rows
	# define		P_COLS		prb_mtx_cols
	# define		P_MINES		prb_mtx_mines[0]

	# define		USR_MAT		prb_mtx[1]
	# define		USR_FLAGS	prb_mtx_mines[1]
	# define		USR_CLEARED	prb_mtx_cleared


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
		USR_FLAG
	};

	enum	Actions {
		ACT_MOVE_UP,
		ACT_MOVE_DOWN,
		ACT_MOVE_RIGHT,
		ACT_MOVE_LEFT,
		ACT_DISCOVER,
		ACT_PLACE_FLAG,
		ACT_RM_FLAG,
		ACT_QUIT
	};


/******************************************************************************
 ******* variables ************************************************************
 ******************************************************************************/
	extern	int	prb_lvl [2];
	extern	int	prb_sol [3] [DIM_MAX] [DIM_MAX];

	extern	int	prb_mtx [2] [DIM_MAX] [DIM_MAX];
	extern	int	prb_mtx_rows;
	extern	int	prb_mtx_cols;
	extern	int	prb_mtx_mines [2];
	extern	int	prb_mtx_cleared;
	extern	double	p;

	extern	int	count;

	extern	clock_t	tim_0;
	extern	clock_t	tim_1;
	extern	double	tim_tot;

	extern	int	flag_s;
	extern	int	flag_V;
	extern	bool	flag_x;

	extern	char	file_path [FILENAME_MAX];
	extern	int	seed;


/******************************************************************************
 ******* functions ************************************************************
 ******************************************************************************/
	void	init_values	(void);


# endif				/* data.h */
