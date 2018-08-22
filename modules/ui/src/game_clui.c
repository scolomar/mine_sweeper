/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/


		/* sprintf() */
	#include <stdio.h>
		/* wchar_t */
	#include <wchar.h>

		/* board & macros */
	#include "data.h"

	#include "game_clui.h"


	# define	TITLE_SIZE	(20)


/******************************************************************************
 ******| static |**************************************************************
 ******************************************************************************/
static	int	usr_input		(void);

static	void	show_board		(int pos_row, int pos_col);
static	void	board_loop		(int pos_row, int pos_col);

static	void	show_help		(void);
static	void	show_help_ready		(void);
static	void	show_help_playing	(void);
static	void	show_help_pause		(void);
static	void	show_help_xyzzy		(void);
static	void	show_help_cheated	(void);
static	void	show_help_end		(void);


/******************************************************************************
 ******| main |****************************************************************
 ******************************************************************************/
int	game_clui			(int oldaction, int pos_row, int pos_col)
{
	/* User action */
	int	action;
	if (oldaction != ACT_FOO) {
		show_help();
		show_board(pos_row, pos_col);
	}
	action = usr_input();

	return	action;
}


/******************************************************************************
 ******| static |**************************************************************
 ******************************************************************************/
static	int	usr_input		(void)
{
	wchar_t	ch;
	ch = getchar();

	int	action;

	switch (ch) {
	/* Escape sequence */
	case 27:
		/* Arrows ¿? */
		ch = getchar();
		switch (ch) {
		case 91:
			ch = getchar();
			switch (ch) {
			case 65:
				action =	ACT_MOVE_UP;
				break;

			case 66:
				action =	ACT_MOVE_DOWN;
				break;

			case 67:
				action =	ACT_MOVE_RIGHT;
				break;

			case 68:
				action =	ACT_MOVE_LEFT;
				break;
			}
			break;
		}
		break;

	case 'h':
		action =	ACT_MOVE_LEFT;
		break;

	case 'j':
		action =	ACT_MOVE_DOWN;
		break;

	case 'k':
		action =	ACT_MOVE_UP;
		break;

	case 'l':
		action =	ACT_MOVE_RIGHT;
		break;

	case '+':
		action =	ACT_STEP;
		break;

	case ' ':
		action =	ACT_FLAG;
		break;

	case 'f':
		action =	ACT_FLAG_POSSIBLE;
		break;

		/* ASCII 0x08 is BS */
	case 0x7F:
	case 0x08:
		action =	ACT_RM_FLAG;
		break;

	case 'p':
		action =	ACT_PAUSE;
		break;

	case 's':
		action =	ACT_SAVE;
		break;

	case 'x':
		/* Special sequence "xyzzy" */
		ch = getchar();
		if (ch == 'y') {
			ch = getchar();
			if (ch == 'z') {
				ch = getchar();
				if (ch == 'z') {
					ch = getchar();
					if (ch == 'y') {
						action =	ACT_XYZZY_ON;
					}
				}
			}
		}
		break;

	case '0':
		action =	ACT_XYZZY_OFF;
		break;

	case '1':
		action =	ACT_XYZZY_LIN;
		break;

	case '2':
		action =	ACT_XYZZY_P;
		break;

	case '3':
		action =	ACT_XYZZY_NP;
		break;

	case 'q':
		action =	ACT_QUIT;
		break;

	default:
		action =	ACT_FOO;
		break;
	}

	return	action;
}

static	void	show_board		(int pos_row, int pos_col)
{
	/* Title */
	char	tit [TITLE_SIZE];
	switch (board.state) {
	case GAME_READY:
	case GAME_XYZZY:
	case GAME_CHEATED:
	case GAME_PLAYING:
	case GAME_PAUSE:
		sprintf(tit, "Mines: %i/%i", board.flags, board.mines);
		break;

	case GAME_OVER:
		sprintf(tit, "GAME OVER");
		break;

	case GAME_WIN:
		sprintf(tit, "You win!");
		break;
	}
	puts("________________________________________________________________________________");
	puts(tit);

	/* Board */
	board_loop(pos_row, pos_col);

	/* Subtitle */
	char	subtit[TITLE_SIZE];
	int	mins;
	int	secs;
	if (board.time != CHEATED) {
		mins =	(int)(board.time / 60);
		secs =	((int)board.time % 60);
		sprintf(subtit, "%i:%02i | %i", mins, secs, board.clicks);
		puts(subtit);
	}
	puts("--------------------------------------------------------------------------------");

}

