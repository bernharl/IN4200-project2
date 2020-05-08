#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>

#include "utils.c"
#include "mpi_count_friends_of_ten.c"


int main(int argc, char **argv) {
    /*
     * Code mostly taken from task description
     */
    // Empty values used by rank!=0 to be able to call counting function.
    int M=0, N=0, rank, num_triple_friends;
    int **v=NULL;
    // Initialize multiprocessing
    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    if (rank==0) {
        // decide the values for M and N
        // allocate 2D array v and assign it with suitable values
        M = 1000;
        N = 10000;
        v = random_array(M, N);
        //M = example_M();
        //N = example_N();
        //v = example_array();   
    }
    num_triple_friends = MPI_count_friends_of_ten (M, N, v);
    printf("MPI rank <%d>: number of triple friends=%d\n",rank, num_triple_friends);
    if (rank==0) {
        //deallocation of 2D array 
        free(v[0]);
        free(v);
    }
    // Finalize multiprocessing
    MPI_Finalize();
    return 0;
}
