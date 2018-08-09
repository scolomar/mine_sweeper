/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

	#include <stdint.h>
	#include <stdio.h>
	#include <stdlib.h>

	#include "alx_seed.h"

	#include "data.h"

	#include "init.h"


	/*
	 * Init:
	 */
/*----------------------------------------------------------------------------*/

static	void	init_clr	(void);
static	void	init_usr	(void);


void	init_rand	(void)
{
	int	l;
	int	c;
	int	i;

	/* clear */
	init_clr();

	/* put mines */
	board.mines =	board.p * board.rows * board.cols;
	i =	0;
	while (i < board.mines) {
		l =	(rand() % board.rows);
		c =	(rand() % board.cols);

		if (board.gnd[l][c] == MINE_NO) {
			board.gnd[l][c] = MINE_YES;
			i++;
		}
	}

	/* init user screen */
	init_usr();
}

	/*
	 * Read from a file.
	 */
void	init_custom	(void)
{
	int64_t	i;
	int64_t	j;
	char	ch;
	FILE	*fp;

	/* clear */
	init_clr();

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
	} else {
		printf("Fail");
	}
}


static	void	init_clr	(void)
{
	int	i;
	int	j;

	/* clear */
	for (i = 0; i < board.rows; i++) {
		for (j = 0; j < board.cols; j++) {
			board.gnd[i][j] = MINE_NO;
			board.usr[i][j] = USR_HIDDEN;
		}
	}
	board.mines = 0;
	board.flags = 0;
	board.cleared = 0;
	board.state = GAME_PLAYING;
}

static	void	init_usr	(void)
{
	int	l;
	int	i;
	int	c;
	int	j;

	for (l = 0; l < board.rows; l++) {
		for (c = 0; c < board.cols; c++) {
			if (board.gnd[l][c] >= MINE_YES) {
				for (i = l-1; i < l+2; i++) {
					for (j = c-1; j < c+2; j++) {
						if (i >= 0 && i < board.rows &&
								j >= 0 &&
								j < board.cols) {
							board.gnd[i][j]++;
						}
					}
				}
			}
		}
	}

	board.flags =	0;
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
