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


void	parser	(int argc, char *argv[])
{
	int	opt =		0;
	int	opt_index =	0;

	struct option long_options[] = {
		{"rows",		required_argument,	0,	'a'},
		{"columns",		required_argument,	0,	'b'},
		{"file",		required_argument,	0,	'f'},
		{"help",		no_argument,		0,	'h'},
		{"proportion-first",	required_argument,	0,	'i'},
		{"proportion-interval",	required_argument,	0,	'j'},
		{"proportion-last",	required_argument,	0,	'k'},
		{"license",		no_argument,		0,	'l'},
		{"order",		required_argument,	0,	'o'},
		{"proportion",		required_argument,	0,	'p'},
		{"rand-seed",		required_argument,	0,	'r'},
		{"start",		required_argument,	0,	's'},
		{"Verbose",		required_argument,	0,	'V'},
		{"version",		no_argument,		0,	'v'},
		{"exit",		no_argument,		0,	'x'},
		{0,			0,			0,	0}
	};

	while ((opt = getopt_long(argc, argv, OPT_LIST, long_options,
						&opt_index )) != -1) {
		switch (opt) {
		case 'a':
			board.rows =	atoi(optarg);
			if (board.rows < 1 || board.rows > DIM_MAX) {
				printf("--order-first argument not valid\n");
				printf("It must be an integer [1 U %i]\n", DIM_MAX);
				exit(EXIT_FAILURE);
			}
			break;

		case 'b':
			board.cols =	atoi(optarg);
			if (board.cols < 1 || board.cols > DIM_MAX) {
				printf("--order-interval argument not valid\n");
				printf("It must be an integer [1 U %i]\n", DIM_MAX);
				exit(EXIT_FAILURE);
			}
			break;

		case 'f':
			strcpy(file_path, optarg);
			FILE	*fp;
			fp =	fopen(file_path, "r");
			if (!fp) {
				printf("--file argument not valid\n");
				printf("It must be a valid file path\n");
				exit(EXIT_FAILURE);
			} else {
				fclose(fp);
			}
			break;

		case 'h':
			print_help();
			exit(EXIT_SUCCESS);

		case 'l':
			print_license();
			exit(EXIT_SUCCESS);

		case 'p':
			board.p =		atof(optarg);
			if (board.p < 0 || board.p > 1) {
				printf("--proportion argument not valid\n");
				printf("It must be a real [0 U 1]\n");
				exit(EXIT_FAILURE);
			}
			break;

		case 'r':
			seed =	atof(optarg);
			srand(seed);
			break;

		case 's':
			flag_s =	atoi(optarg);
			if (flag_s < 0 || flag_s > 10) {
				printf("--start argument not valid\n");
				printf("It must be an integer [1 U 10]\n");
				exit(EXIT_FAILURE);
			}
			break;

		case 'V':
			flag_V =	atoi(optarg);
			if (flag_V < 0 || flag_V > 4) {
				printf("--Verbose argument not valid\n");
				printf("It must be an integer [0 U 4]\n");
				exit(EXIT_FAILURE);
			}
			break;

		case 'v':
			print_version();
			exit(EXIT_SUCCESS);

		case 'x':
			flag_x =	true;
			break;

		case '?':
			/* getopt_long already printed an error message. */

		default:
			print_usage();
			exit(EXIT_FAILURE);
		}
	}
}
