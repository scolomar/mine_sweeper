/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/


/******************************************************************************
 ******* headers **************************************************************
 ******************************************************************************/
/*	*	*	*	*	*	*	*	*	*
 *	*	* Standard	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
		/* fscanf() & fprintf() & FILE & FILENAME_MAX */
	#include <stdio.h>
		/* exit() */
	#include <stdlib.h>
		/* strcpy() & strcat() */
	#include <string.h>
		/* time_t & time() & struct tm & localtime() */
	#include <time.h>

/*	*	*	*	*	*	*	*	*	*
 *	*	* Other	*	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
		/* struct Game_Board */
	#include "game.h"
		/* enum Game_Iface_Level */
	#include "game_iface.h"
		/* player_iface_score_name() */
	#include "player_iface.h"
		/* saved_name */
	#include "save.h"

	#include "score.h"


/******************************************************************************
 ******* macros ***************************************************************
 ******************************************************************************/
	# define	BUFF_SIZE	(1024)


/******************************************************************************
 ******* variables ************************************************************
 ******************************************************************************/
char	var_path [FILENAME_MAX];
char	var_hiscores_path [FILENAME_MAX];
char	var_boards_beginner_path [FILENAME_MAX];
char	var_boards_intermediate_path [FILENAME_MAX];
char	var_boards_expert_path [FILENAME_MAX];
char	var_boards_custom_path [FILENAME_MAX];

char	var_hiscores_beginner_name [FILENAME_MAX];
char	var_hiscores_intermediate_name [FILENAME_MAX];
char	var_hiscores_expert_name [FILENAME_MAX];


/******************************************************************************
 ******* static functions *****************************************************
 ******************************************************************************/
static	void	read_scores_file	(char *file_name);


/******************************************************************************
 ******* main *****************************************************************
 ******************************************************************************/
void	score_init	(void)
{
	strcpy(var_path, INSTALL_VAR_DIR);
	strcat(var_path, "/");
	strcat(var_path, VAR_DIR);
	strcat(var_path, "/");

	strcpy(var_hiscores_path, var_path);
	strcat(var_hiscores_path, "/");
	strcat(var_hiscores_path, HISCORES_DIR);
	strcat(var_hiscores_path, "/");

	strcpy(var_boards_beginner_path, var_path);
	strcat(var_boards_beginner_path, "/");
	strcat(var_boards_beginner_path, BOARDS_BEGINNER_DIR);
	strcat(var_boards_beginner_path, "/");

	strcpy(var_boards_intermediate_path, var_path);
	strcat(var_boards_intermediate_path, "/");
	strcat(var_boards_intermediate_path, BOARDS_INTERMEDIATE_DIR);
	strcat(var_boards_intermediate_path, "/");

	strcpy(var_boards_expert_path, var_path);
	strcat(var_boards_expert_path, "/");
	strcat(var_boards_expert_path, BOARDS_EXPERT_DIR);
	strcat(var_boards_expert_path, "/");

	strcpy(var_boards_custom_path, var_path);
	strcat(var_boards_custom_path, "/");
	strcat(var_boards_custom_path, BOARDS_CUSTOM_DIR);
	strcat(var_boards_custom_path, "/");

	strcpy(var_hiscores_beginner_name, HISCORES_BEGINNER_NAME);
	strcpy(var_hiscores_intermediate_name, HISCORES_INTERMEDIATE_NAME);
	strcpy(var_hiscores_expert_name, HISCORES_EXPERT_NAME);
}

