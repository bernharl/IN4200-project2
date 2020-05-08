#include <stdlib.h>
#include <stdio.h>

#include "count_friends_of_ten.c"
#include "utils.c"

int main() {
	int M = example_M();
	int N = example_N();
	int** v = example_array();
    //int M = 100;
    //int N = 100;
    //int** v = random_array(M, N);
    for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
            printf("%i ", v[i][j]);
        }
        printf("\n");
	}
	printf("%i\n", count_friends_of_ten(M, N, v));
	free(v[0]);
    free(v);
	return 0;
}
