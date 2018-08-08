/******************************************************************************
 * PNP-Solver	Copyright (C) 2012	Alejandro Colomar Andrés	      *
 *									      *
 * This program is free software; you can redistribute it and/or modify	      *
 * it under the terms of the GNU General Public License as published by	      *
 * the Free Software Foundation, version 2.				      *
 *									      *
 * This program is distributed in the hope that it will be useful,	      *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of	      *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	      *
 * GNU General Public License for more details.				      *
 *									      *
 * You should have received a copy of the GNU General Public License	      *
 * along with this program; if not, see the file COPYING, or write	      *
 * to the Free Software Foundation, Inc.				      *
 ******************************************************************************/

/******************************************************************************
 *	Disclaimer of Warranty.						      *
 *									      *
 * THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY	      *
 * APPLICABLE LAW.							      *
 *									      *
 * EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER *
 * PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER   *
 * EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED	      *
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.	      *
 *									      *
 * THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH   *
 * YOU.									      *
 *									      *
 * SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY   *
 * SERVICING, REPAIR OR CORRECTION.					      *
 ******************************************************************************/

	If you make a version or fork it, please tell me.
	I would like to see it. Thank you.

COMPILE:
	linux: 
		$ make
	windows (MSYS):
		$ make OS=win


THE PROGRAM DOES:
	This program creates a random matrix that represents an independent set,
	and then uses an algorithm developed by me to solve it.
	
	The 1s in the matrix mean that the two rows are compatible (rows and
	columns are the same)

	The 0s mean incompatibility between rows.
 
	The algorithm returns the largest possible list of rows that are all
	compatible, and its lenght.

	The program also returns the time (s) needed to solve the problem.

	You can select verbose mode to see the steps of the process,
	although that steps are not yet explained, and you will see a lot of
	numbers like if it were The Matrix.


P = NP:
	I have used it writing down the times used to solve different matrices,
	and it seems to me that it is working in P time, but that would imply
	too many things, so I'm not really sure...  Maybe it uses NP time...  Or
	maybe it begins thermonuclear war... who knows?
	
	I am running benchmarks to see if it really works.

 - PLEASE, IF YOU DOWNLOAD AND USE IT, LET ME KNOW WHAT YOUR RESULTS ARE,
	WHETHER THEY'RE GOOD OR BAD!!

 - I know the code is not very readable. When I have time, I will change that,
	as well as also explain the algorithm.

Thank you for reading until here. :-)


MENU:
	When you run the program, it starts in a menu that has these branches:

	/*
	 * + Menu:
	 *	+ [1] Continue:
	 *		- [1] Start
	 *		+ [2] Select matrix:
	 *			- [1] Use your matrix
	 *			- [2] Single random
	 *			- [3] Fixed order, variable p
	 *			- [4] Fixed p, variable order
	 *			- [0] ..
	 *		+ [3] Change order of the matrix:
	 *			- [1] Change order of the matrix: o
	 *			- [2] Change begining: o_0
	 *			- [3] Change interval: o_i
	 *			- [4] Change ending: o_1
	 *			- [0] ..
	 *		+ [4] Change proportion of 1s:
	 *			- [1] Change proportion of 1s: p
	 *			- [2] Change begining: p_0
	 *			- [3] Change interval: p_i
	 *			- [4] Change ending: p_1
	 *			- [0] ..
	 *		- [5] Change file path
	 *		- [6] Change seed (srand)
	 *		+ [7] Change verbose:
	 *			- [1] Show only time
	 *			- [2] Show WORST time, matrix and solution
	 *			- [3] Show time, matrix and solution
	 *			- [4] Show everything
	 *			- [0] Show NOTHING
	 *		- [0] ..
	 *	- [2] Disclaimer
	 *	- [3] License
	 *	- [0] Exit program
	 */


SYSTEM REQUIREMENTS:

	/*
	 * It uses a lot of RAM
	 */

To be continued...
