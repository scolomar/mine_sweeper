/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

	#include <math.h>
	#include <ncurses.h>
	#include <stdbool.h>
	#include <stdlib.h>

	#include "alx_ncur.h"

	#include "about.h"
	#include "data.h"
	#include "start.h"

	#include "tui.h"


	/*
	 * + Menu:
	 *	+ Continue:
	 *		- Start
	 *		+ Select map:
	 *			- New map
	 *			- Load map("path
	 *			- ..
	 *		+ Change difficulty:
	 *			- Change rows: rows		(XX)
	 *			- Change columns: cols		(XX)
	 *			- Change proportion of mines: p	(XX.XXXXXX)
	 *			- ..
	 *		- Change file name (File: "<file_name>")
	 *		+ DEVEL:
	 *			- Change seed (srand)
	 *			x Change verbose
	 *			- ..
	 *		- ..
	 *	- Disclaimer of warranty
	 *	- Terms and conditions
	 *	- Exit program
	 */


/******************************************************************************
 ******| submenus |************************************************************
 ******************************************************************************/
static	void	menu_continue	(void);
static	void	menu_select	(void);
static	void	menu_difficulty	(void);
static	void	menu_devel	(void);
static	void	menu_verbose	(void);


/******************************************************************************
 ******| main menu |***********************************************************
 ******************************************************************************/
void	menu_main		(void)
{
	int	sw;
	bool	wh;
	int	h =	10;
	int	w =	34;

	int		N = 4;
	struct alx_optn	mnu[4] =	{
		{7, 4, "[0]	Exit program"},
		{2, 4, "[1]	Continue"},
		{4, 4, "[2]	Disclaimer of warranty"},
		{5, 4, "[3]	Terms and conditions"}
	};

	flag_s =	START_NEW;

	wh = true;
	while (wh) {
		sw =	alx_menu(h, w, N, mnu, "MENU:");

		switch (sw) {
		case 0:
			wh = false;
			break;

		case 1:
			menu_continue();
			break;

		case 2:
			alx_pause_curses();
			print_disclaim();
			getchar();
			alx_resume_curses();
			break;

		case 3:
			alx_pause_curses();
			print_license();
			getchar();
			alx_resume_curses();
			break;
		}
	}
}


/******************************************************************************
 ******| submenus |************************************************************
 ******************************************************************************/
static	void	menu_continue	(void)
{
	int	sw;
	bool	wh;
	WINDOW		*win;
	int	h =	17;
	int	w =	50;
	int	r =	1;
	int	c =	(80 - w) / 2;

	int	w2 =	w - 8;
	int	r2 =	r + h - 5;

	int		N = 6;
	struct alx_optn	mnu[6] =	{
		{10, 4, "[0]	Back"},
		{2, 4, "[1]	Start"},
		{4, 4, "[2]	Select map"},
		{5, 4, "[3]	Change difficulty"},
		{6, 4, "[4]	Change file name"},
		{8, 4, "[5]	DEVEL"}
	};

	char	*txt[] =	{"File name:"};

	wh = true;
	while (wh) {
		win =	newwin(h, w, r, c);
		mvwprintw(win, mnu[4].r, mnu[4].c, "%s (File: \"%s\")", mnu[4].t, saved_name);
		wrefresh(win);
		sw =	alx_menu_2(win, N, mnu, "CONTINUE:");

		switch (sw) {
		case 0:
			alx_win_del(win);
			wh = false;
			break;

		case 1:
			alx_win_del(win);
			alx_pause_curses();
			start_switch();
			alx_resume_curses();
			break;

		case 2:
			alx_win_del(win);
			menu_select();
			break;

		case 3:
			alx_win_del(win);
			menu_difficulty();
			break;

		case 4:
			alx_w_getfname(USER_SAVED_DIR, saved_name, w2, r2, txt[0],
					saved_name, NULL);
			alx_win_del(win);
			break;

		case 5:
			alx_win_del(win);
			menu_devel();
			break;
		}
	}
}

