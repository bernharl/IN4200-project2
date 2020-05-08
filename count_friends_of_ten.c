int count_friends_of_ten(int M, int N, int** v) {
    /*
     * Counts the triple friends of ten of given array v
     */
	int friends = 0;
	int tmp;
    // Looping over array
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			// If i+1 and i+2 exist, calculate equality that is 1 if the sum 
            // equals 10, and 0 else.
            if (i < M-2) {
				tmp = (v[i][j] + v[i+1][j] + v[i+2][j]) == 10;
				friends += tmp;
			}	
			// If j+1 and j+2 exist, calculate equality that is 1 if the sum 
            // equals 10, and 0 else.
			if (j < N-2) {
				tmp = (v[i][j] + v[i][j+1] + v[i][j+2]) == 10;
				friends += tmp;
			}
			// If two diagonal points in the downward right direction exist, ...
			if ((i < M-2) && (j < N-2)) {
				tmp = (v[i][j] + v[i+1][j+1] + v[i+2][j+2]) == 10;
				friends += tmp;
			}
			// If two diagonal points in the upward right direction exist, ...
			if ((i >= 2) && (j < N-2)) {
				tmp = (v[i][j] + v[i-1][j+1] + v[i-2][j+2]) == 10;
				friends += tmp;
			}
		}
	}
	return friends;
}