void	save_score	(const struct Game_Iface_Score  *game_iface_score)
{
	/* File name */
	char	file_name [FILENAME_MAX];
	strcpy(file_name, var_hiscores_path);
	switch (game_iface_score->level) {
	case GAME_IFACE_LEVEL_BEGINNER:
		strcat(file_name, var_hiscores_beginner_name);
		break;

	case GAME_IFACE_LEVEL_INTERMEDIATE:
		strcat(file_name, var_hiscores_intermediate_name);
		break;

	case GAME_IFACE_LEVEL_EXPERT:
		strcat(file_name, var_hiscores_expert_name);
		break;
	}

	/* Date & time */
	time_t		date_secs;
	struct tm	*date_format;
	date_secs	= time(NULL);
	date_format	= localtime(&date_secs);

	/* Player name (foo is default) */
	char	player_name [BUFF_SIZE];
	player_iface_score_name(player_name);

	/* Write to file (append) */
	FILE	*fp;
	fp	= fopen(file_name, "a");
	if (fp) {
		fprintf(fp, "\n");
		fprintf(fp, "name	%s\n", player_name);
		fprintf(fp, "date	%i\n", (int)date_secs);
		fprintf(fp, "{\n");
		fprintf(fp, "	isdst	%i\n", date_format->tm_isdst);
		fprintf(fp, "	yday	%i\n", date_format->tm_yday);
		fprintf(fp, "	wday	%i\n", date_format->tm_wday);
		fprintf(fp, "	year	%i\n", date_format->tm_year);
		fprintf(fp, "	mon	%i\n", date_format->tm_mon);
		fprintf(fp, "	mday	%i\n", date_format->tm_mday);
		fprintf(fp, "	hour	%i\n", date_format->tm_hour);
		fprintf(fp, "	min	%i\n", date_format->tm_min);
		fprintf(fp, "	sec	%i\n", date_format->tm_sec);
		fprintf(fp, "}\n");
		fprintf(fp, "time	%i\n", game_iface_score->time);
		fprintf(fp, "clicks	%i\n", game_iface_score->clicks);
		fprintf(fp, "file	%s\n", saved_name);

		fclose(fp);
	} else {
		exit(EXIT_FAILURE);
	}
}

void	read_scores	(void)
{
	/* File */
	char	file_name [FILENAME_MAX];

	/* Beginner */
	strcpy(file_name, var_hiscores_path);
	strcat(file_name, var_hiscores_beginner_name);
	read_scores_file(file_name);

	/* Intermediate */
	strcpy(file_name, var_hiscores_path);
	strcat(file_name, var_hiscores_intermediate_name);
	read_scores_file(file_name);

	/* Expert */
	strcpy(file_name, var_hiscores_path);
	strcat(file_name, var_hiscores_expert_name);
	read_scores_file(file_name);
}


/******************************************************************************
 ******* static functions *****************************************************
 ******************************************************************************/
static	void	read_scores_file	(char *file_name)
{
	/* File */
	FILE	*fp;
	int	c;

	/* Score variables */
	char	title [BUFF_SIZE];
	char	name [BUFF_SIZE];
	int	year;
	int	mon;
	int	day;
	int	time;
	int	hours;
	int	mins;
	int	secs;
	int	clicks;
	char	file [FILENAME_MAX];

	fp	= fopen(file_name, "r");

	if (fp) {
		/* Title */
		fscanf(fp, "%[^\n]s", title);
		/* For some reason, a space after "%[^\n]s" doesn't skip spaces */
		fscanf(fp, " ");

		/* Print */
		printf("_______________________________________________________\n");
		printf("%s\n\n", title);
		printf("name	date		clicks	time		file\n\n");

		while ((c = getc(fp)) != EOF){
			ungetc(c, fp);

			/* Read */
			fscanf(fp, "name	%s ", name);
			fscanf(fp, "date	%*i ");
			fscanf(fp, "{ ");
			fscanf(fp, "	isdst	%*i ");
			fscanf(fp, "	yday	%*i ");
			fscanf(fp, "	wday	%*i ");
			fscanf(fp, "	year	%i ", &year);
			fscanf(fp, "	mon	%i ", &mon);
			fscanf(fp, "	mday	%i ", &day);
			fscanf(fp, "	hour	%*i ");
			fscanf(fp, "	min	%*i ");
			fscanf(fp, "	sec	%*i ");
			fscanf(fp, "} ");
			fscanf(fp, "time	%i ", &time);
			fscanf(fp, "clicks	%i ", &clicks);
			fscanf(fp, "file	%s ", file);

			/* Adjust date & time */
			year	+= 1900;
			hours	= (time / 3600);
			mins	= ((time % 3600) / 60);
			secs	= (time % 60);

			/* Print */
			printf("%s\n\t", name);
			printf("%4i/%2i/%2i	%i	%i:%02i:%02i	\t%s\n\n",
				year, mon, day,
						clicks,
							hours, mins, secs,
									file);
		}

		fclose(fp);
	}
}


/******************************************************************************
 ******* end of file **********************************************************
 ******************************************************************************/
