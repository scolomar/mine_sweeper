/******************************************************************************
 *	Copyright (C) 2017	Alejandro Colomar Andrés		      *
 ******************************************************************************/

# ifndef		ALX_GETNUM_H
	# define	ALX_GETNUM_H

//	#include <curses.h>
	#include <math.h>
//	#include <stdbool.h>
	#include <stdarg.h>
	#include <stdint.h>

	/*
	 * Examples:
	 *	a =	alx_getdbl_mM(m, M, d, "a:\t", NULL);
	 *	a =	alx_getdbl_m(m, d, "a:\t", NULL);
	 *	a =	alx_getdbl("a:\t", NULL);
	 *	a =	alx_getint_mM(m, M, d, "a:\t", NULL);
	 *	a =	alx_getint_m(m, d, "a:\t", NULL);
	 */


	double	alx_getdbl	(double		m,
				double		def,
				double		M,
				const char	*formatA,
				const char	*formatB,
						...);

	int64_t	alx_getint	(int64_t	m,
				int64_t		def,
				int64_t		M,
				const char	*formatA,
				const char	*formatB,
						...);

# endif			/* alx_getnum.h */
