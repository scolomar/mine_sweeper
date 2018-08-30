/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/


/******************************************************************************
 ******* headers **************************************************************
 ******************************************************************************/
/*	*	*	*	*	*	*	*	*	*
 *	*	* Standard	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
		/* printf() */
	#include <stdio.h>
		/* strcpy() & strcat() */
	#include <string.h>

/*	*	*	*	*	*	*	*	*	*
 *	*	* Other	*	*	*	*	*	*	*
 *	*	*	*	*	*	*	*	*	*/
		/* alx_prn_file() */
	#include "alx_file.h"

	#include "about.h"


/******************************************************************************
 ******* variables ************************************************************
 ******************************************************************************/
char	share_path [FILENAME_MAX];


/******************************************************************************
 ******* main *****************************************************************
 ******************************************************************************/
void	about_init		(void)
{
	strcpy(share_path, INSTALL_SHARE_DIR);
	strcat(share_path, "/");
	strcat(share_path, SHARE_DIR);
	strcat(share_path, "/");
}

void	print_cpright		(void)
{
	char	file_name [FILENAME_MAX];

	strcpy(file_name, share_path);
	strcat(file_name, "/");
	strcat(file_name, "COPYRIGHT.txt");

	alx_prn_file(file_name);
}

void	print_disclaim		(void)
{
	char	file_name [FILENAME_MAX];

	strcpy(file_name, share_path);
	strcat(file_name, "/");
	strcat(file_name, "DISCLAIMER.txt");

	alx_prn_file(file_name);
}

void	print_help		(void)
{
	char	file_name [FILENAME_MAX];

	strcpy(file_name, share_path);
	strcat(file_name, "/");
	strcat(file_name, "HELP.txt");

	alx_prn_file(file_name);
}

void	print_license		(void)
{
	char	file_name [FILENAME_MAX];

	strcpy(file_name, share_path);
	strcat(file_name, "/");
	strcat(file_name, "LICENSE.txt");

	alx_prn_file(file_name);
}

void	print_usage		(void)
{
	char	file_name [FILENAME_MAX];

	strcpy(file_name, share_path);
	strcat(file_name, "/");
	strcat(file_name, "USAGE.txt");

	alx_prn_file(file_name);
}

void	print_version		(void)
{
	printf("" PROG_NAME " " PROG_VERSION "\n\n");
}
