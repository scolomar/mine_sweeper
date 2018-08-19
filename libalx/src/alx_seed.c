	#include <stdint.h>

	#include "alx_seed.h"

int64_t	seedf		(int64_t a, int64_t b, int64_t c)
{
	a -=	b + c;
	a =	a ^ (c >> 13);
	b -=	c + a;
	b =	b ^ (a << 8);
	c -=	a + b;
	c =	c ^ (b >> 13);
	a -=	b + c;
	a =	a ^ (c >> 12);
	b -=	a + c;
	b =	b ^ (a << 16);
	c -=	a + b;
	c =	c ^ (b >> 5);
	a -=	b + c;
	a =	a ^ (c >> 3);
	b -=	a + c;
	b =	b ^ (a << 10);
	c -=	a + b;
	c =	c ^ (b >> 15);
	return	c;
}
