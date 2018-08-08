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
	 *		+ Change size:
	 *			- Change rows:
	 *			- Change cloumns:
	 *			- ..
	 *		+ Change proportion of mines:
	 *			- Change proportion of mines:
	 *			- ..
	 *		- Change seed (srand)
	 *		+ Change verbose:
	 *			- Show only time
	 *			- Show WORST time, matrix and solution
	 *			- Show time, matrix and solution
	 *			- Show everything
	 *			- Show NOTHING
	 *		- ..
	 *	- Disclaimer
	 *	- License
	 *	- Exit program
	 */


/******************************************************************************
 ******| submenus |************************************************************
 ******************************************************************************/
static	void	menu_continue	(void);
static	void	menu_difficulty	(void);
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

	flag_s =	2;

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
			alx_resume_curses();
			break;

		case 3:
			alx_pause_curses();
			print_license();
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
	int64_t	w =	50;
	int64_t	r =	1;
	int64_t	c =	(80 - w) / 2;

	int64_t	w2 =	w - 8;
	int64_t	r2 =	r + h - 5;

	int64_t		N = 6;
	struct alx_optn	mnu[6] =	{
		{11, 4, "[0]	Back"},
		{2, 4, "[1]	Start"},
		{4, 4, "[2]	Change difficulty"},
		{5, 4, "[4]	Change file path"},
		{6, 4, "[5]	Change seed (srand)"},
		{7, 4, "[6]	Change verbose"}
	};

	char	*txt[] =	{"File path:",
				"Seed:"};

	wh = true;
	while (wh) {
		win =	newwin(h, w, r, c);
		mvwprintw(win, mnu[5].r, mnu[5].c, "%s (V = %i)", mnu[5].t, flag_V);
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
			menu_difficulty();
			break;

		case 3:
			alx_w_getfpath(file_path, w2, r2, txt[0],
					"files/DATA.txt", NULL);
			break;

		case 4:
			seed =	alx_w_getint(w2, r2, txt[1],
					-INFINITY, 1, INFINITY, NULL);
			srand(seed);
			break;

		case 5:
			alx_win_del(win);
			menu_verbose();
			break;
		}
	}
}

static	void	menu_difficulty	(void)
{

	int64_t	sw;
	bool	wh;
	WINDOW		*win;
	int64_t	h =	16;
	int64_t	w =	76;
	int64_t	r =	1;
	int64_t	c =	(80 - w) / 2;

	int64_t	w2 =	w - 8;
	int64_t	r2 =	r + h - 5;

	int64_t		N = 4;
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
		mvwprintw(win, mnu[1].r, mnu[1].c, "%s rows\t(%i)", mnu[1].t, P_ROWS);
		mvwprintw(win, mnu[2].r, mnu[2].c, "%s cols\t(%i)", mnu[2].t, P_COLS);
		mvwprintw(win, mnu[3].r, mnu[3].c, "%s p\t(%lf)", mnu[3].t, p);
		wrefresh(win);
		sw =	alx_menu_2(win, N, mnu, "Difficulty:");

		switch (sw) {
		case 0:
			wh = false;
			break;

		case 1:
			P_ROWS =	alx_w_getint(w2, r2, txt[sw - 1],
						2, P_ROWS, DIM_MAX, NULL);
			break;

		case 2:
			P_COLS =	alx_w_getint(w2, r2, txt[sw - 1],
						2, P_COLS, DIM_MAX, NULL);
			break;

		case 3:
			p =	alx_w_getdbl(w2, r2, txt[sw - 1],
						0, p, 1, NULL);
			break;
		}

		alx_win_del(win);
	}
}

static	void	menu_verbose	(void)
{
	int64_t	h =	10;
	int64_t	w =	51;

	int64_t		N = 5;
	struct alx_optn	mnu[5] =	{{7, 4, "[0]	Show NOTHING"},
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
}


