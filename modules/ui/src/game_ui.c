/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

		/* WINDOW & wgetch() & KEY_... & ... */
	#include <ncursesw/ncurses.h>
		/* sprintf() */
	#include <stdio.h>
		/* clock_t & clock() & CLOCKS_PER_SEC */
	#include <time.h>
		/* wchar_t */
	#include <wchar.h>

		/* alx_..._curses() & alx_ncur_prn_...() */
	#include "alx_ncur.h"

		/* board & macros */
	#include "data.h"
		/* game_action() & game_state() */
	#include "game.h"
		/* show_board() */
	#include "print.h"

	#include "game_ui.h"


	# define	TITLE_SIZE	(20)


/******************************************************************************
 ******| static |**************************************************************
 ******************************************************************************/
static	int	usr_input		(WINDOW *win);
static	void	show_char		(WINDOW *win, int row, int col,
					wchar_t ch);
static	void	show_board		(WINDOW *win, int pos_row, int pos_col);
static	wchar_t	board_char		(int row, int col);
static	void	board_loop		(WINDOW *win);
static	void	show_help		(WINDOW *win);


/******************************************************************************
 ******| main |****************************************************************
 ******************************************************************************/
void	game_ui			(void)
{
	alx_resume_curses();

	/* Dimensions: board */
	WINDOW		*win_board;
	const int	h1 =	board.rows + 2;
	const int	w1 =	2 * board.cols + 3;
	const int	r1 =	0;
	const int	c1 =	10;
	win_board =	newwin(h1, w1, r1, c1);

	/* Dimensions: help */
	WINDOW		*win_help;
	const int	h2 =	24;
	const int	w2 =	10;
	const int	r2 =	0;
	const int	c2 =	0;
	win_help =	newwin(h2, w2, r2, c2);
	show_help(win_help);

	/* Activate keypad, and don't echo input */
	keypad(win_board, true);
	noecho();

	/* Board position */
	int	pos_row;
	int	pos_col;
	pos_row =	0;
	pos_col =	0;

	/* User action */
	int	action;

	/* Game loop */
	while (board.state != GAME_QUIT) {
		show_board(win_board, pos_row, pos_col);
		action = usr_input(win_board);
		game_action(action, &pos_row, &pos_col);
		game_update_time();
	}

	/* Wait for any key & del win */
	wgetch(win_board);
	alx_win_del(win_board);
	alx_win_del(win_help);

	alx_pause_curses();
}


/******************************************************************************
 ******| static |**************************************************************
 ******************************************************************************/
