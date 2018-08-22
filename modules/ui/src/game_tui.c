/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

		/* WINDOW & wgetch() & KEY_... & ... */
	#include <ncursesw/ncurses.h>
		/* sprintf() */
	#include <stdio.h>
		/* wchar_t */
	#include <wchar.h>

		/* alx_..._curses() & alx_ncur_prn_...() */
	#include "alx_ncur.h"

		/* board & macros */
	#include "data.h"

	#include "game_tui.h"


	# define	TITLE_SIZE	(20)


/******************************************************************************
 ******| static |**************************************************************
 ******************************************************************************/
static	WINDOW	*win_board;
static	WINDOW	*win_help;


static	int	usr_input		(WINDOW *win);

static	void	show_board		(WINDOW *win, int pos_row, int pos_col);
static	void	board_loop		(WINDOW *win);
static	void	show_char		(WINDOW *win, int row, int col,
					wchar_t ch);

static	void	show_help		(WINDOW *win);
static	void	show_help_ready		(WINDOW *win);
static	void	show_help_playing	(WINDOW *win);
static	void	show_help_pause		(WINDOW *win);
static	void	show_help_xyzzy		(WINDOW *win);
static	void	show_help_cheated	(WINDOW *win);
static	void	show_help_end		(WINDOW *win);

static	void	highlight_cursor	(void);


/******************************************************************************
 ******| main |****************************************************************
 ******************************************************************************/
void	game_tui_init			(void)
{
	/* Use curses mode */
	alx_resume_curses();

	/* Dimensions: board */
	const int	h1 =	board.rows + 2;
	const int	w1 =	2 * board.cols + 3;
	const int	r1 =	0;
	const int	c1 =	11;
	win_board =	newwin(h1, w1, r1, c1);

	/* Dimensions: help */
	const int	h2 =	24;
	const int	w2 =	10;
	const int	r2 =	0;
	const int	c2 =	0;
	win_help =	newwin(h2, w2, r2, c2);

	/* Activate keypad, don't echo input, and set timeout=30ms */
	keypad(win_board, true);
	noecho();
	wtimeout(win_board, 100);
}

int	game_tui			(int pos_row, int pos_col)
{
	int	action;

	show_help(win_help);
	show_board(win_board, pos_row, pos_col);
	action = usr_input(win_board);

	return	action;
}

void	game_tui_cleanup		(void)
{
	/* Del wins & return to terminal mode */
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
	case 'k':
		action =	ACT_MOVE_UP;
		break;

	case KEY_DOWN:
	case 'j':
		action =	ACT_MOVE_DOWN;
		break;

	case KEY_RIGHT:
	case 'l':
		action =	ACT_MOVE_RIGHT;
		break;

	case KEY_LEFT:
	case 'h':
		action =	ACT_MOVE_LEFT;
		break;

	case '+':
	case '\r':
	case '\n':
		action =	ACT_STEP;
		break;

	case ' ':
		action =	ACT_FLAG;
		break;

	case 'f':
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

	case 'c':
		highlight_cursor();
		action =	ACT_FOO;
		break;

	default:
		action =	ACT_FOO;
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
	alx_ncur_prn_title(win, tit);

	/* Subtitle */
	char	subtit[TITLE_SIZE];
	int	hours;
	int	mins;
	int	secs;
	if (board.time != CHEATED) {
		hours =	((int)board.time / 3600);
		mins =	(((int)board.time % 3600) / 60);
		secs =	((int)board.time % 60);

		if (board.time >= 3600) {
			sprintf(subtit, "%02i:%02i:%02i | %i", hours, mins, secs, board.clicks);
		} else {
			sprintf(subtit, "%02i:%02i | %i", mins, secs, board.clicks);
		}

		alx_ncur_prn_subtitle(win, subtit);
	}

	/* Board */
	board_loop(win);

	/* Highlight cursor */
	if (highlight) {
		show_char(win, 1 + pos_row, 2 + 2 * pos_col, 'c');
	}
	wmove(win, 1 + pos_row, 2 + 2 * pos_col);

	/* Refresh */
	wrefresh(win);
}

