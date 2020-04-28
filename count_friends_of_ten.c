int count_friends_of_ten(int M, int N, int** v) {
	int friends = 0;
	int tmp;
	for (int i = 0; i < M - 2; i++) {
		for (int j = 0; j < N - 2; j++) {
			tmp = v[i][j] + v[i+1][j] + v[i+2][j];
			if (tmp == 10) {
				friends++;
			}
			tmp = v[i][j] + v[i][j+1] + v[i][j+2];
			if (tmp == 10) {
				friends++;
			}
			tmp = v[i][j] + v[i+1][j+1] + v[i+2][j+2];
			if (tmp==10) {
				friends++;
			}
		}
	}
	return friends;
}