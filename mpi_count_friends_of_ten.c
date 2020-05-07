int MPI_count_friends_of_ten(int M, int N, int** v) {
    int ghost = 2;
    int rank;
    int size;
    int N_split;
    int num_triple_friends = 0;
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    printf("%i %i\n", rank, size);
    if (rank==0) {
        // Need to read two extra at edge, hence + 2
        // We do not want this with only one thread though.
        N_split = N / size;
        if (size > 1) {
            N_split += ghost;
        }
        int** v_0 = allocate_2d(M, N_split);
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N_split; j++) {
                v_0[i][j] = v[i][j];
            }
        }
        num_triple_friends = count_friends_of_ten(M, N_split, v_0);
        free(v_0[0]);
        free(v_0);
        for (int i = 1; i < size; i++) {
            MPI_Send(&M, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            int starts[2] = {0, i * (N_split-ghost)}; // -2 to account for edge added
            if (i==size - 1) {
                // Adding rest to last rank, but removing edge (as we are at edge
                // of matrix)
                N_split += N % size - ghost;
            }
            MPI_Send(&N_split, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            
            MPI_Datatype split_array; //Thank you, Stackexchange!
            
            int sub[2] = {M, N_split};
            int full[2] = {M, N};
            // Creating subarray in 2D, with C-contigous memory (not FORTRAN)
            MPI_Type_create_subarray(2, full, sub, starts, MPI_ORDER_C, MPI_INT, &split_array);
            MPI_Type_commit(&split_array);
            MPI_Send(&(v[0][0]), 1, split_array, i, 0, MPI_COMM_WORLD);
            MPI_Type_free(&split_array);
        }
    }
    else {
        MPI_Recv(&M, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&N_split, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        int** split_array = allocate_2d(M, N_split);
        MPI_Recv(&(split_array[0][0]), M * N_split, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        num_triple_friends = count_friends_of_ten(M, N_split, split_array);
        free(split_array[0]);
        free(split_array);
    }
    int total;
    printf("Rank %i: %i\n", rank, num_triple_friends);
    MPI_Allreduce(&num_triple_friends, &total, size, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    return total;
}