static	void	board_loop		(int pos_row, int pos_col)
{
	int	i;
	int	j;
	wchar_t	ch;

	putchar('\n');
	for (i = 0; i < board.rows; i++) {
		for (j = 0; j < board.cols; j++) {
			ch =	board.visible[i][j];

			/* Print char */
			if (i == pos_row && j == pos_col) {
				putchar('<');
				putchar(ch);
				putchar('>');
			} else {
				putchar(' ');
				putchar(ch);
				putchar(' ');
			}
		}
		putchar('\n');
	}
	putchar('\n');
}

static	void	show_help		(void)
{
	switch (board.state) {
	case GAME_READY:
		show_help_ready();
		break;

	case GAME_PLAYING:
		show_help_playing();
		break;

	case GAME_PAUSE:
		show_help_pause();
		break;

	case GAME_XYZZY:
		show_help_xyzzy();
		break;

	case GAME_CHEATED:
		show_help_cheated();
		break;

	case GAME_WIN:
	case GAME_OVER:
		show_help_end();
		break;
	}
}

static	void	show_help_ready		(void)
{
	puts("Move:");
	/* hjkl */
	printf(" %c", 'h');
	printf(" %c", 'j');
	printf(" %c", 'k');
	printf(" %c", 'l');
	putchar('\n');
	/* Arrows */
	printf(" %c", '<');
	printf(" %c", 'v');
	printf(" %c", '^');
	printf(" %c", '>');
	putchar('\n');

	puts("Step:");
	printf(" %c\n", '+');

	puts("Save:");
	printf(" %c\n", 's');

	puts("Quit:");
	printf(" %c\n", 'q');

	puts("Confirm:");
	printf(" Enter\n");
}

static	void	show_help_playing	(void)
{
	puts("Move:");
	/* hjkl */
	printf(" %c", 'h');
	printf(" %c", 'j');
	printf(" %c", 'k');
	printf(" %c", 'l');
	putchar('\n');
	/* Arrows */
	printf(" %c", '<');
	printf(" %c", 'v');
	printf(" %c", '^');
	printf(" %c", '>');
	putchar('\n');

	puts("Step:");
	printf(" %c\n", '+');

	puts("Flag:");
	printf(" Space\n");

	puts("Possible:");
	printf(" %c\n", 'f');

	puts("rm flag:");
	printf(" Backspace\n");

	puts("Pause:");
	printf(" %c\n", 'p');

	puts("Save:");
	printf(" %c\n", 's');

	puts("Quit:");
	printf(" %c\n", 'q');

	puts("Confirm:");
	printf(" Enter\n");
}

static	void	show_help_pause		(void)
{

	puts("Continue:");
	printf(" %c\n", 'p');

	puts("Save:");
	printf(" %c\n", 's');

	puts("Quit:");
	printf(" %c\n", 'q');

	puts("Confirm:");
	printf(" Enter\n");
}

static	void	show_help_xyzzy		(void)
{
	puts("XYZZY:");
	printf(" %c", '1');
	printf(" %c", '2');
	putchar('\n');

	puts("XYZZY off:");
	printf(" %c\n", '0');

	puts("Move:");
	/* hjkl */
	printf(" %c", 'h');
	printf(" %c", 'j');
	printf(" %c", 'k');
	printf(" %c", 'l');
	putchar('\n');
	/* Arrows */
	printf(" %c", '<');
	printf(" %c", 'v');
	printf(" %c", '^');
	printf(" %c", '>');
	putchar('\n');

	puts("Step:");
	printf(" %c\n", '+');

	puts("Flag:");
	printf(" Space\n");

	puts("Possible:");
	printf(" %c\n", 'f');

	puts("rm flag:");
	printf(" Backspace\n");

	puts("Save:");
	printf(" %c\n", 's');

	puts("Quit:");
	printf(" %c\n", 'q');

	puts("Confirm:");
	printf(" Enter\n");
}

static	void	show_help_cheated	(void)
{
	puts("Move:");
	/* hjkl */
	printf(" %c", 'h');
	printf(" %c", 'j');
	printf(" %c", 'k');
	printf(" %c", 'l');
	putchar('\n');
	/* Arrows */
	printf(" %c", '<');
	printf(" %c", 'v');
	printf(" %c", '^');
	printf(" %c", '>');
	putchar('\n');

	puts("Step:");
	printf(" %c\n", '+');

	puts("Flag:");
	printf(" Space\n");

	puts("Possible:");
	printf(" %c\n", 'f');

	puts("rm flag:");
	printf(" Backspace\n");

	puts("Save:");
	printf(" %c\n", 's');

	puts("Quit:");
	printf(" %c\n", 'q');

	puts("Confirm:");
	printf(" Enter\n");
}

static	void	show_help_end		(void)
{
	puts("Quit:");
	printf(" %c\n", 'q');

	puts("Confirm:");
	printf(" Enter\n");
}
