/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/


		/* clock_t & clock() & CLOCKS_PER_SEC */
	#include <time.h>
		/* wchar_t */
	#include <wchar.h>

		/* board & macros */
	#include "data.h"
		/* game_action() & game_state() & game_update_time() */
	#include "game.h"
		/* game_tui() */
	#include "game_clui.h"
		/* game_tui() */
	#include "game_tui.h"

	#include "game_iface.h"


/******************************************************************************
 ******| static |**************************************************************
 ******************************************************************************/
static	void	game_iface_visible_board	(void);
static	wchar_t	board_char			(int row, int col);


/******************************************************************************
 ******| main |****************************************************************
 ******************************************************************************/
void	game_iface	(void)
{
	/* Board position */
	int	pos_row;
	int	pos_col;
	pos_row =	0;
	pos_col =	0;

	/* User action */
	int	action;

	/* Game loop */
	while (board.state != GAME_QUIT) {
		game_iface_visible_board();
		switch (flag_iface) {
		case IFACE_CLUI:
			action	= game_clui(action, pos_row, pos_col);
			break;

		case IFACE_TUI:
			action	= game_tui(pos_row, pos_col);
			break;
		}
		game_action(action, &pos_row, &pos_col);
		game_update_time();
	}
}


/******************************************************************************
 ******| static |**************************************************************
 ******************************************************************************/
static	void	game_iface_visible_board	(void)
{
	int	i;
	int	j;
	wchar_t	ch;

	for (i = 0; i < board.rows; i++) {
		for (j = 0; j < board.cols; j++) {
			ch =	board_char(i, j);
			board.visible[i][j] =	ch;
		}
	}
}

static	wchar_t	board_char			(int row, int col)
{
	wchar_t	ch;

	switch (board.state) {
	case GAME_READY:
		switch (board.usr[row][col]) {
		case USR_HIDDEN:
			ch =	'+';
			break;

		case USR_FLAG:
			ch =	'!';
			break;

		case USR_POSSIBLE:
			ch =	'?';
			break;
		}
		break;

	case GAME_CHEATED:
	case GAME_XYZZY:
	case GAME_PLAYING:
		switch (board.usr[row][col]) {
		case USR_HIDDEN:
			ch =	'+';
			break;
		case USR_CLEAR:
			if (board.gnd[row][col] == MINE_NO) {
				ch =	' ';
			} else {
				ch =	'0' + board.gnd[row][col];
			}
			break;
		case USR_FLAG:
			ch =	'!';
			break;
		case USR_POSSIBLE:
			ch =	'?';
			break;
		}
		break;

	case GAME_WIN:
		switch (board.usr[row][col]) {
		case USR_HIDDEN:
			ch =	'v';
			break;

		case USR_CLEAR:
			if (board.gnd[row][col] == MINE_NO) {
				ch =	' ';
			} else {
				ch =	'0' + board.gnd[row][col];
			}
			break;

		case USR_FLAG:
			ch =	'!';
			break;

		case USR_POSSIBLE:
			ch =	'?';
			break;
		}
		break;

	case GAME_OVER:
		switch (board.usr[row][col]) {
		case KBOOM:
			ch =	'#';
			break;

		case USR_HIDDEN:
			if (board.gnd[row][col] >= MINE_YES) {
				ch =	'*';
			} else {
				ch =	'-';
			}
			break;

		case USR_CLEAR:
			if (board.gnd[row][col] == MINE_NO) {
				ch =	' ';
			} else {
				ch =	'0' + board.gnd[row][col];
			}
			break;

		case USR_FLAG:
			if (board.gnd[row][col] >= MINE_YES) {
				ch =	'!';
			} else {
				ch =	'F';
			}
			break;

		case USR_POSSIBLE:
			if (board.gnd[row][col] >= MINE_YES) {
				ch =	'*';
			} else {
				ch =	'f';
			}
			break;
		}
		break;

	default:
		ch =	'0';
		break;
	}

	return	ch;
}
