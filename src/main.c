#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#define	_d	0.02	//Densidad de minas: entre 0.01 y 0.05
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










	///////////////////	Variables globales:

	int		F,	C,	FC,	M,	N = 0,	B = 0;











	//////////////////	Prototipos de funciones:

//	Solicitar Entero entre m y M.
	int		getZmM	(int Zm, int ZM);

//	Solicitar numero de filas y columnas.
	void		solFC	(void);

//	Iniciar partida.
	void		ini	(int BM[F][C][2]);

	//	Iniciar tablero a 0.
		void		ini0	(int BM[F][C][2]);

	//	Crear minas.
		void		iniM	(int BM[F][C][2]);

	//	Iniciar valores.
		void		iniV	(int BM[F][C][2]);

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

	int		getZmM	(int Zm, int ZM){
		long double	in;
		int	i,	Z,	r = 1;
		printf	("Introduce un Entero [%i U %i]:...\t", Zm, ZM);
		for	(i = 0; i < 3 && r; i++){
			scanf	("%Lf", &in);
			Z =	in;
			if	(in < Zm || in != Z || in > ZM){
				printf	("No es valido...\t");
				Z =	0;
			}else
				r =	0;
		}
		return	Z;
	}

	/////////////////////////////////////////////////////////////////////////

	void		solFC	(void){
		printf	("Numero de filas:\t");
		F =	getZmM	(8, 32);
		printf	("Numero de columnas:\t");
		C =	getZmM	(8, 32);
		FC =	F * C;
	}

	/////////////////////////////////////////////////////////////////////////

	void		ini	(int BM[F][C][2]){
		M =	10 + _d*F*C;
		ini0	(BM);
		iniM	(BM);
		iniV	(BM);
	//	mosM	(BM);	//
	}


	/////////////////////////////////////////////////////////////////////////

	void		ini0	(int BM[F][C][2]){
		int	f,	c;
		for	(f = 0; f < F; f++)
			for	(c = 0; c < C; c++){
				BM[f][c][0] =	0;
				BM[f][c][1] =	0;
			}
	}

	/////////////////////////////////////////////////////////////////////////

	void		iniM	(int BM[F][C][2]){
		int	m,	rf,	rc;
		for	(m = 0; m < M; m++){
			rf =	rand() % F;
			rc =	rand() % C;
			if	(BM[rf][rc][0] == 9)
				m--;
			else
				BM[rf][rc][0] =	9;
		}
	}

	/////////////////////////////////////////////////////////////////////////

	void		iniV	(int BM[F][C][2]){
		int	f,	g,	c,	d;
		for	(f = 0; f < F; f++)
			for	(c = 0; c < C; c++)
				if	(BM[f][c][0] > 8)
					for	(g = f-1; g < f+2; g++)
						if	(g >= 0 && g < F)
							for	(d = c-1; d < c+2; d++)
								if	(d >= 0 && d < C)
									BM[g][d][0]++;
	}

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
		int	f,	c,	a,	b;
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
		printf	("\n%2i ╗ ", M-B);
		for	(c = 0; c < C; c++){
			printf	("%2i ", c+1);
		}
		printf	("\n═══╬═");
		for	(c = 0; c < C; c++){
			if	((c+1)%5)
				printf	("═══");
			else if	((c+1)%10)
				printf	("═╤═");
			else
				printf	("═╪═");
		}
		printf	("═╗\n");
		for	(f = 0; f < F; f++){
			if	((f+1)%5)
				printf	("%2i ║ ", f+1);
			else if	((f+1)%10)
				printf	("%2i ╟ ", f+1);
			else
				printf	("%2i ╫─", f+1);
			for	(c = 0; c < C; c++)
				switch	(BM[f][c][1]){
					case	0:
						if	((f+1)%10 && (c+1)%10)
							printf	(" + ");
						else
							printf	(" x ");
						break;
					case	1:
						if	(BM[f][c][0] > 0)
							printf	(" %i ", BM[f][c][0]);
						else
							printf	(" · ");
						break;
					default:
						printf	(" # ");
						break;
				}
			if	((f+1)%5)
				printf	(" ║ ");
			else if	((f+1)%10)
				printf	(" ╢ ");
			else
				printf	("─╫ ");
			printf	("\n");
		}
		printf	("   ╚═");
		for	(c = 0; c < C; c++){
			if	((c+1)%5)
				printf	("═══");
			else if	((c+1)%10)
				printf	("═╧═");
			else
				printf	("═╪═");
		}
		printf	("═╝\n\n");
	}

	/////////////////////////////////////////////////////////////////////////

	int		confD	(void){
		int	C;
		printf	("Posible mina!\tConfirmar acción: 1\tAnular: 0\n");
		C =	getZmM	(0, 1);
		return	C;
	}

	/////////////////////////////////////////////////////////////////////////

	void		desC	(int BM[F][C][2], int f, int c){
		int	g,	d;
		if	(f >= 0 && f < F && c >= 0 &&  c < C){
			if		(BM[f][c][0] > 8){
				BM[f][c][1] =	0;
				N =	-1;
			}else if	(BM[f][c][1] != 1){
				BM[f][c][1] =	1;
				N++;
				if		(!BM[f][c][0]){
					BM[f][c][0] =	-1;
					for		(g = f-1; g < f+2; g++)
						if		(g >= 0 && g < F)
							for		(d = c-1; d < c+2; d++)
								if		(d >= 0 && d < C)
									desC	(BM, g, d);
				}
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////

	void		banC	(int BM[F][C][2], int f, int c){
		if	(!BM[f][c][1]){
			if	(BM[f][c][0] > 8)
				BM[f][c][1] =	2;
			else
				BM[f][c][1] =	3;
			B++;
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
