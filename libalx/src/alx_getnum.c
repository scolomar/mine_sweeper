/******************************************************************************
 *	Copyright (C) 2017	Alejandro Colomar Andrés		      *
 ******************************************************************************/

	#include <inttypes.h>
	#include <stdarg.h>
	#include <stdio.h>

	#include "alx_getnum.h"

	# define	BUFF_SIZE	(1024)

	# define	MAX_TRIES	(2)

	# define	ERR_RANGE	(1)
	# define	ERR_SSCANF	(2)
	# define	ERR_FGETS	(3)

	# define	ERR_RANGE_MSG	"¡ Number is out of range !"
	# define	ERR_SSCANF_MSG	"¡ sscanf() error !"
	# define	ERR_FGETS_MSG	"¡ fgets() error !"


static	double	loop_getdbl	(double m, double def, double M);
static	int64_t	loop_getint	(int64_t m, int64_t def, int64_t M);
static	void	manage_error	(int err);


	/*
	 * Ask for a double in the range [m, M].
	 *
	 * If the user enters a non valid number, it repeats to ask for
	 * the number two more times. After that, it uses the default
	 * value.
	 */
double	alx_getdbl	(double m, double def, double M,
			const char *formatA, const char *formatB, ...)
{
	va_list	args;
	va_start(args, formatB);

	double	R;

	if (formatA != NULL) {
		puts(formatA);
	}
	if (formatB == NULL) {
		printf("Introduce a real number [%lf U %lf] (default %lf):...\t", m, M, def);
	} else {
		vprintf(formatB, args);
	}

	R = loop_getdbl(m, def, M);

	va_end(args);
	return	R;
}

	/*
	 * Ask for an int64_t in the range [m, M].
	 *
	 * If the user enters a non valid number, it repeats to ask for
	 * the number two more times. After that, it uses the default
	 * value.
	 */
int64_t	alx_getint	(int64_t m, int64_t def, int64_t M,
			const char *formatA, const char *formatB, ...)
{
	va_list	args;
	va_start(args, formatB);

	int64_t	Z;

	if (formatA != NULL) {
		puts(formatA);
	}
	if (formatB == NULL) {
		printf("Introduce an integer number [%"PRIi64" U %"PRIi64"] (default %"PRIi64"):...\t", m, M, def);
	} else {
		vprintf(formatB, args);
	}

	Z = loop_getint(m, def, M);

	va_end(args);
	return	Z;
}


static	double	loop_getdbl	(double m, double def, double M)
{
	int	i;
	char	buff [BUFF_SIZE];
	char	*x1;
	int	x2;
	double	R;
	int	err;

	for (i = 0; i < MAX_TRIES; i++) {
		x1 =	fgets(buff, BUFF_SIZE, stdin);

		if (x1 == NULL) {
			err = ERR_FGETS;
		} else {
			x2 =	sscanf(buff, "%lf", &R);

			if (x2 != 1) {
				err = ERR_SSCANF;
			} else if (R < m || R > M) {
				err = ERR_RANGE;
			} else {
				break;
			}
		}

		manage_error(err);
		R = def;
	}

	return	R;
}

static	int64_t	loop_getint	(int64_t m, int64_t def, int64_t M)
{
	int	i;
	char	buff [BUFF_SIZE];
	char	*x1;
	int	x2;
	int64_t	Z;
	int	err;

	for (i = 0; i < MAX_TRIES; i++) {
		x1 =	fgets(buff, BUFF_SIZE, stdin);

		if (x1 == NULL) {
			err = ERR_FGETS;
		} else {
			x2 =	sscanf(buff, "%"SCNi64, &Z);

			if (x2 != 1) {
				err = ERR_SSCANF;
			} else if (Z < m || Z > M) {
				err = ERR_RANGE;
			} else {
				break;
			}
		}

		manage_error(err);
		Z = def;
	}

	return	Z;
}

static	void	manage_error	(int err)
{
	switch (err) {
	case ERR_RANGE:
		puts(ERR_RANGE_MSG);
		break;
	case ERR_SSCANF:
		puts(ERR_SSCANF_MSG);
		break;
	case ERR_FGETS:
		puts(ERR_FGETS_MSG);
		break;
	}
}
