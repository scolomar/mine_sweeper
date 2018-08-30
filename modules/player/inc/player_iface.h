/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/


/******************************************************************************
 ******* include guard ********************************************************
 ******************************************************************************/
# ifndef		MSW_PLAYER_IFACE_H
	# define	MSW_PLAYER_IFACE_H


/******************************************************************************
 ******* headers **************************************************************
 ******************************************************************************/
	/* struct Game_Iface_... */
	#include "game_iface.h"


/******************************************************************************
 ******* enums ****************************************************************
 ******************************************************************************/
	enum	Player_Iface_Mode {
		PLAYER_IFACE_FOO = 0,
		PLAYER_IFACE_CLUI,
		PLAYER_IFACE_TUI,
		PLAYER_IFACE_GUI
	};

	enum	Player_Iface_Action {
		PLAYER_IFACE_ACT_FOO,
		PLAYER_IFACE_ACT_STEP,
		PLAYER_IFACE_ACT_FLAG,
		PLAYER_IFACE_ACT_FLAG_POSSIBLE,
		PLAYER_IFACE_ACT_RM_FLAG,

		PLAYER_IFACE_ACT_PAUSE,
		PLAYER_IFACE_ACT_SAVE,
		PLAYER_IFACE_ACT_XYZZY_ON,
		PLAYER_IFACE_ACT_XYZZY_OFF,
		PLAYER_IFACE_ACT_XYZZY_LIN,
		PLAYER_IFACE_ACT_XYZZY_P,
		PLAYER_IFACE_ACT_XYZZY_NP,
		PLAYER_IFACE_ACT_QUIT,

		PLAYER_IFACE_ACT_MOVE_UP,
		PLAYER_IFACE_ACT_MOVE_DOWN,
		PLAYER_IFACE_ACT_MOVE_RIGHT,
		PLAYER_IFACE_ACT_MOVE_LEFT,
		PLAYER_IFACE_ACT_HIGHLIGHT
	};


/******************************************************************************
 ******* structs **************************************************************
 ******************************************************************************/
	struct	Player_Iface_Position {
		int	rows;
		int	cols;
		int	row;
		int	col;
		int	highlight;
	};


/******************************************************************************
 ******* variables ************************************************************
 ******************************************************************************/
extern	int	player_iface_mode;


/******************************************************************************
 ******* functions ************************************************************
 ******************************************************************************/
void	player_iface_init	(int rows, int cols);
void	player_iface_start	(int *pos_row, int *pos_col);
void	player_iface		(const	struct Game_Iface_Out	*game_iface_out,
				const	struct Game_Iface_Score	*game_iface_score,
					struct Game_Iface_In	*game_iface_in);
void	player_iface_cleanup	(void);


/******************************************************************************
 ******* include guard ********************************************************
 ******************************************************************************/
# endif			/* player_iface.h */


/******************************************************************************
 ******* end of file **********************************************************
 ******************************************************************************/
