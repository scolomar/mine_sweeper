/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/


/******************************************************************************
 ******* headers **************************************************************
 ******************************************************************************/
/*	*	*	*	*	*	*	*	*	*
 *	*	* Standard	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
	#include <stdbool.h>
		/* sprintf() */
	#include <stdio.h>
	#include <wchar.h>

/*	*	*	*	*	*	*	*	*	*
 *	*	* Other	*	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
		/* struct Game_Iface_Out */
	#include "game_iface.h"

		/* struct Player_Iface_Position */
	#include "player_iface.h"

	#include "player_clui.h"


/******************************************************************************
 ******* macros ***************************************************************
 ******************************************************************************/
	# define	BUFF_SIZE	(1024)


/******************************************************************************
 ******* variables ************************************************************
 ******************************************************************************/
static	int	oldaction;


/******************************************************************************
 ******* static functions *****************************************************
 ******************************************************************************/
	/* Start */
static	void	show_board_start(const struct Player_Iface_Position	*position,
				const char				*title,
				const char				*subtitle);

static	void	board_loop_start(const struct Player_Iface_Position	*position);

	/* Play */
static	void	show_board	(const struct Game_Iface_Out		*board,
				const struct Player_Iface_Position	*position,
				const char				*title,
				const char				*subtitle);

static	void	board_loop	(const struct Game_Iface_Out		*board,
				const struct Player_Iface_Position	*position);

static	char	set_char	(int game_iface_visible);
	/* Input */
static	int	usr_input	(void);
	/* Help */
static	void	show_help		(const struct Game_Iface_Out	*board);
static	void	show_help_start		(void);
static	void	show_help_play		(void);
static	void	show_help_pause		(void);
static	void	show_help_xyzzy		(void);
static	void	show_help_cheat		(void);
static	void	show_help_safe		(void);
static	void	show_help_gameover	(void);


/******************************************************************************
 ******* main *****************************************************************
 ******************************************************************************/
void	player_clui_start	(const struct Player_Iface_Position	*position,
				const char				*title,
				const char				*subtitle,
				int					*action)
{
	/* User action */
	show_help_start();
	show_board_start(position, title, subtitle);

	*action		= usr_input();
	oldaction	= *action;
}

void	player_clui		(const struct Game_Iface_Out		*board,
				const struct Player_Iface_Position	*position,
				const char				*title,
				const char				*subtitle,
				int					*action)
{
	/* User action */


	if (oldaction != PLAYER_IFACE_ACT_FOO) {
		show_help(board);
		show_board(board, position, title, subtitle);
	}
	*action		= usr_input();
	oldaction	= *action;
}

void	player_clui_save_name	(const char *filepath, char *filename)
{
	puts("File name:");
	scanf(" %100c ", filename);
}

void	player_clui_score_name	(char *player_name)
{
	puts("Your name:");
	scanf(" %100c ", player_name);
}


/******************************************************************************
 ******* static functions *****************************************************
 ******************************************************************************/
/*	*	*	*	*	*	*	*	*	*
 *	*	* Start	*	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
static	void	show_board_start(const struct Player_Iface_Position	*position,
				const char				*title,
				const char				*subtitle)
{
	/* Title */
	puts("________________________________________________________________________________");
	puts(title);

	/* Board */
	board_loop_start(position);

	/* Subtitle */
	puts(subtitle);
	puts("--------------------------------------------------------------------------------");
}

