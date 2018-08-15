/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

	#include <stdio.h>
//	#include <stdlib.h>

	#include "data.h"

	#include "save.h"


/*----------------------------------------------------------------------------*/

	/*
	 * Load from a file.
	 */
int	load_game_file	(void)
{
	FILE	*fp;
	int	i;
	int	j;
	int	err;

	fp =	fopen(file_path, "r");
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
	} else {
		err =	ERR_FILEPATH;
	}

	return	err;
}

	/*
	 * Save into a file.
	 */
int	save_game_file	(void)
{
	/* Look for an unused name of the type 'saved_XXX.mine'. */
	FILE	*fp;
	char	filename[30] = "../files/saved/saved_000.mine";
	int	i;
	bool	x;
	x =	true;
	for (i = 0; x; i++) {
		fp =	fopen(filename, "r");
		if (fp) {
			fclose(fp);
			filename[21] =	'0' + ((i / 100) % 10);
			filename[22] =	'0' + ((i / 10) % 10);
			filename[23] =	'0' + (i % 10);
		} else {
			x = false;
		}
	}

	/* Write to a new file */
	int	err;
	int	j;
	fp = fopen(filename, "w");
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
		err =	ERR_FILEPATH;
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
