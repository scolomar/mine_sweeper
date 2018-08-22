/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

		/* fscanf() & fprintf() & FILE & FILENAME_MAX */
	#include <stdio.h>
		/* strcpy() & strcat() */
	#include <string.h>

	#include "data.h"

	#include "save.h"


static	FILE	*fp;

/*----------------------------------------------------------------------------*/

	/*
	 * Load from a file.
	 */
int	load_game_file	(void)
{
	int	i;
	int	j;
	int	err;
	char	file_name [FILENAME_MAX];

	strcpy(file_name, saved_path);
	strcat(file_name, saved_name);

	fp =	fopen(file_name, "r");
	if (fp) {
		fscanf(fp, "mine_sweeper saved game");
		fscanf(fp, " rows %i", &board.rows);
		fscanf(fp, " cols %i", &board.cols);
		fscanf(fp, " mines %i", &board.mines);
		fscanf(fp, " gnd");
		for (i = 0; i < board.rows; i++) {
			fscanf(fp, " %i", &board.gnd[i][0]);
			for (j = 1; j < board.cols; j++) {
				fscanf(fp, ",%i", &board.gnd[i][j]);
			}
		}
		fscanf(fp, " usr");
		for (i = 0; i < board.rows; i++) {
			fscanf(fp, " %i", &board.usr[i][0]);
			for (j = 1; j < board.cols; j++) {
				fscanf(fp, ",%i", &board.usr[i][j]);
			}
		}
		fscanf(fp, " flags %i", &board.flags);
		fscanf(fp, " cleared %i", &board.cleared);

		fclose(fp);
		err =	ERR_OK;

		board.time =	CHEATED;
		board.clicks =	CHEATED;
		board.state =	GAME_CHEATED;
	} else {
		err =	ERR_FILENAME;
	}

	return	err;
}

	/*
	 * Save into a file.
	 */
int	save_game_file	(void)
{
	/* Look for an unused name of the type 'saved_XXX.mine'. */
	char	file_name [FILENAME_MAX];
	int	i;
	bool	x;
	x =	true;
	strcpy(saved_name, SAVED_NAME_DEFAULT);
	for (i = 0; x; i++) {
		strcpy(file_name, saved_path);
		strcat(file_name, saved_name);

		fp =	fopen(file_name, "r");
		if (fp) {
			fclose(fp);
			saved_name[6] =	'0' + ((i / 100) % 10);
			saved_name[7] =	'0' + ((i / 10) % 10);
			saved_name[8] =	'0' + (i % 10);
		} else {
			x = false;
		}
	}

	/* Write to a new file */
	int	err;
	int	j;
	fp = fopen(file_name, "w");
	if (fp) {
		fprintf(fp, "mine_sweeper saved game\n");
		fprintf(fp, "rows %i\n", board.rows);
		fprintf(fp, "cols %i\n", board.cols);
		fprintf(fp, "mines %i\n", board.mines);
		fprintf(fp, "gnd\n");
		for (i = 0; i < board.rows; i++) {
			fprintf(fp, "%i", board.gnd[i][0]);
			for (j = 1; j < board.cols; j++) {
				fprintf(fp, ",%i", board.gnd[i][j]);
			}
			fprintf(fp, "\n");
		}
		fprintf(fp, "usr\n");
		for (i = 0; i < board.rows; i++) {
			fprintf(fp, "%i", board.usr[i][0]);
			for (j = 1; j < board.cols; j++) {
				fprintf(fp, ",%i", board.usr[i][j]);
			}
			fprintf(fp, "\n");
		}
		fprintf(fp, "flags %i\n", board.flags);
		fprintf(fp, "cleared %i\n", board.cleared);

		fclose(fp);
		err =	ERR_OK;
	} else {
		err =	ERR_FILENAME;
	}

	return	err;
}

/******************************************************************************
 ******************************************************************************
 **** END OF FILE *************************************************************
 ******************************************************************************
 ******************************************************************************/

/******************************************************************************
 ******************************************************************************
 **** END OF FILE *************************************************************
 ******************************************************************************
 ******************************************************************************/