static	int	usr_input		(WINDOW *win)
{
	wchar_t	ch;
	ch = wgetch(win);

	int	action;

	switch (ch) {
	case KEY_UP:
		action =	ACT_MOVE_UP;
		break;

	case KEY_DOWN:
		action =	ACT_MOVE_DOWN;
		break;

	case KEY_RIGHT:
		action =	ACT_MOVE_RIGHT;
		break;

	case KEY_LEFT:
		action =	ACT_MOVE_LEFT;
		break;

	case '\r':
		action =	ACT_STEP;
		break;

	case ' ':
		action =	ACT_FLAG;
		break;

	case 'd':
		action =	ACT_FLAG_POSSIBLE;
		break;

		/* ASCII 0x08 is BS */
	case KEY_BACKSPACE:
	case 0x08:
		action =	ACT_RM_FLAG;
		break;

	case KEY_BREAK:
	case 'p':
		action =	ACT_PAUSE;
		break;

	case 's':
		action =	ACT_SAVE;
		break;

	case 'x':
		ch = wgetch(win);
		if (ch == 'y') {
			ch = wgetch(win);
			if (ch == 'z') {
				ch = wgetch(win);
				if (ch == 'z') {
					ch = wgetch(win);
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
		action =	ACT_XYZZY_SQ;
		break;

	case 'q':
		action =	ACT_QUIT;
		break;
	}

	return	action;
}

static	void	show_board		(WINDOW *win, int pos_row, int pos_col)
{
	/* Clear & box */
	wclear(win);
	box(win, 0, 0);

	/* Title */
	char	tit[TITLE_SIZE];
	switch (board.state) {
	case GAME_READY:
	case GAME_XYZZY:
	case GAME_CHEATED:
	case GAME_PLAYING:
		sprintf(tit, "Mines: %i/%i", board.flags, board.mines);
		break;

	case GAME_OVER:
		sprintf(tit, "GAME OVER");
		break;

	case GAME_WIN:
		sprintf(tit, "You win!");
		break;
	}
	alx_ncur_prn_title(win, tit);

	/* Subtitle */
	char	subtit[TITLE_SIZE];
	int	mins;
	int	secs;
	if (board.time != CHEATED) {
		mins =	(int)(board.time / 60);
		secs =	((int)board.time % 60);
		sprintf(subtit, "%i:%02i | %i", mins, secs, board.clicks);
		alx_ncur_prn_subtitle(win, subtit);
	}

	/* Board */
	board_loop(win);
	wmove(win, 1 + pos_row, 2 + 2 * pos_col);
	wrefresh(win);
}

static	void	board_loop	(WINDOW *win)
{
	int	i;
	int	j;
	int	k;
	int	l;

	for (i = 0; i < board.rows; i++) {
		k =	1 + i;

		/* clear */
		for (j = 0; j < board.cols; j++) {
			l =	2 + 2 * j;
			wchar_t		ch;
			if (board.usr[i][j] == USR_CLEAR) {
				ch =	board_char(i, j);
				show_char(win, k, l, ch);
			}
		}
		/* xyzzy */
		/* hidden */
		for (j = 0; j < board.cols; j++) {
			l =	2 + 2 * j;
			wchar_t		ch;
			if (board.usr[i][j] != USR_CLEAR) {
				ch =	board_char(i, j);
				show_char(win, k, l, ch);
			}
		}
		/* kboom */
		for (j = 0; j < board.cols; j++) {
			l =	2 + 2 * j;
			wchar_t		ch;
			if (board.usr[i][j] == KBOOM) {
				ch =	board_char(i, j);
				show_char(win, k, l, ch);
			}
		}
	}
	wrefresh(win);
}

static	wchar_t	board_char	(int row, int col)
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

static	void	show_char	(WINDOW *win, int row, int col, wchar_t ch)
{
	/* Select attributes */
	int	pair;
	switch (ch) {
	case '1':
		pair =	PAIR_1;
		break;

	case '2':
		pair =	PAIR_2;
		break;

	case '3':
		pair =	PAIR_3;
		break;

	case '4':
		pair =	PAIR_4;
		break;

	case '5':
		pair =	PAIR_5;
		break;

	case '6':
		pair =	PAIR_6;
		break;

	case '7':
		pair =	PAIR_7;
		break;

	case '8':
		pair =	PAIR_8;
		break;

	case ' ':
		pair =	PAIR_BLANK;
		break;

	case '*':
	case 'v':
		pair =	PAIR_MINE;
		break;

	case '+':
	case '-':
		pair =	PAIR_HIDDEN;
		break;

	case 'f':
		pair =	PAIR_fail;
		break;

	case '?':
		pair =	PAIR_POSSIBLE;
		break;

	case 'F':
		pair =	PAIR_FAIL;
		break;

	case '!':
		pair =	PAIR_FLAG;
		break;

	case '#':
		pair =	PAIR_KBOOM;
		break;

	default:
		pair =	PAIR_KBOOM;
		break;
	}

	/* Print char */
	if (flag_color) {
		wattron(win, A_BOLD | COLOR_PAIR(pair));
	}
	mvwaddch(win, row, col - 1, ' ');
	mvwaddch(win, row, col, ch);
	mvwaddch(win, row, col + 1, ' ');
	if (flag_color) {
		wattroff(win, A_BOLD | COLOR_PAIR(pair));
	}
	wrefresh(win);
}

static	void	show_help		(WINDOW *win)
{
	mvwaddstr(win, 0, 0, "Move:");
	mvwaddch(win, 1, 1, ACS_UARROW);
	mvwaddch(win, 1, 3, ACS_DARROW);
	mvwaddch(win, 1, 5, ACS_RARROW);
	mvwaddch(win, 1, 7, ACS_LARROW);
	mvwaddstr(win, 3, 0, "Step:");
	mvwprintw(win, 4, 1, "Enter");
	mvwaddstr(win, 6, 0, "Flag:");
	mvwprintw(win, 7, 1, "Space");
	mvwaddstr(win, 9, 0, "Possible:");
	mvwprintw(win, 10, 1, "%c", 'd');
	mvwaddstr(win, 12, 0, "rm flag:");
	mvwprintw(win, 13, 1, "Backspace");
	mvwaddstr(win, 15, 0, "Pause:");
	mvwprintw(win, 16, 1, "Break / %c", 'p');
	mvwaddstr(win, 18, 0, "Save:");
	mvwprintw(win, 19, 1, "%c", 's');
	mvwaddstr(win, 21, 0, "Quit:");
	mvwprintw(win, 22, 1, "%c", 'q');
	wrefresh(win);
}
