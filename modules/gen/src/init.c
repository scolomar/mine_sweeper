/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

	#include <stdio.h>
	#include <stdlib.h>

	#include "alx_seed.h"

	#include "data.h"
	#include "save.h"

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
	/* clear */
	init_clr();

	load_game_file();
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
	board.time = 0;
	board.clicks = 0;
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