static	void	board_loop		(WINDOW *win)
{
	int	i;
	int	j;
	int	k;
	int	l;
	wchar_t	ch;

	for (i = 0; i < board.rows; i++) {
		k =	1 + i;

		/* clear */
		for (j = 0; j < board.cols; j++) {
			l =	2 + 2 * j;
			if (board.usr[i][j] == USR_CLEAR) {
				ch =	board.visible[i][j];
				show_char(win, k, l, ch);
			}
		}
		/* xyzzy */
		/* hidden */
		for (j = 0; j < board.cols; j++) {
			l =	2 + 2 * j;
			if (board.usr[i][j] != USR_CLEAR) {
				ch =	board.visible[i][j];
				show_char(win, k, l, ch);
			}
		}
		/* kboom */
		for (j = 0; j < board.cols; j++) {
			l =	2 + 2 * j;
			if (board.usr[i][j] == KBOOM) {
				ch =	board.visible[i][j];
				show_char(win, k, l, ch);
			}
		}
	}
	/* Refresh */
	wrefresh(win);
}

static	void	show_char		(WINDOW *win, int row, int col, wchar_t ch)
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

	case 'c':
		pair =	PAIR_HILITE;
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
	/* Clear */
	wclear(win);

	switch (board.state) {
	case GAME_READY:
		show_help_ready(win);
		break;

	case GAME_PLAYING:
		show_help_playing(win);
		break;

	case GAME_PAUSE:
		show_help_pause(win);
		break;

	case GAME_XYZZY:
		show_help_xyzzy(win);
		break;

	case GAME_CHEATED:
		show_help_cheated(win);
		break;

	case GAME_WIN:
	case GAME_OVER:
		show_help_end(win);
		break;
	}
}

static	void	show_help_ready		(WINDOW *win)
{
	int	r;
	int	c;

	r =	0;
	c =	0;
	mvwaddstr(win, r++, c++, "Move:");
	/* hjkl */
	mvwaddch(win, r, c, 'h');
	c += 2;
	mvwaddch(win, r, c, 'j');
	c += 2;
	mvwaddch(win, r, c, 'k');
	c += 2;
	mvwaddch(win, r, c, 'l');
	/* Arrows */
	r++;
	c = 1;
	mvwaddch(win, r, c, ACS_LARROW);
	c += 2;
	mvwaddch(win, r, c, ACS_DARROW);
	c += 2;
	mvwaddch(win, r, c, ACS_UARROW);
	c += 2;
	mvwaddch(win, r, c, ACS_RARROW);

	r++;
	c = 0;
	mvwaddstr(win, r++, c, "Cursor:");
	mvwprintw(win, r++, c, " %c", 'c');

	mvwaddstr(win, r++, c, "Step:");
	mvwprintw(win, r++, c, " Enter / %c", '+');

	mvwaddstr(win, r++, c, "Save:");
	mvwprintw(win, r++, c, " %c", 's');

	mvwaddstr(win, r++, c, "Quit:");
	mvwprintw(win, r++, c, " %c", 'q');

	wrefresh(win);
}

static	void	show_help_playing	(WINDOW *win)
{
	int	r;
	int	c;

	r =	0;
	c =	0;
	mvwaddstr(win, r++, c++, "Move:");
	/* hjkl */
	mvwaddch(win, r, c, 'h');
	c += 2;
	mvwaddch(win, r, c, 'j');
	c += 2;
	mvwaddch(win, r, c, 'k');
	c += 2;
	mvwaddch(win, r, c, 'l');
	/* Arrows */
	r++;
	c = 1;
	mvwaddch(win, r, c, ACS_LARROW);
	c += 2;
	mvwaddch(win, r, c, ACS_DARROW);
	c += 2;
	mvwaddch(win, r, c, ACS_UARROW);
	c += 2;
	mvwaddch(win, r, c, ACS_RARROW);

	r++;
	c = 0;
	mvwaddstr(win, r++, c, "Cursor:");
	mvwprintw(win, r++, c, " %c", 'c');

	mvwaddstr(win, r++, c, "Step:");
	mvwprintw(win, r++, c, " Enter / %c", '+');

	mvwaddstr(win, r++, c, "Flag:");
	mvwprintw(win, r++, c, " Space");

	mvwaddstr(win, r++, c, "Possible:");
	mvwprintw(win, r++, c, " %c", 'f');

	mvwaddstr(win, r++, c, "rm flag:");
	mvwprintw(win, r++, c, " Backspace");

	mvwaddstr(win, r++, c, "Pause:");
	mvwprintw(win, r++, c, " Break / %c", 'p');

	mvwaddstr(win, r++, c, "Save:");
	mvwprintw(win, r++, c, " %c", 's');

	mvwaddstr(win, r++, c, "Quit:");
	mvwprintw(win, r++, c, " %c", 'q');

	wrefresh(win);
}

