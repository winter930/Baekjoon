#include<stdio.h>
#include<iostream>
#include<queue>

using namespace std;

int N, M;
int r, c, d;

int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };

enum State {
	cleaning,
	searching,
	back,
	stop
};

// 0: Ã»¼ÒÀü: 1  º® 2: Ã»¼ÒÈÄ
int map[50][50];

int clean(int sr, int sc, int sd) {
	int nr = sr;
	int nc = sc;
	int nd = sd;
	int flagd = 0;
	int count = 0;
	State s = cleaning;

	while (1) {
		switch (s) {
		case cleaning:
			map[nr][nc] = 2;
			count++;
			s = searching;
			break;
		case searching:
			if (flagd == 4) {
				if (map[nr + dy[(nd + 2) % 4]][nc + dx[(nd + 2) % 4]] == 1) {
					s = stop;
					continue;
				}
				else {
					s = back;
					flagd = 0;
					continue;
				}
			}

			if (map[nr + dy[(nd + 3) % 4]][nc + dx[(nd + 3) % 4]] == 0) {
				nd = (nd + 3) % 4;
				flagd = 0;
				nr += dy[nd];
				nc += dx[nd];
				s = cleaning;
				continue;
			}
			else {
				nd = (nd + 3) % 4;
				flagd++;
			}
			break;
		case back:
			nr += dy[(nd + 2) % 4];
			nc += dx[(nd + 2) % 4];
			s = searching;
			break;
		case stop:
			return count;
			break;
		}
	}
}

int main() {
	cin >> N >> M;
	cin >> r >> c >> d;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	cout << clean(r, c, d);
	return 0;
}
