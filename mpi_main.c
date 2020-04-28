#include <stdlib.h>
#include <stdio.h>

#include "mpi_count_friends_of_ten.c"
#include "utils.c"

int main(int argc, char **argv) {
    int M=0, N=0, rank, num_triple_friends;
    int **v=NULL;
    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    if (rank==0) {
    // decide the values for M and N
    // allocate 2D array v and assign it with suitable values
    }
    num_triple_friends = MPI_count_friends_of_ten (M, N, v);
    printf("MPI rank <%d>: number of triple friends=%d\n",rank, num_triple_friends);
    if (rank==0) {
    // deallocation of 2D array 
    }
    MPI_Finalize();
    return 0;
}