/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/


/******************************************************************************
 ******* include guard ********************************************************
 ******************************************************************************/
# ifndef		MSW_PLAYER_CLUI_H
	# define	MSW_PLAYER_CLUI_H


/******************************************************************************
 ******* headers **************************************************************
 ******************************************************************************/
		/* struct Game_Iface_... */
	#include "game_iface.h"

	#include "player_iface.h"


/******************************************************************************
 ******* enums ****************************************************************
 ******************************************************************************/
	enum	Player_CLUI_Char {
		PLAYER_CLUI_CHAR_KBOOM		= '#',
		PLAYER_CLUI_CHAR_HIDDEN_FIELD	= '+',
		PLAYER_CLUI_CHAR_HIDDEN_MINE	= '*',
		PLAYER_CLUI_CHAR_HIDDEN_SAFE	= '-',
		PLAYER_CLUI_CHAR_SAFE_MINE	= 'v',
		PLAYER_CLUI_CHAR_0		= ' ',
		PLAYER_CLUI_CHAR_1		= '1',
		PLAYER_CLUI_CHAR_2		= '2',
		PLAYER_CLUI_CHAR_3		= '3',
		PLAYER_CLUI_CHAR_4		= '4',
		PLAYER_CLUI_CHAR_5		= '5',
		PLAYER_CLUI_CHAR_6		= '6',
		PLAYER_CLUI_CHAR_7		= '7',
		PLAYER_CLUI_CHAR_8		= '8',
		PLAYER_CLUI_CHAR_FLAG		= '!',
		PLAYER_CLUI_CHAR_FLAG_FALSE	= 'F',
		PLAYER_CLUI_CHAR_POSSIBLE	= '?',
		PLAYER_CLUI_CHAR_POSSIBLE_FALSE	= 'f'
	};


/******************************************************************************
 ******* functions ************************************************************
 ******************************************************************************/
void	player_clui_start	(const struct Player_Iface_Position	*position,
				const char				*title,
				const char				*subtitle,
				int					*action);

void	player_clui		(const struct Game_Iface_Out		*board,
				const struct Player_Iface_Position	*position,
				const char				*title,
				const char				*subtitle,
				int					*action);

void	player_clui_save_name	(const char *filepath, char *filename);
void	player_clui_score_name	(char *player_name);


/******************************************************************************
 ******* include guard ********************************************************
 ******************************************************************************/
# endif			/* player_clui.h */


/******************************************************************************
 ******* end of file **********************************************************
 ******************************************************************************/
