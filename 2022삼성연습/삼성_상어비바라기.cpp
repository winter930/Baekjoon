#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>

using namespace std;

int N, M;
int map[51][51];
int rain[51][51] = {0,};

queue<pair<int, int>> cmd;
queue<pair<int, int>> cloud;
queue<pair<int, int>> water;

// 0  1좌   3상   5우   7하
int dx[9] = {0, -1, -1 , 0, 1, 1, 1, 0, -1};
int dy[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}

	cloud.push({ N, 1 });
	cloud.push({ N, 2 });
	cloud.push({ N - 1, 1 });
	cloud.push({ N - 1, 2 });

	int d, s;
	for (int i = 0; i < M; i++) {
		cin >> d >> s;
		cmd.push({ d, s });
	}

	for (; !cmd.empty(); cmd.pop()) {
		//비내리기
		for (; !cloud.empty(); cloud.pop()) {
			int r = cloud.front().first + dy[cmd.front().first] * cmd.front().second;
			int c = cloud.front().second + dx[cmd.front().first] * cmd.front().second;

			if (r > N) {
				r = r % N;
			}
			if (c > N) {
				c = c % N;
			}
			if (r < 1) {
				r = N + r % N;
			}
			if (c < 1) {
				c = N + c % N;
			}

			water.push({ r, c });

			map[r][c]++;
			rain[r][c] = 1;
		}

		//물복사
		for (; !water.empty(); water.pop()) {
			for (int i = 1; i <= 4; i++) {
				int r = water.front().first + dy[2 * i];
				int c = water.front().second + dx[2 * i];
				if (r <= N && c <= N && r >= 1 && c >= 1) {
					if (map[r][c] > 0) {
						map[r - dy[2 * i]][c - dx[2 * i]]++;
					}
				}
				
			}
		}

		//구름 생성
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (map[i][j] >= 2 && rain[i][j] != 1) {
					cloud.push({ i, j });
					map[i][j] -= 2;
				}
			}
		}
		
		memset(rain, 0, sizeof(rain));
	}

	int sum = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			sum += map[i][j];
		}
	}

	cout << sum;

	return 0;
}
