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
		l =	(rand() % P_ROWS);
		c =	(rand() % P_COLS);

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
/*
 *
 */
}


static	void	init_clr	(void)
{
	int	l;
	int	c;

	/* clear */
	for (l = 0; l < P_ROWS; l++) {
		for (c = 0; c < P_COLS; c++) {
			board.gnd[l][c] = MINE_NO;
			board.usr[l][c] = USR_HIDDEN;
		}
	}
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
							P_MAT[i][j]++;
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
