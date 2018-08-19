/******************************************************************************
 *	Copyright (C) 2017	Alejandro Colomar Andrés		      *
 ******************************************************************************/

	#include <stdint.h>
	#include <stdio.h>

	#include "alx_file.h"


	# define	BEGINNING	"\n┌──────────────────────────────────────────────────────────────────────────────┐\n"
	# define	ENDING		"└──────────────────────────────────────────────────────────────────────────────┘\n\n"

	# define	ERR_FPTR_MSG	"¡ FILE error !"


void	alx_prn_file		(const char *filepath)
{

	int64_t	c;
	FILE	*fp;

	fp =	fopen(filepath, "r");
	printf(BEGINNING);
	if (fp) {
		while ((c = getc(fp)) != EOF){
			putchar(c);
		}
		fclose(fp);
	} else {
		printf(ERR_FPTR_MSG);
	}
	printf(ENDING);

}
