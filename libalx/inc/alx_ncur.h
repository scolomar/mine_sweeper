/******************************************************************************
 *	Copyright (C) 2017	Alejandro Colomar Andrés		      *
 ******************************************************************************/

# ifndef		LIBALX_NCUR_H
	# define	LIBALX_NCUR_H

	#include <ncurses.h>
	#include <stdint.h>

	struct	alx_optn {
		int	r;
		int	c;
		char	*t;
	};


	void	alx_start_curses	(void);
	void	alx_pause_curses	(void);
	void	alx_resume_curses	(void);
	void	alx_end_curses		(void);
	void	alx_win_del		(WINDOW		*win);

	int	alx_menu		(int		h,
					int		w,
					int		N,
					struct alx_optn	mnu[N],
					const char	*str);

	int	alx_menu_2		(WINDOW		*win,
					int		N,
					struct alx_optn	mnu[N],
					const char	*str);

	double	alx_w_getdbl		(int		w,
					int		r,
					const char	*title,
					double		m,
					double		def,
					double		M,
					const char	*format,
							...);

	int64_t	alx_w_getint		(int		w,
					int		r,
					const char	*title,
					double		m,
					int64_t		def,
					double		M,
					const char	*format,
							...);

	void	alx_w_getstr		(char		*str,
					int		w,
					int		r,
					const char	*title,
					const char	*def,
					const char	*format,
							...);

	void	alx_w_getfpath		(char		*fpath,
					int		w,
					int		r,
					const char	*title,
					const char	*def,
					const char	*format,
							...);


/*


	const int64_t		len = TST_FUNCTIONS;
	const struct alx_option	mnu[TST_FUNCTIONS] =	{{7, 4, "[0]	Exit program"},
						{2, 4, "[1]	Continue"},
						{3, 4, "[2]	Disclaimer of warranty"},
						{4, 4, "[3]	Continue"},
						{5, 4, "[4]	Disclaimer of warranty"},
						{6, 4, "[5]	Continue"},
						{7, 4, "[6]	Disclaimer of warranty"},
						{8, 4, "[7]	Continue"},
						{9, 4, "[8]	Disclaimer of warranty"},
						{10, 4, "[9]	Continue"},
						{11, 4, "[10]	Disclaimer of warranty"},
						{12, 4, "[11]	Continue"},
						{13, 4, "[12]	Disclaimer of warranty"},
						{14, 4, "[13]	Continue"},
						{15, 4, "[14]	Disclaimer of warranty"},
						{16, 4, "[15]	Continue"},
						{17, 4, "[16]	Disclaimer of warranty"},
						{18, 4, "[17]	Continue"},
						{19, 4, "[18]	Disclaimer of warranty"},
						{20, 4, "[19]	Continue"},
						{21, 4, "[20]	Disclaimer of warranty"},
						{22, 4, "[21]	Continue"},
						{23, 4, "[22]	Disclaimer of warranty"},
						{24, 4, "[23]	Continue"},
						{25, 4, "[24]	Disclaimer of warranty"},
						{26, 4, "[25]	Continue"},
						{27, 4, "[26]	Disclaimer of warranty"},
						{28, 4, "[27]	Continue"},
						{29, 4, "[28]	Disclaimer of warranty"},
						{26, 4, "[29]	Terms and conditions"}};

	wh = true;
	while (wh) {
		win =	newwin(h, w, r, c);
		keypad(win, true);

		alx_w_title(win, "MENU:");
		mvwaddstr(win, mnu[1].r, mnu[1].c, mnu[1].t);
		mvwaddstr(win, mnu[2].r, mnu[2].c, mnu[2].t);
		mvwaddstr(win, mnu[3].r, mnu[3].c, mnu[3].t);
		mvwaddstr(win, mnu[4].r, mnu[4].c, mnu[4].t);
		mvwaddstr(win, mnu[5].r, mnu[5].c, mnu[5].t);
		mvwaddstr(win, mnu[6].r, mnu[6].c, mnu[6].t);
		mvwaddstr(win, mnu[7].r, mnu[7].c, mnu[7].t);
		mvwaddstr(win, mnu[8].r, mnu[8].c, mnu[8].t);
		mvwaddstr(win, mnu[9].r, mnu[9].c, mnu[9].t);
		mvwaddstr(win, mnu[0].r, mnu[0].c, mnu[0].t);
		mvwaddstr(win, mnu[11].r, mnu[11].c, mnu[11].t);
		mvwaddstr(win, mnu[12].r, mnu[12].c, mnu[12].t);
		mvwaddstr(win, mnu[13].r, mnu[13].c, mnu[13].t);
		mvwaddstr(win, mnu[14].r, mnu[14].c, mnu[14].t);
		mvwaddstr(win, mnu[15].r, mnu[15].c, mnu[15].t);
		mvwaddstr(win, mnu[16].r, mnu[16].c, mnu[16].t);
		mvwaddstr(win, mnu[17].r, mnu[17].c, mnu[17].t);
		mvwaddstr(win, mnu[18].r, mnu[18].c, mnu[18].t);
		mvwaddstr(win, mnu[19].r, mnu[19].c, mnu[19].t);
		mvwaddstr(win, mnu[0].r, mnu[0].c, mnu[0].t);
		wrefresh(win);

*/

# endif			/* alx_ncur.h */
