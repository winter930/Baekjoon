#include<iostream>
#include<algorithm>

using namespace std;

int N, M;
int map[500][500];
int maxvalue = 0;

int tetromino1() {//막대모양
	int s = 0;
	for (int i = 0; i <= N - 4; i++) {//세로모양
		for (int j = 0; j < M; j++) {
			s = max(s, map[i][j] + map[i + 1][j] + map[i + 2][j] + map[i + 3][j]);
		}
	}

	for (int i = 0; i < N; i++) {//가로모양
		for (int j = 0; j <= M-4; j++) {
			s = max(s, map[i][j] + map[i][j + 1] + map[i][j + 2] + map[i][j + 3]);
		}
	}
	return s;
}

int tetromino2() {//사각형
	int s = 0;
	for (int i = 0; i <= N-2; i++) {
		for (int j = 0; j <= M - 2; j++) {
			s = max(s, map[i][j] + map[i + 1][j] + map[i][j + 1] + map[i + 1][j + 1]);
		}
	}
	return s;
}

int tetromino3() {//ㄱ모양
	int s = 0;
	for (int i = 0; i <= N -3; i++) {//세로모양
		for (int j = 0; j <= M - 2; j++) {
			s = max(s, map[i][j] + map[i + 1][j] + map[i + 2][j] + map[i][j + 1]);
			s = max(s, map[i][j] + map[i + 1][j] + map[i + 2][j] + map[i + 2][j + 1]);
			s = max(s, map[i][j + 1] + map[i + 1][j + 1] + map[i + 2][j + 1] + map[i][j]);
			s = max(s, map[i][j + 1] + map[i + 1][j + 1] + map[i + 2][j + 1] + map[i + 2][j]);

		}
	}

	for (int i = 0; i <= N - 2; i++) {
		for (int j = 0; j <= M - 3; j++) {
			s = max(s, map[i][j] + map[i][j + 1] + map[i][j + 2] + map[i + 1][j]);
			s = max(s, map[i][j] + map[i][j + 1] + map[i][j + 2] + map[i + 1][j + 2]);
			s = max(s, map[i + 1][j] + map[i + 1][j + 1] + map[i + 1][j + 2] + map[i][j]);
			s = max(s, map[i + 1][j] + map[i + 1][j + 1] + map[i + 1][j + 2] + map[i][j + 2]);
		}
	}
	return s;
}

int tetromino4() {//ㄴㄱ모양
	int s = 0;
	for (int i = 0; i <= N - 3; i++) {
		for (int j = 0; j <= M - 2; j++) {
			s = max(s, map[i][j] + map[i + 1][j] + map[i + 1][j + 1] + map[i + 2][j + 1]);
			s = max(s, map[i][j + 1] + map[i + 1][j + 1] + map[i + 1][j] + map[i + 2][j]);
		}
	}

	for (int i = 0; i <= N - 2; i++) {
		for (int j = 0; j <= M - 3; j++) {
			s = max(s, map[i][j] + map[i][j + 1] + map[i + 1][j + 1] + map[i + 1][j + 2]);
			s = max(s, map[i + 1][j] + map[i + 1][j + 1] + map[i][j + 1] + map[i][j + 2]);
		}
	}
	return s;
}

int tetromino5() {//ㅗ모양
	int s = 0;
	for (int i = 0; i <= N - 3; i++) {
		for (int j = 0; j <= M - 2; j++) {
			s = max(s, map[i][j] + map[i + 1][j] + map[i + 2][j] + map[i + 1][j + 1]);
			s = max(s, map[i][j + 1] + map[i + 1][j + 1] + map[i + 2][j + 1] + map[i + 1][j]);
		}
	}

	for (int i = 0; i <= N - 2; i++) {
		for (int j = 0; j <= M - 3; j++) {
			s = max(s, map[i][j] + map[i][j + 1] + map[i][j + 2] + map[i + 1][j + 1]);
			s = max(s, map[i + 1][j] + map[i + 1][j + 1] + map[i + 1][j + 2] + map[i][j + 1]);
		}
	}
	return s;
}

int solution() {
	maxvalue = max({ tetromino1(),tetromino2(),tetromino3(),tetromino4(),tetromino5() });

	return maxvalue;
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	cout << solution() << endl;

	return 0;
}