static	void	board_loop_start(const struct Player_Iface_Position	*position)
{
	int	i;
	int	j;
	char	ch;

	putchar('\n');
	for (i = 0; i < position->rows; i++) {
		for (j = 0; j < position->cols; j++) {
			ch =	PLAYER_CLUI_CHAR_HIDDEN_FIELD;

			/* Print char */
			if (i == position->row && j == position->col) {
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

/*	*	*	*	*	*	*	*	*	*
 *	*	* Play	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
static	void	show_board	(const struct Game_Iface_Out		*board,
				const struct Player_Iface_Position	*position,
				const char				*title,
				const char				*subtitle)
{
	/* Title */
	puts("________________________________________________________________________________");
	puts(title);

	/* Board */
	board_loop(board, position);

	/* Subtitle */
	puts(subtitle);
	puts("--------------------------------------------------------------------------------");

}

static	void	board_loop	(const struct Game_Iface_Out		*board,
				const struct Player_Iface_Position	*position)
{
	int	i;
	int	j;
	char	ch;

	putchar('\n');
	for (i = 0; i < board->rows; i++) {
		for (j = 0; j < board->cols; j++) {
			ch =	set_char(board->visible[i][j]);

			/* Print char */
			if (i == position->row && j == position->col) {
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

static	char	set_char	(int game_iface_visible)
{
	char	ch;
	switch (game_iface_visible) {
	case GAME_IFACE_VIS_KBOOM:
		ch	= PLAYER_CLUI_CHAR_KBOOM;
		break;

	case GAME_IFACE_VIS_HIDDEN_FIELD:
		ch	= PLAYER_CLUI_CHAR_HIDDEN_FIELD;
		break;

	case GAME_IFACE_VIS_HIDDEN_MINE:
		ch	= PLAYER_CLUI_CHAR_HIDDEN_MINE;
		break;

	case GAME_IFACE_VIS_HIDDEN_SAFE:
		ch	= PLAYER_CLUI_CHAR_HIDDEN_SAFE;
		break;

	case GAME_IFACE_VIS_SAFE_MINE:
		ch	= PLAYER_CLUI_CHAR_SAFE_MINE;
		break;

	case GAME_IFACE_VIS_0:
		ch	= PLAYER_CLUI_CHAR_0;
		break;

	case GAME_IFACE_VIS_1:
		ch	= PLAYER_CLUI_CHAR_1;
		break;

	case GAME_IFACE_VIS_2:
		ch	= PLAYER_CLUI_CHAR_2;
		break;

	case GAME_IFACE_VIS_3:
		ch	= PLAYER_CLUI_CHAR_3;
		break;

	case GAME_IFACE_VIS_4:
		ch	= PLAYER_CLUI_CHAR_4;
		break;

	case GAME_IFACE_VIS_5:
		ch	= PLAYER_CLUI_CHAR_5;
		break;

	case GAME_IFACE_VIS_6:
		ch	= PLAYER_CLUI_CHAR_6;
		break;

	case GAME_IFACE_VIS_7:
		ch	= PLAYER_CLUI_CHAR_7;
		break;

	case GAME_IFACE_VIS_8:
		ch	= PLAYER_CLUI_CHAR_8;
		break;

	case GAME_IFACE_VIS_FLAG:
		ch	= PLAYER_CLUI_CHAR_FLAG;
		break;

	case GAME_IFACE_VIS_FLAG_FALSE:
		ch	= PLAYER_CLUI_CHAR_FLAG_FALSE;
		break;

	case GAME_IFACE_VIS_POSSIBLE:
		ch	= PLAYER_CLUI_CHAR_POSSIBLE;
		break;

	case GAME_IFACE_VIS_POSSIBLE_FALSE:
		ch	= PLAYER_CLUI_CHAR_POSSIBLE_FALSE;
		break;
	}

	return	ch;
}

/*	*	*	*	*	*	*	*	*	*
 *	*	* Input	*	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
static	int	usr_input	(void)
{
	/* Wait for input */
	char	buff [BUFF_SIZE];
	char	ch;
	buff[0]	= '\0';
	ch	= '\0';
	fgets(buff, BUFF_SIZE, stdin);

	/* Interpret input */
	int	action;
	sscanf(buff, "%c", &ch);
	switch (ch) {
		/* Escape sequence */
	case 27:
			/* Arrows */
		sscanf(buff, "%*c""%c", &ch);
		switch (ch) {
		case 91:
			sscanf(buff, "%*2c""%c", &ch);
			switch (ch) {
			case 65:
				action =	PLAYER_IFACE_ACT_MOVE_UP;
				break;

			case 66:
				action =	PLAYER_IFACE_ACT_MOVE_DOWN;
				break;

			case 67:
				action =	PLAYER_IFACE_ACT_MOVE_RIGHT;
				break;

			case 68:
				action =	PLAYER_IFACE_ACT_MOVE_LEFT;
				break;
			}
			break;
		}
		break;

	case 'h':
		action =	PLAYER_IFACE_ACT_MOVE_LEFT;
		break;

	case 'j':
		action =	PLAYER_IFACE_ACT_MOVE_DOWN;
		break;

	case 'k':
		action =	PLAYER_IFACE_ACT_MOVE_UP;
		break;

	case 'l':
		action =	PLAYER_IFACE_ACT_MOVE_RIGHT;
		break;

	case '+':
		action =	PLAYER_IFACE_ACT_STEP;
		break;

	case ' ':
		action =	PLAYER_IFACE_ACT_FLAG;
		break;

	case 'f':
		action =	PLAYER_IFACE_ACT_FLAG_POSSIBLE;
		break;

		/* ASCII 0x08 is BS */
	case 0x7F:
	case 0x08:
		action =	PLAYER_IFACE_ACT_RM_FLAG;
		break;

	case 'p':
		action =	PLAYER_IFACE_ACT_PAUSE;
		break;

	case 's':
		action =	PLAYER_IFACE_ACT_SAVE;
		break;

	case 'x':
		/* Special sequence "xyzzy" */
		sscanf(buff, "%*c""%c", &ch);
		if (ch == 'y') {
			sscanf(buff, "%*2c""%c", &ch);
			if (ch == 'z') {
			sscanf(buff, "%*3c""%c", &ch);
			if (ch == 'z') {
			sscanf(buff, "%*4c""%c", &ch);
			if (ch == 'y') {
				action =	PLAYER_IFACE_ACT_XYZZY_ON;
			}
			}
			}
		}
		break;

	case '0':
		action =	PLAYER_IFACE_ACT_XYZZY_OFF;
		break;

	case '1':
		action =	PLAYER_IFACE_ACT_XYZZY_LIN;
		break;

	case '2':
		action =	PLAYER_IFACE_ACT_XYZZY_P;
		break;

	case '3':
		action =	PLAYER_IFACE_ACT_XYZZY_NP;
		break;

	case 'q':
		action =	PLAYER_IFACE_ACT_QUIT;
		break;

	default:
		action =	PLAYER_IFACE_ACT_FOO;
		break;
	}

	return	action;
}

/*	*	*	*	*	*	*	*	*	*
 *	*	* Help	*	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
static	void	show_help		(const struct Game_Iface_Out	*board)
{
	switch (board->state) {
	case GAME_IFACE_STATE_PLAYING:
		show_help_play();
		break;

	case GAME_IFACE_STATE_PAUSE:
		show_help_pause();
		break;

	case GAME_IFACE_STATE_XYZZY:
		show_help_xyzzy();
		break;

	case GAME_IFACE_STATE_CHEATED:
		show_help_cheat();
		break;

	case GAME_IFACE_STATE_SAFE:
		show_help_safe();
		break;

	case GAME_IFACE_STATE_GAMEOVER:
		show_help_gameover();
		break;
	}
}

static	void	show_help_start		(void)
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

static	void	show_help_play		(void)
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

static	void	show_help_cheat		(void)
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

static	void	show_help_safe		(void)
{
	puts("Save:");
	printf(" %c\n", 's');

	puts("Quit:");
	printf(" %c\n", 'q');

	puts("Confirm:");
	printf(" Enter\n");
}

static	void	show_help_gameover	(void)
{
	puts("Quit:");
	printf(" %c\n", 'q');

	puts("Confirm:");
	printf(" Enter\n");
}


/******************************************************************************
 ******* end of file **********************************************************
 ******************************************************************************/
