#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "count_friends_of_ten.c"
#include "utils.c"

int main() {
	// int M = example_M();
	// int N = example_N();
	// int** v = example_array();
    int M = 10000;
    int N = 10000;
    int** v = random_array(M, N);
	printf("Triple friends of ten, serial: %i\n", count_friends_of_ten(M, N, v));
	free(v[0]);
    free(v);
	return 0;
}
