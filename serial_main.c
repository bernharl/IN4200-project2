#include <stdlib.h>
#include <stdio.h>

#include "count_friends_of_ten.c"
#include "utils.c"

int main() {
	int M = example_M();
	int N = example_N();
	int** A = example_array();
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			printf("%i ", A[i][j]);
		}
		printf("\n");
	}
	printf("%i\n", count_friends_of_ten(M, N, A));
	free_2d(A, M, N);
	return 0;
}
