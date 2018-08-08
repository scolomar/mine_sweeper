/******************************************************************************
 *	Copyright (C) 2017	Alejandro Colomar Andrés		      *
 ******************************************************************************/

# ifndef		ALX_MATH_H
	# define	ALX_MATH_H

	#include <math.h>
	#include <stdint.h>

	/*
	 * Factorial
	 */
double	alx_fact	(int64_t n);

	/*
	 * Binomial coefficient (a b):				--!!!  a > b  !!!--
	 * - Bugs: If !(a > b), returns 1.
	 */
double	alx_bin_coef	(int64_t a, int64_t b);

# endif			/* alx_math.h */
