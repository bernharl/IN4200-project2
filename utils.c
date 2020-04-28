int** allocate_2d(int Nx, int Ny) {
    int *A_storage = (int*)malloc(Nx * Ny * sizeof(int));
    int **A = (int**)malloc(Nx * sizeof(int*));
    for (int i=0; i<Nx; i++) {
        A[i] = &(A_storage[i*Ny]);
    }  
    return A;
}

int** zeros_2d(int Nx, int Ny) {
    int** A = allocate_2d(Nx, Ny);
    for (int i = 0; i<Nx; i++) {
        for (int j = 0; j<Ny; j++) {
            A[i][j] = 0;
        }
    }    
    return A;
}

int example_M() {
    return 4;
}

int example_N() {
    return 5;
}

int** example_array() {
    int** A = allocate_2d(example_M(), example_N());
    A[0][0] = 1;
    A[0][1] = 5;
    A[0][2] = 6;
    A[0][3] = 3;
    A[0][4] = 1;
    A[1][0] = 2;
    A[1][1] = 4;
    A[1][2] = 4;
    A[1][3] = 1;
    A[1][4] = 7;
    A[2][0] = 7;
    A[2][1] = 2;
    A[2][2] = 3;
    A[2][3] = 1;
    A[2][4] = 2;
    A[3][0] = 3;
    A[3][1] = 2;
    A[3][2] = 2;
    A[3][3] = 5;
    A[3][4] = 3;
    return A;
}

void free_2d(int** A, int M, int N) {
    /*for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            free(A[i][j]);
        }
    }*/
    //for (int i = 0; i < N; i++) {
    //    free(A[i]);
    //}
    free(A[0]);
    free(A);
}