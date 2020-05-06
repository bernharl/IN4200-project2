int MPI_count_friends_of_ten(int M, int N, int** v) {
    int rank;
    int size;
    int N_split;
    int num_triple_friends = 0;
    int N_rest = 0;
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    printf("%i %i\n", rank, size);
    if (rank==0) {
        N_split = N / size;
        int** v_0 = allocate_2d(M, N_split);
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N_split; j++) {
                v_0[i][j] = v[i][j];
            }
        }
        num_triple_friends = count_friends_of_ten(M, N_split, v_0);
        
        
        return num_triple_friends;
        
        
    }
    else {
        0;
    }
    return 1;
}
