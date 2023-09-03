//백준 17142 연구소3

#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

int N, M;
vector<vector<int>> board(50, vector<int>(50, 0));

int dr[4] = { 0,1,0,-1 };
int dc[4] = { 1,0,-1,0 };

struct point {
	int r;
	int c;
};
vector<point> virus;
vector<bool> pre;

int min_time = 2500;
void BFS(vector<vector<int>> b) {
	int t = 0;
	queue<pair<point, int>> q;
	for (int i = 0; i < pre.size(); i++) {
		if (pre[i]) {
			b[virus[i].r][virus[i].c] = -1;
			q.push({ virus[i],0 });
			if (q.size() == M) {
				break;
			}
		}
	}

	while (!q.empty()) {
		int r = q.front().first.r;
		int c = q.front().first.c;
		int d = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			if (r + dr[i] < 0 || r + dr[i] >= N || c + dc[i] < 0 || c + dc[i] >= N
				|| b[r + dr[i]][c + dc[i]] == -1
				|| b[r + dr[i]][c + dc[i]] > 0) {
				continue;
			}

			if (b[r + dr[i]][c + dc[i]] == -2) {
				b[r + dr[i]][c + dc[i]] = -1;
			}
			else {
				if (t < d + 1) {
					t = d + 1;
					if (t >= min_time) {
						return;
					}
				}
				b[r + dr[i]][c + dc[i]] = d + 1;
			}
			q.push({ { r + dr[i], c + dc[i] }, d + 1 });
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (b[i][j] == 0) {
				return;
			}
		}
	}

	min_time = t;
	return;
}

int main() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
			if (board[i][j] == 2) {
				virus.push_back({ i, j });
				board[i][j] = -2;
			}
			else if (board[i][j] == 1) {
				board[i][j] = -1;
			}
		}
	}

	pre = vector<bool>(virus.size(), false);
	for (int i = 0; i < M; i++) {
		pre[i] = true;
	}

	do {
		BFS(board);
		if (min_time == 0) {
			break;
		}
	} while (prev_permutation(pre.begin(), pre.end()));//vCm

	if (min_time == 2500) {
		min_time = -1;
	}
	cout << min_time;


	return 0;
}
