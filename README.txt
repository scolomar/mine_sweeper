/******************************************************************************
 * Based on the game 'Mine', written in 1990 by				      *
 * Robert Donner & Curt Johnson at Duff Software.			      *
 *									      *
 * Check this: https://tcrf.net/Proto:Minesweeper_(Windows,_1990)	      *
 ******************************************************************************
 * mine_sweeper	Copyright (C) 2015	Alejandro Colomar Andrés	      *
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

	If you make a version, please tell me.
	I would like to see it. Thank you.

COMPILE:
	linux: 
		$ make
	windows (MSYS):
		$ make OS=win

RUN:
	linux: 
		$ cd bin
		$ ./mine_sweeper
	windows:
		double click on win/mine_sweeper.exe


THE PROGRAM DOES:
	The typical minesweeper game.


MENU:
	When you run the program, it starts in a menu that has these branches:

	/*
	 * + Menu:
	 *	+ Continue:
	 *		- Start
	 *		+ Change size:
	 *			- Change rows:
	 *			- Change cloumns:
	 *			- ..
	 *		+ Change proportion of mines:
	 *			- Change proportion of mines:
	 *			- ..
	 *		- Change seed (srand)
	 *		+ Change verbose:
	 *			- Show only time
	 *			- Show WORST time, matrix and solution
	 *			- Show time, matrix and solution
	 *			- Show everything
	 *			- Show NOTHING
	 *		- ..
	 *	- Disclaimer
	 *	- License
	 *	- Exit program
	 */


SYSTEM REQUIREMENTS:

	/*
	 * Not much
	 */

To be continued...
