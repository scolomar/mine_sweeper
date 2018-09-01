/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/


/******************************************************************************
 ******* include guard ********************************************************
 ******************************************************************************/
# ifndef		MSW_SCORE_H
	# define	MSW_SCORE_H


/******************************************************************************
 ******* headers **************************************************************
 ******************************************************************************/
		/* FILENAME_MAX */
	#include <stdio.h>


/******************************************************************************
 ******* macros ***************************************************************
 ******************************************************************************/
	# if defined (OS_LINUX)
	#	define		ENV_HOME		"HOME"
	# elif defined (OS_WIN)
	#	define		ENV_HOME		"USERPROFILE"
	# endif

	# define	HISCORES_DIR			"hiscores/"
	# define	BOARDS_BEGINNER_DIR		"hiscores/boards_beginner/"
	# define	BOARDS_INTERMEDIATE_DIR		"hiscores/boards_intermediate/"
	# define	BOARDS_EXPERT_DIR		"hiscores/boards_expert/"
	# define	BOARDS_CUSTOM_DIR		"hiscores/boards_custom/"
	# define	USER_SAVED_DIR			".mine_sweeper/saved/"
	# define	HISCORES_BEGINNER_NAME		"hiscores_beginner.mine"
	# define	HISCORES_INTERMEDIATE_NAME	"hiscores_intermediate.mine"
	# define	HISCORES_EXPERT_NAME		"hiscores_expert.mine"


/******************************************************************************
 ******* variables ************************************************************
 ******************************************************************************/
extern	char	var_path [FILENAME_MAX];
extern	char	var_hiscores_path [FILENAME_MAX];
extern	char	var_boards_beginner_path [FILENAME_MAX];
extern	char	var_boards_intermediate_path [FILENAME_MAX];
extern	char	var_boards_expert_path [FILENAME_MAX];
extern	char	var_boards_custom_path [FILENAME_MAX];

extern	char	var_hiscores_beginner_name [FILENAME_MAX];
extern	char	var_hiscores_intermediate_name [FILENAME_MAX];
extern	char	var_hiscores_expert_name [FILENAME_MAX];


/******************************************************************************
 ******* functions ************************************************************
 ******************************************************************************/
void	score_init	(void);
void	save_score	(const struct Game_Iface_Score  *game_iface_score);
void	read_scores	(void);


/******************************************************************************
 ******* include guard ********************************************************
 ******************************************************************************/
# endif				/* score.h */


/******************************************************************************
 ******* end of file **********************************************************
 ******************************************************************************/
