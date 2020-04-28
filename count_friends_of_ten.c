int count_friends_of_ten(int M, int N, int** v) {
	int friends = 0;
	int tmp;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (i < M-2) {
				tmp = (v[i][j] + v[i+1][j] + v[i+2][j]) == 10;
				friends += tmp;
			}	
			if (j < N-2) {
				tmp = (v[i][j] + v[i][j+1] + v[i][j+2]) == 10;
				friends += tmp;
			}
			if (i < M-2 && j < N-2) {
				tmp = (v[i][j] + v[i+1][j+1] + v[i+2][j+2]) == 10;
				friends += tmp;
			}
			if (i >= 2 && j >= 2) {
				tmp = (v[i][j] + v[i-1][j-1] + v[i-2][j-2]) == 10;
				friends += tmp;
			}
		}
	}
	return friends;
}
