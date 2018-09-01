/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/


/******************************************************************************
 ******* headers **************************************************************
 ******************************************************************************/
/*	*	*	*	*	*	*	*	*	*
 *	*	* Standard	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
		/* errno */
	#include <errno.h>
		/* bool */
	#include <stdbool.h>
		/* fscanf() & fprintf() & FILE & FILENAME_MAX */
	#include <stdio.h>
		/* getenv() */
	#include <stdlib.h>
		/* strcpy() & strcat() */
	#include <string.h>
		/* mkdir */
	#include <sys/stat.h>

/*	*	*	*	*	*	*	*	*	*
 *	*	* Other	*	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
		/* struct Game_Board */
	#include "game.h"
		/* player_iface_save_name() */
	#include "player_iface.h"

	#include "save.h"


/******************************************************************************
 ******* variables ************************************************************
 ******************************************************************************/
char	home_path [FILENAME_MAX];
char	user_game_path [FILENAME_MAX];
char	saved_path [FILENAME_MAX];
char	saved_name [FILENAME_MAX];


/******************************************************************************
 ******* main *****************************************************************
 ******************************************************************************/
void	save_init	(void)
{
	strcpy(home_path, getenv(ENV_HOME));

	strcpy(user_game_path, home_path);
	strcat(user_game_path, "/");
	strcat(user_game_path, USER_GAME_DIR);
	strcat(user_game_path, "/");

	strcpy(saved_path, home_path);
	strcat(saved_path, "/");
	strcat(saved_path, USER_SAVED_DIR);
	strcat(saved_path, "/");

	strcpy(saved_name, SAVED_NAME_DEFAULT);
	strcat(saved_name, FILE_EXTENSION);

	int	err;
#if defined	OS_LINUX
	err	= mkdir(user_game_path, 0700);
#elif defined	OS_WIN
	err	= mkdir(user_game_path);
#endif

	if (!err) {
#if defined	OS_LINUX
		mkdir(saved_path, 0700);
#elif defined	OS_WIN
		mkdir(saved_path);
#endif
	} else {

		switch (errno) {
		case EACCES:
			printf("err = EACCES");
			exit(EXIT_FAILURE);
			break;

		case EEXIST:
			/* OK */
			break;

		default:
			printf("WTF?!");
			exit(EXIT_FAILURE);
		}
	}
}

void	load_game_file	(char *filepath, char *filename)
{
	char	file_name [FILENAME_MAX];
	FILE	*fp;

	int	i;
	int	j;

	if (filepath == NULL) {
		strcpy(file_name, saved_path);
	} else {
		strcpy(file_name, filepath);
	}
	if (filename == NULL) {
		strcat(file_name, saved_name);
	} else {
		strcat(file_name, filename);
	}

	fp	= fopen(file_name, "r");
	if (fp) {
		fscanf(fp, "mine_sweeper saved game");
		fscanf(fp, " rows %i", &game_board.rows);
		fscanf(fp, " cols %i", &game_board.cols);
		fscanf(fp, " mines %i", &game_board.mines);
		fscanf(fp, " gnd");
		for (i = 0; i < game_board.rows; i++) {
			fscanf(fp, " %i", &game_board.gnd[i][0]);
			for (j = 1; j < game_board.cols; j++) {
				fscanf(fp, ",%i", &game_board.gnd[i][j]);
			}
		}
		fscanf(fp, " usr");
		for (i = 0; i < game_board.rows; i++) {
			fscanf(fp, " %i", &game_board.usr[i][0]);
			for (j = 1; j < game_board.cols; j++) {
				fscanf(fp, ",%i", &game_board.usr[i][j]);
			}
		}
		fscanf(fp, " flags %i", &game_board.flags);
		fscanf(fp, " cleared %i", &game_board.clr);

		fclose(fp);
	}
}

void	save_game_file	(char *filepath)
{
	char	file_name [FILENAME_MAX];
	char	file_num [6]	= "";
	FILE	*fp;

	int	i;
	int	j;

	/* Input box size */
	int	w;
	int	r;
	w	= 70;
	r	= 10;

	/* Default name */
	strcpy(saved_name, SAVED_NAME_DEFAULT);

	/* Request file name */
	player_iface_save_name(filepath, saved_name);

	/* Look for an unused name of the type 'name_XXX.mine'. */
	bool	x;
	x	= true;
	for (i = 0; x; i++) {
		if (filepath == NULL) {
			strcpy(file_name, saved_path);
		} else {
			strcpy(file_name, filepath);
		}
		strcat(file_name, saved_name);
		strcat(file_name, file_num);
		strcat(file_name, FILE_EXTENSION);

		fp =	fopen(file_name, "r");
		if (fp) {
			fclose(fp);
			file_num[0] =	'_';
			file_num[1] =	'0' + ((i / 100) % 10);
			file_num[2] =	'0' + ((i / 10) % 10);
			file_num[3] =	'0' + (i % 10);
			file_num[4] =	'\0';
		} else {
			x	= false;
			strcat(saved_name, file_num);
			strcat(saved_name, FILE_EXTENSION);
		}
	}

	/* Write to a new file */
	fp	= fopen(file_name, "w");
	if (fp) {
		fprintf(fp, "mine_sweeper saved game\n");
		fprintf(fp, "rows %i\n", game_board.rows);
		fprintf(fp, "cols %i\n", game_board.cols);
		fprintf(fp, "mines %i\n", game_board.mines);
		fprintf(fp, "gnd\n");
		for (i = 0; i < game_board.rows; i++) {
			fprintf(fp, "%i", game_board.gnd[i][0]);
			for (j = 1; j < game_board.cols; j++) {
				fprintf(fp, ",%i", game_board.gnd[i][j]);
			}
			fprintf(fp, "\n");
		}
		fprintf(fp, "usr\n");
		for (i = 0; i < game_board.rows; i++) {
			fprintf(fp, "%i", game_board.usr[i][0]);
			for (j = 1; j < game_board.cols; j++) {
				fprintf(fp, ",%i", game_board.usr[i][j]);
			}
			fprintf(fp, "\n");
		}
		fprintf(fp, "flags %i\n", game_board.flags);
		fprintf(fp, "cleared %i\n", game_board.clr);

		fclose(fp);
	}
}


/******************************************************************************
 ******* end of file **********************************************************
 ******************************************************************************/
