/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

		/* USR_CLEARED & KBOOM*/
	#include "data.h"
		/* print_t...() */
	#include "print.h"

	#include "check.h"


void	game_over		(void)
{
	if (USR_CLEARED == KBOOM) {
		print_fail();
	} else {
		print_victory();
	}
}
