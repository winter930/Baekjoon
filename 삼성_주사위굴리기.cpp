#include<iostream>
#include<queue>

using namespace std;

int N, M, x, y, K;

int map[21][21];
int dice[] = { 0, 0, 0, 0, 0, 0, 0 };

queue<int> mk;

int dx[] = { 0, 1, -1, 0, 0 };
int dy[] = { 0, 0, 0, -1, 1 };

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M >> y >> x >> K;
	int r, c, temp;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < K; i++) {
		cin >> temp;
		mk.push(temp);
	}

	for (; !mk.empty(); mk.pop()) {
		r = y + dy[mk.front()];
		c = x + dx[mk.front()];
		if (r < 0 || r > N - 1 || c < 0 || c > M - 1) {
			continue;
		}
		switch (mk.front()) {
		case 1://µ¿
			temp = dice[1];
			dice[1] = dice[4];
			dice[4] = dice[6];
			dice[6] = dice[3];
			dice[3] = temp;
			break;
		case 2://¼­
			temp = dice[1];
			dice[1] = dice[3];
			dice[3] = dice[6];
			dice[6] = dice[4];
			dice[4] = temp;
			break;
		case 3://ºÏ
			temp = dice[1];
			dice[1] = dice[5];
			dice[5] = dice[6];
			dice[6] = dice[2];
			dice[2] = temp;
			break;
		case 4://³²
			temp = dice[1];
			dice[1] = dice[2];
			dice[2] = dice[6];
			dice[6] = dice[5];
			dice[5] = temp;
			break;
		}

		if (map[r][c] != 0) {
			dice[6] = map[r][c];
			map[r][c] = 0;
		}
		else {
			map[r][c] = dice[6];
		}
		x = c;
		y = r;
		cout << dice[1] << endl;
	}

	return 0;
}