static	void	show_help_pause		(WINDOW *win)
{
	int	r;
	int	c;

	r =	0;
	c =	0;
	mvwaddstr(win, r++, c, "Cursor:");
	mvwprintw(win, r++, c, " %c", 'c');

	mvwaddstr(win, r++, c, "Continue:");
	mvwprintw(win, r++, c, " Break / %c", 'p');

	mvwaddstr(win, r++, c, "Save:");
	mvwprintw(win, r++, c, " %c", 's');

	mvwaddstr(win, r++, c, "Quit:");
	mvwprintw(win, r++, c, " %c", 'q');

	wrefresh(win);
}

static	void	show_help_xyzzy		(WINDOW *win)
{
	int	r;
	int	c;

	r =	0;
	c =	0;
	mvwaddstr(win, r++, c++, "XYZZY:");
	mvwprintw(win, r, c, "%c", '1');
	c += 2;
	mvwprintw(win, r, c, "%c", '2');
//	c += 2;
//	mvwprintw(win, r, c, "%c", 'd');

	r++;
	c = 0;
	mvwaddstr(win, r++, c, "XYZZY off:");
	mvwprintw(win, r++, c, " %c", '0');

	mvwaddstr(win, r++, c++, "Move:");
	/* hjkl */
	mvwaddch(win, r, c, 'h');
	c += 2;
	mvwaddch(win, r, c, 'j');
	c += 2;
	mvwaddch(win, r, c, 'k');
	c += 2;
	mvwaddch(win, r, c, 'l');
	/* Arrows */
	r++;
	c = 1;
	mvwaddch(win, r, c, ACS_LARROW);
	c += 2;
	mvwaddch(win, r, c, ACS_DARROW);
	c += 2;
	mvwaddch(win, r, c, ACS_UARROW);
	c += 2;
	mvwaddch(win, r, c, ACS_RARROW);

	r++;
	c = 0;
	mvwaddstr(win, r++, c, "Cursor:");
	mvwprintw(win, r++, c, " %c", 'c');

	mvwaddstr(win, r++, c, "Step:");
	mvwprintw(win, r++, c, " Enter / %c", '+');

	mvwaddstr(win, r++, c, "Flag:");
	mvwprintw(win, r++, c, " Space");

	mvwaddstr(win, r++, c, "Possible:");
	mvwprintw(win, r++, c, " %c", 'f');

	mvwaddstr(win, r++, c, "rm flag:");
	mvwprintw(win, r++, c, " Backspace");

	mvwaddstr(win, r++, c, "Save:");
	mvwprintw(win, r++, c, " %c", 's');

	mvwaddstr(win, r++, c, "Quit:");
	mvwprintw(win, r++, c, " %c", 'q');

	wrefresh(win);
}

static	void	show_help_cheated	(WINDOW *win)
{
	int	r;
	int	c;

	r =	0;
	c =	0;
	mvwaddstr(win, r++, c++, "Move:");
	/* hjkl */
	mvwaddch(win, r, c, 'h');
	c += 2;
	mvwaddch(win, r, c, 'j');
	c += 2;
	mvwaddch(win, r, c, 'k');
	c += 2;
	mvwaddch(win, r, c, 'l');
	/* Arrows */
	r++;
	c = 1;
	mvwaddch(win, r, c, ACS_LARROW);
	c += 2;
	mvwaddch(win, r, c, ACS_DARROW);
	c += 2;
	mvwaddch(win, r, c, ACS_UARROW);
	c += 2;
	mvwaddch(win, r, c, ACS_RARROW);

	r++;
	c = 0;
	mvwaddstr(win, r++, c, "Cursor:");
	mvwprintw(win, r++, c, " %c", 'c');

	mvwaddstr(win, r++, c, "Step:");
	mvwprintw(win, r++, c, " Enter / %c", '+');

	mvwaddstr(win, r++, c, "Flag:");
	mvwprintw(win, r++, c, " Space");

	mvwaddstr(win, r++, c, "Possible:");
	mvwprintw(win, r++, c, " %c", 'f');

	mvwaddstr(win, r++, c, "rm flag:");
	mvwprintw(win, r++, c, " Backspace");

	mvwaddstr(win, r++, c, "Save:");
	mvwprintw(win, r++, c, " %c", 's');

	mvwaddstr(win, r++, c, "Quit:");
	mvwprintw(win, r++, c, " %c", 'q');

	wrefresh(win);
}

static	void	show_help_end		(WINDOW *win)
{
	int	r;
	int	c;

	r =	0;
	c =	0;
	mvwaddstr(win, r++, c, "Quit:");
	mvwprintw(win, r++, c, " %c", 'q');

	wrefresh(win);
}

static	void	highlight_cursor	(void)
{
	highlight =	!highlight;
}