static	void	menu_select	(void)
{
	int	sw;
	WINDOW		*win;
	int	h =	9;
	int	w =	70;
	int	r =	1;
	int	c =	(80 - w) / 2;

	int		N = 3;
	struct alx_optn	mnu[3] =	{
		{6, 4, "[0]	Back"},
		{2, 4, "[1]	New map"},
		{4, 4, "[2]	Load map"}
	};

	win =	newwin(h, w, r, c);
	mvwprintw(win, mnu[2].r, mnu[2].c, "%s (File: \"%s\")", mnu[1].t, saved_name);
	wrefresh(win);
	sw =	alx_menu_2(win, N, mnu, "SELECT MAP:");

	alx_win_del(win);

	switch (sw) {
	case 1:
		flag_s =	START_NEW;
		break;

	case 2:
		flag_s =	START_LOAD;
		break;
	}

}

static	void	menu_difficulty	(void)
{

	int	sw;
	bool	wh;
	WINDOW		*win;
	int	h =	16;
	int	w =	76;
	int	r =	1;
	int	c =	(80 - w) / 2;

	int	w2 =	w - 8;
	int	r2 =	r + h - 5;

	int		N = 4;
	struct alx_optn	mnu[4] =	{
		{8, 4, "[0]	Back"},
		{2, 4, "[1]	Change rows:"},
		{4, 4, "[2]	Change columns:"},
		{6, 4, "[3]	Change proportion of mines:"}
	};

	char	*txt[] =	{
		"Rows:",
		"Columns:",
		"Proportion:"
	};

	wh = true;
	while (wh) {
		win =	newwin(h, w, r, c);
		mvwprintw(win, mnu[1].r, mnu[1].c, "%s rows\t\t(%i)", mnu[1].t, board.rows);
		mvwprintw(win, mnu[2].r, mnu[2].c, "%s cols\t\t(%i)", mnu[2].t, board.cols);
		mvwprintw(win, mnu[3].r, mnu[3].c, "%s p\t(%lf)", mnu[3].t, board.p);
		wrefresh(win);
		sw =	alx_menu_2(win, N, mnu, "Difficulty:");

		switch (sw) {
		case 0:
			wh = false;
			break;

		case 1:
			board.rows =	alx_w_getint(w2, r2, txt[sw - 1],
						2, board.rows, ROWS_MAX, NULL);
			break;

		case 2:
			board.cols =	alx_w_getint(w2, r2, txt[sw - 1],
						2, board.cols, COLS_MAX, NULL);
			break;

		case 3:
			board.p =	alx_w_getdbl(w2, r2, txt[sw - 1],
						0, board.p, 1, NULL);
			break;
		}

		alx_win_del(win);
	}
}

static	void	menu_devel	(void)
{
	int	sw;
	bool	wh;
	WINDOW		*win;
	int	h =	12;
	int	w =	50;
	int	r =	1;
	int	c =	(80 - w) / 2;

	int	w2 =	w - 8;
	int	r2 =	r + h - 5;

	int		N = 3;
	struct alx_optn	mnu[3] =	{
		{5, 4, "[0]	Back"},
		{2, 4, "[1]	Change seed (srand)"},
		{3, 4, "[-]	Change verbose"}
	};

	char	*txt[] =	{"Seed:"};

	wh = true;
	while (wh) {
		win =	newwin(h, w, r, c);
		mvwprintw(win, mnu[2].r, mnu[2].c, "%s (V = %i)", mnu[2].t, flag_V);
		wrefresh(win);
		sw =	alx_menu_2(win, N, mnu, "DEVELOPER OPTIONS:");

		switch (sw) {
		case 0:
			alx_win_del(win);
			wh = false;
			break;

		case 1:
			seed =	alx_w_getint(w2, r2, txt[0],
					-INFINITY, 1, INFINITY, NULL);
			srand(seed);
			alx_win_del(win);
			break;

		case 2:
/* Not yet */
			alx_win_del(win);
//			menu_verbose();
			break;
		}
	}
}

static	void	menu_verbose	(void)
{
/*
	int	h =	10;
	int	w =	51;

	int		N = 5;
	struct alx_optn	mnu[5] =	{
		{7, 4, "[0]	Show NOTHING"},
		{2, 4, "[1]	Show only time"},
		{3, 4, "[2]	Show WORST time, matrix and solution"},
		{4, 4, "[3]	Show time, matrix and solution"},
# if (DBG)
		{5, 4, "[4]	Show everything  (DBG)"}
# else
		{5, 4, "[4]	DBG (Not active)"}
# endif
	};

	flag_V =	alx_menu(h, w, N, mnu, "VERBOSE: //Not yet//");
*/
}


