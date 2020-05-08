int count_friends_of_ten(int M, int N, int** v, int ghost) {
    /*
     * Modified version of the serial count function that takes the ghost points 
     * into account when counting along the vertical axis.
     * See count_friends_of_ten.c for more details.
     */
	int friends = 0;
	int tmp;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if ((i < M-2) && (j < N - ghost)) {
				tmp = (v[i][j] + v[i+1][j] + v[i+2][j]) == 10;
				friends += tmp;
			}	
			if (j < N-2) {
				tmp = (v[i][j] + v[i][j+1] + v[i][j+2]) == 10;
				friends += tmp;
			}
			if ((i < M-2) && (j < N-2)) {
				tmp = (v[i][j] + v[i+1][j+1] + v[i+2][j+2]) == 10;
				friends += tmp;
			}
			if ((i >= 2) && (j < N-2)) {
				tmp = (v[i][j] + v[i-1][j+1] + v[i-2][j+2]) == 10;
				friends += tmp;
			}
		}
	}
	return friends;
}

int MPI_count_friends_of_ten(int M, int N, int** v) {
    /*
     * Function that used MPI to count friends of ten in array v of dimension 
     * MxN. Only M, N and V from rank==0 are used and will be distributed to other 
     * threads.
     */
    // Need two points of overlap in the horizontal direction for our counting 
    // to count all points.
    int ghost = 2;
    int rank;
    int size;
    int N_split;
    int num_triple_friends = 0;
    // Get rank and size
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    if (rank==0) {
        // Split N into equal parts for use by the different processes.
        N_split = N / size;
        // If we have only one process, we do not want any ghost points.
        int ghost_0 = 0;
        if (size > 1) {
            ghost_0 = ghost;
            N_split += ghost;
        }
        // Create subarray for first thread
        int** v_0 = allocate_2d(M, N_split);
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N_split; j++) {
                v_0[i][j] = v[i][j];
            }
        }
        // Calculate number of friends with first thread.
        num_triple_friends = count_friends_of_ten(M, N_split, v_0, ghost_0);
        free(v_0[0]);
        free(v_0);
        // Loop over all other threads.
        for (int i = 1; i < size; i++) {
            // Send M to other process
            MPI_Send(&M, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            // To use MPIs builtin subarray function we need to define where 
            // in the larger array the subarray should start. In our case it 
            // needs to start at [0, rank*(N_split-ghost)], ghost is accounted for 
            // because we added it to N_split earlier for simple use of the counting 
            // function.
            int starts[2] = {0, i * (N_split-ghost)};
            if (i==size - 1) {
                // Adding rest to last rank, but removing edge (as we are at edge
                // of matrix)
                N_split += N % size - ghost;
            }
            // Sending N_split to other process. This is done now so that it works 
            // for the highest rank as well.
            MPI_Send(&N_split, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            
            MPI_Datatype split_array; //Thank you, Stackexchange!
            // Size of subarray. We want a size of [M, N_split]
            int sub[2] = {M, N_split};
            // Size of full array
            int full[2] = {M, N};
            // Creating subarray in 2D, with C-contigous memory.
            MPI_Type_create_subarray(2, full, sub, starts, MPI_ORDER_C, MPI_INT, &split_array);
            MPI_Type_commit(&split_array);
            // Sending this subarray to rank i.
            MPI_Send(&(v[0][0]), 1, split_array, i, 0, MPI_COMM_WORLD);
            // Freeing
            MPI_Type_free(&split_array);
        }
    }
    else {
        // Receiving M and N_split for current process.
        MPI_Recv(&M, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&N_split, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // Allocating space for subarray
        int** split_array = allocate_2d(M, N_split);
        // Receiving subarray from rank 0
        MPI_Recv(&(split_array[0][0]), M * N_split, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // Counting triple friends, with no ghost if we are at edge of matrix 
        // aka highest rank.
        if (rank < size - 1) {
            num_triple_friends = count_friends_of_ten(M, N_split, split_array, ghost);
        }
        else {
            num_triple_friends = count_friends_of_ten(M, N_split, split_array, 0);
        }
        // Freeing subarray
        free(split_array[0]);
        free(split_array);
    }
    int total;
    // Printing triple friends of ten for current rank
    printf("Rank %i: %i\n", rank, num_triple_friends);
    // Reducing so we get total number of friends in all ranks (as opposed to 
    // MPI_reduce, which only sends the total value to one thread.
    MPI_Allreduce(&num_triple_friends, &total, size, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    return total;
}
