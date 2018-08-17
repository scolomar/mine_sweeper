/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

		/* has_colors() & start_color() & init_pair() */
	#include <ncurses.h>
		/* bool */
	#include <stdbool.h>
		/* srand() */
	#include <stdlib.h>
		/* strcpy() */
	#include <string.h>
		/* clock_t & clock() & time() */
	#include <time.h>
		/* getpid() */
	#include <unistd.h>

		/* seedf() */
	#include "alx_seed.h"

	#include "data.h"


/*
 *	[][][0] = Valor real	< 0:	0 minas cercanas y todas las cercanas descubiertas
 *				0-8:	N.º de minas cercanas
 *				> 8:	Mina
 *
 *	[][][1] = Estado	0:	Oculta
 *				1:	Descubierta
 *				2:	Bandera V
 *				3:	Bandera F
 *
 *	Interfaz		+:	Celda oculta
 *				·:	0 minas cercanas
 *				1-8:	N.º de minas cercanas
 *				#:	Mina marcada
 *				M:	Mina no explotada
 *				N:	No había mina
 *				X:	Mina explotada
 */


/******************************************************************************
 ******* variables ************************************************************
 ******************************************************************************/
char		prog_name[FILENAME_MAX];

struct Board	board;

bool		color;


clock_t		tim_0;
clock_t		tim_1;
double		tim_tot;

enum Flag_s	flag_s;
enum Flag_V	flag_V;
enum Flag_x	flag_x;

char		file_name [FILENAME_MAX];
char		file_path [FILENAME_MAX];
int		seed;


/******************************************************************************
 ******* functions ************************************************************
 ******************************************************************************/
void	init_values	(void)
{
	board.p =	0.05;
	board.rows =	10;
	board.cols =	10;

	strcpy(file_name, DEFAULT_SAVE);

	flag_s =	START_FOO;
	flag_V =	1;
	flag_x =	0;

	seed =		seedf(clock(), time(NULL), getpid());
	srand(seed);

	color =		false;
	if (has_colors()) {
		color =	true;
		start_color();

		/* clear */
		init_pair(PAIR_1, COLOR_BLUE, COLOR_WHITE);
		init_pair(PAIR_2, COLOR_GREEN, COLOR_WHITE);
		init_pair(PAIR_3, COLOR_RED, COLOR_WHITE);
		init_pair(PAIR_4, COLOR_BLUE, COLOR_WHITE);
		init_pair(PAIR_5, COLOR_RED, COLOR_WHITE);
		init_pair(PAIR_6, COLOR_CYAN, COLOR_WHITE);
		init_pair(PAIR_7, COLOR_BLACK, COLOR_WHITE);
		init_pair(PAIR_8, COLOR_BLACK, COLOR_WHITE);
		init_pair(PAIR_BLANK, COLOR_BLACK, COLOR_WHITE);
		/* hidden */
		init_pair(PAIR_MINE, COLOR_WHITE, COLOR_BLACK);
		init_pair(PAIR_HIDDEN, COLOR_WHITE, COLOR_BLACK);
		/* possible */
		init_pair(PAIR_fail, COLOR_RED, COLOR_BLACK);
		init_pair(PAIR_POSSIBLE, COLOR_BLUE, COLOR_BLACK);
		/* flag */
		init_pair(PAIR_FAIL, COLOR_RED, COLOR_BLACK);
		init_pair(PAIR_FLAG, COLOR_RED, COLOR_BLACK);
		/* kboom */
		init_pair(PAIR_KBOOM, COLOR_BLACK, COLOR_RED);
	}
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
