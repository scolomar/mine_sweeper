	#include <stdint.h>

	#include "alx_cmp.h"


	/*
	 * Comparison function. Receives two items under comparison.
	 * return int
	 */
int	compare_int64		(const void *a, const void *b)
{
	int	r;

	if (*(int64_t *)a < *(int64_t *)b) {
		r = -1;
	} else if (*(int64_t *)a > *(int64_t *)b) {
		r = 1;
	} else if (*(int64_t *)a == *(int64_t *)b) {
		r = 0;
	}

	return	r;
}
