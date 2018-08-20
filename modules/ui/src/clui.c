/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 ******************************************************************************/

	#include <getopt.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	#include "alx_seed.h"

	#include "about.h"
	#include "data.h"

	#include "clui.h"


/******************************************************************************
 ******* static ***************************************************************
 ******************************************************************************/
static	void	parse_rows		(char* argument);
static	void	parse_columns		(char* argument);
static	void	parse_file		(char* argument);
static	void	parse_proportion	(char* argument);
static	void	parse_rand_seed		(char* argument);
static	void	parse_start		(char* argument);


/******************************************************************************
 ******* main *****************************************************************
 ******************************************************************************/
void	parser	(int argc, char *argv[])
{
	strcpy(prog_name, argv[0]);

	int	opt =		0;
	int	opt_index =	0;

	struct option long_options[] = {
		/* Standard */
		{"exit",		no_argument,		0,	'x'},
		{"help",		no_argument,		0,	'h'},
		{"license",		no_argument,		0,	'L'},
		{"usage",		no_argument,		0,	'u'},
		{"verbose",		required_argument,	0,	'V'},
		{"version",		no_argument,		0,	'v'},
		/* Non-standard */
		{"rows",		required_argument,	0,	'a'},
		{"columns",		required_argument,	0,	'b'},
		{"file",		required_argument,	0,	'f'},
		{"proportion",		required_argument,	0,	'p'},
		{"rand-seed",		required_argument,	0,	'r'},
		{"start",		required_argument,	0,	's'},
		/* Null */
		{0,			0,			0,	0}
	};

	while ((opt = getopt_long(argc, argv, OPT_LIST, long_options,
						&opt_index )) != -1) {
		switch (opt) {
		/* Standard */
		case 'x':
			flag_exit =	true;
			break;

		case 'h':
			print_help();
			exit(EXIT_SUCCESS);

		case 'L':
			print_license();
			exit(EXIT_SUCCESS);

		case 'u':
			print_usage();
			exit(EXIT_FAILURE);

		case 'V':
/*
			flag_V =	atoi(optarg);
			if (flag_V < 0 || flag_V > 4) {
				printf("--Verbose argument not valid\n");
				printf("It must be an integer [0 U 4]\n");
				exit(EXIT_FAILURE);
			}
*/
			break;

		case 'v':
			print_version();
			exit(EXIT_SUCCESS);

		/* Non-standard */
		case 'a':
			parse_rows(optarg);
			break;

		case 'b':
			parse_columns(optarg);
			break;

		case 'f':
			parse_file(optarg);
			break;

		case 'p':
			parse_proportion(optarg);
			break;

		case 'r':
			parse_rand_seed(optarg);
			break;

		case 's':
			parse_start(optarg);
			break;

		case '?':
			/* getopt_long already printed an error message. */

		default:
			print_usage();
			exit(EXIT_FAILURE);
		}
	}
}


/******************************************************************************
 ******* static ***************************************************************
 ******************************************************************************/
static	void	parse_rows		(char* argument)
{
	board.rows =	atoi(argument);
	if (board.rows < 2 || board.rows > ROWS_MAX) {
		printf("--rows argument not valid\n");
		printf("It must be an integer [%i U %i]\n", 2, ROWS_MAX);
		exit(EXIT_FAILURE);
	}
}

static	void	parse_columns		(char* argument)
{
	board.cols =	atoi(argument);
	if (board.cols < 2 || board.cols > COLS_MAX) {
		printf("--columns argument not valid\n");
		printf("It must be an integer [%i U %i]\n", 2, COLS_MAX);
		exit(EXIT_FAILURE);
	}
}

static	void	parse_file		(char* argument)
{
	FILE	*fp;
	fp =	fopen(argument, "r");
	if (!fp) {
		printf("--file argument not valid\n");
		printf("It must be a valid file name\n");
		exit(EXIT_FAILURE);
	} else {
		fclose(fp);

		strcpy(file_name, "../../bin/");
		strcat(file_name, argument);
	}
}

static	void	parse_proportion	(char* argument)
{
	board.p =	atof(argument);
	if (board.p < 0 || board.p > 1) {
		printf("--proportion argument not valid\n");
		printf("It must be a real [0 U 1]\n");
		exit(EXIT_FAILURE);
	}
}

static	void	parse_rand_seed		(char* argument)
{
	seed =	atof(argument);
	srand(seed);
}

static	void	parse_start		(char* argument)
{
	flag_s =	atoi(argument);
	if (flag_s < 0 || flag_s > 10) {
		printf("--start argument not valid\n");
		printf("It must be an integer [%i U %i]\n", START_FOO, START_LOAD);
		exit(EXIT_FAILURE);
	}
}
