#include<iostream>

using namespace std;

int N;
int A[500][500];

int sand = 0;

int dy[] = {0, 1, 0, -1};
int dx[] = {-1, 0, 1, 0};

int ty[] = {-1, 1, 1, -1};
int tx[] = {-1, -1, 1, 1};

void tornado(int r, int c, int d) {
	int dir = d;
	int a = 0;
	//´ë°¢¼±
	for (int i = 0; i < 4; i++) {
		if (i < 2) {
			if (r + ty[(dir + i) % 4] >= 1 && r + ty[(dir + i) % 4] <= N && c + tx[(dir + i) % 4] >= 1 && c + tx[(dir + i) % 4] <= N) {
				A[r + ty[(dir + i) % 4]][c + tx[(dir + i) % 4]] += A[r][c] / 10;
			}
			else {
				sand += A[r][c] / 10;
			}
			a += A[r][c] / 10;
		}
		else {
			if (r + ty[(dir + i) % 4] >= 1 && r + ty[(dir + i) % 4] <= N && c + tx[(dir + i) % 4] >= 1 && c + tx[(dir + i) % 4] <= N) {
				A[r + ty[(dir + i) % 4]][c + tx[(dir + i) % 4]] += A[r][c] / 100;
			}
			else {
				sand += A[r][c] / 100;
			}
			a += A[r][c] / 100;
		}
	}

	//¿ÞÂÊ
	if (r + dy[(dir + 1) % 4] >= 1 && r + dy[(dir + 1) % 4] <= N && c + dx[(dir + 1) % 4] >= 1 && c + dx[(dir + 1) % 4] <= N) {
		A[r + dy[(dir + 1) % 4]][c + dx[(dir + 1) % 4]] += A[r][c] * 7 / 100;
	}
	else {
		sand += A[r][c] * 7 / 100;
	}
	a += A[r][c] * 7 / 100;

	if (r + dy[(dir + 1) % 4] * 2 >= 1 && r + dy[(dir + 1) % 4] * 2 <= N && c + dx[(dir + 1) % 4] * 2 >= 1 && c + dx[(dir + 1) % 4] * 2 <= N) {
		A[r + dy[(dir + 1) % 4] * 2][c + dx[(dir + 1) % 4] * 2] += A[r][c] / 50;
	}
	else {
		sand += A[r][c] / 50;
	}
	a += A[r][c] / 50;

	//¿À¸¥ÂÊ
	if (r + dy[(dir + 3) % 4] >= 1 && r + dy[(dir + 3) % 4] <= N && c + dx[(dir + 3) % 4] >= 1 && c + dx[(dir + 3) % 4] <= N) {
		A[r + dy[(dir + 3) % 4]][c + dx[(dir + 3) % 4]] += A[r][c] * 7 / 100;
	}
	else {
		sand += A[r][c] * 7 / 100;
	}
	a += A[r][c] * 7 / 100;

	if (r + dy[(dir + 3) % 4] * 2 >= 1 && r + dy[(dir + 3) % 4] * 2 <= N && c + dx[(dir + 3) % 4] * 2 >= 1 && c + dx[(dir + 3) % 4] * 2 <= N) {
		A[r + dy[(dir + 3) % 4] * 2][c + dx[(dir + 3) % 4] * 2] += A[r][c] / 50;
	}
	else {
		sand += A[r][c] / 50;
	}
	a += A[r][c] / 50;

	//Á¤¸é
	if (r + dy[dir] * 2 >= 1 && r + dy[dir] * 2 <= N && c + dx[dir] * 2 >= 1 && c + dx[dir] * 2 <= N) {
		A[r + dy[dir] * 2][c + dx[dir] * 2] += A[r][c] / 20;
	}
	else {
		sand += A[r][c] / 20;
	}
	a += A[r][c] / 20;

	if (r + dy[dir]>= 1 && r + dy[dir] <= N && c + dx[dir] >= 1 && c + dx[dir] <= N) {
		A[r + dy[dir]][c + dx[dir]] += A[r][c] - a;
	}
	else {
		sand += A[r][c] - a;
	}

	A[r][c] = 0;
}

int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
		}
	}

	int r = (N + 1) / 2, c = (N + 1) / 2;
	int distance = 1;
	int dir = 0;
	while (r != 1 || c != 1) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < distance; k++) {
				r += dy[dir];
				c += dx[dir];
				tornado(r, c, dir);

				if (r == 1 && c == 1) {
					j = 2;
					break;
				}
			}
			dir = (dir + 1) % 4;
		}
		distance++;
	}

	cout << sand;

	return 0;
}
