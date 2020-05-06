#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>

#include "utils.c"
#include "count_friends_of_ten.c"
#include "mpi_count_friends_of_ten.c"


int main(int argc, char **argv) {
    int M=0, N=0, rank, num_triple_friends;
    int **v=NULL;
    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    if (rank==0) {
        M = 100;
        N = 100;
        v = random_array(M, N);
    // decide the values for M and N
    // allocate 2D array v and assign it with suitable values
    }
    num_triple_friends = MPI_count_friends_of_ten (M, N, v);
    printf("MPI rank <%d>: number of triple friends=%d\n",rank, num_triple_friends);
    if (rank==0) {
        free(v[0]);
        free(v);
    // deallocation of 2D array 
    }
    MPI_Finalize();
    /*int M = 10;
    int N = 10;
    int** A = random_array(M, N);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%i ", A[i][j]);
        }
        printf("\n");
    }*/
    return 0;
}
