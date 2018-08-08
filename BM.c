#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
/*
	[][][0] = Valor real	< 0:	0 minas cercanas y todas las cercanas descubiertas
				0-8:	N.º de minas cercanas
				> 8:	Mina

	[][][1] = Estado	0:	Oculta
				1:	Descubierta
				2:	Bandera V
				3:	Bandera F

	Interfaz		+:	Celda oculta
				·:	0 minas cercanas
				1-8:	N.º de minas cercanas
				#:	Mina marcada
				M:	Mina no explotada
				N:	No había mina
				X:	Mina explotada
*/



	# define	MINE_NO		0
	# define	MINE_YES	9

	# define	USR_HIDDEN	0
	# define	USR_CLEAR	1
	# define	USR_FLAG_T	2
	# define	USR_FLAG_F	3






	///////////////////	Variables globales:

	int	B = 0;











	//////////////////	Prototipos de funciones:

	//	Mostrar tablero invisible: Solo para pruebas.
		void		mosM	(int BM[F][C][2]);

//	Desarrollo del juego.
	void		juego	(int BM[F][C][2]);

	//	Mostrar tablero.
		void		mosT	(int BM[F][C][2]);

	//	Confirmar: En caso de que la celda este marcada como bandera.	Devuelve 1 si confirma, 0 si anula.
		int		confD	(void);

	//	Descubrir celda.
		void		desC	(int BM[F][C][2], int f, int c);

	//	Colocar bandera.
		void		banC	(int BM[F][C][2], int f, int c);

//	Fin del juego.
	void		fin	(int BM[F][C][2]);

	//	Mostrar tablero Explotado.
		void		mosX	(int BM[F][C][2]);

	//	Mostrar tablero Victoria.
		void		mosV	(int BM[F][C][2]);









	////////////─────────────────────────BUSCAMINAS─────────────────────────////////////

int	main	(void){

	srand	(time(NULL));
	solFC	();

	int	BM[F][C][2];

	ini	(BM);
	juego	(BM);
	fin	(BM);

	return	0;
}

	//////////////──────────────────────────────────────────────────────────/////////////










	/////////////////	Definiciones de funciones:

	/////////////////////////////////////////////////////////////////////////

	void		mosM	(int BM[F][C][2]){
		int	f,	c;
		printf	("\n");
		for	(f = 0; f < F; f++){
			
		}
		for	(f = 0; f < F; f++){
			for	(c = 0; c < C; c++)
				if	(!BM[f][c][0])
					printf	(" · ");
				else if	(BM[f][c][0] > 8)
					printf	(" M ");
				else
					printf	(" %i ", BM[f][c][0]);
			printf	("\n");
		}
		printf	("\n\n");
	}

	/////////////////////////////////////////////////////////////////////////

	void		juego	(int BM[F][C][2]){
		while	(N >= 0 && N < (FC-M)){
			mosT	(BM);
			printf	("Fila:\t\t");
			f =	getZmM(1, F) - 1;
			printf	("Columna:\t");
			c =	getZmM(1, C) - 1;
			printf	("Accion:\n");
			printf	("Descubrir[1]\tBandera[2]\n");
			a =	getZmM	(1, 2);
			switch	(a){
				case	1:
					if	(BM[f][c][1] > 1){
						if	(confD	()){
							B--;
							desC	(BM, f, c);
						}
					}else
						desC	(BM, f, c);
					
					break;
				case	2:
					banC	(BM, f, c);
					break;
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////

	void		mosT	(int BM[F][C][2]){
		int	f,	c;

		for (f = 0; f < F; f++) {
			for (c = 0; c < C; c++) {
				switch (BM[f][c][1]) {
					case 0:
						if ((f+1)%10 && (c+1)%10)
							printf	(" + ");
						else
							printf	(" x ");
						break;
					case 1:
						if	(BM[f][c][0] > 0)
							printf	(" %i ", BM[f][c][0]);
						else
							printf	(" · ");
						break;
					default:
						printf	(" # ");
						break;
				}
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////

	void		fin	(int BM[F][C][2]){
		if	(N < 0)
			mosX	(BM);
		else
			mosV	(BM);
	}

	/////////////////////////////////////////////////////////////////////////

	void		mosX	(int BM[F][C][2]){
		int	f,	c;

		printf	("─────────────────────────\n");
		printf	("\tGAME OVER\n");
		printf	("─────────────────────────\n");
		for	(f = 0; f < F; f++){
			for	(c = 0; c < C; c++)
				switch	(BM[f][c][1]){
					case	0:
						if	(BM[f][c][0] > 8)
							printf	(" X ");
						else
							printf	(" - ");
						break;
					case	1:
						if	(BM[f][c][0] > 0)
							printf	(" %i ", BM[f][c][0]);
						else
							printf	("   ");
						break;
					case	2:
						printf	(" M ");
						break;
					case	3:
						printf	(" N ");
						break;
				}
			printf	("\n");
		}
		printf	("\n");
	}

	/////////////////////////////////////////////////////////////////////////

	void		mosV	(int BM[F][C][2]){
		int	f,	c;

		printf	("─────────────────────────\n");
		printf	("\tVICTORIA\n");
		printf	("─────────────────────────\n");
		for	(f = 0; f < F; f++){
			for	(c = 0; c < C; c++)
				switch	(BM[f][c][1]){
					case	0:
						printf	(" - ");
						break;
					case	1:
						if	(BM[f][c][0] > 0)
							printf	(" %i ", BM[f][c][0]);
						else
							printf	("   ");
						break;
					case	2:
						printf	(" M ");
						break;
				}
			printf	("\n");
		}
		printf	("\n");
	}

////////////////────────────────── ALEJANDRO C. A. ──────────────────////////////////
//1903716BuscaMinasC//
