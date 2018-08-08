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
	P_MINES =	p * P_ROWS * P_COLS;
	i =	0;
	while (i < P_MINES) {
		l =	(rand() % P_ROWS);
		c =	(rand() % P_COLS);

		if (P_MAT[l][c] == MINE_NO) {
			P_MAT[l][c] = MINE_YES;
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
{/*
	int	l;
	int	c;
	char	ch;
	FILE	*fp;

	for (l = 0; l < P_ROWS; l++) {
		for (c = 0; c < P_COLS; c++) {
			P_MAT[l][c] = MINE_YES;
		}
	}

	fp =	fopen(file_path, "r");
	if (fp) {
		if ((ch = fgetc(fp)) != EOF) {
			ungetc(ch, fp);

			fscanf(fp, "%i", &P_DIM);
			while (fscanf(fp, "%i %i", &l, &c) == 2) {
				mat_0[l][c] = MINE_NO;
			}
		}
		fclose(fp);
	}*/
}


static	void	init_clr	(void)
{
	int	l;
	int	c;

	/* clear */
	for (l = 0; l < P_ROWS; l++) {
		for (c = 0; c < P_COLS; c++) {
			P_MAT[l][c] = MINE_NO;
			USR_MAT[l][c] = USR_HIDDEN;
		}
	}
}

static	void	init_usr	(void)
{
	int	l;
	int	i;
	int	c;
	int	j;

	for (l = 0; l < P_ROWS; l++) {
		for (c = 0; c < P_COLS; c++) {
			if (P_MAT[l][c] >= MINE_YES) {
				for (i = l-1; i < l+2; i++) {
					for (j = c-1; j < c+2; j++) {
						if (i >= 0 && i < P_ROWS &&
								j >= 0 &&
								j < P_COLS) {
							P_MAT[i][j]++;
						}
					}
				}
			}
		}
	}

	USR_FLAGS =	0;
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
