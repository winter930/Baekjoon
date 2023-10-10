#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int N, W, H, ans;
vector<vector<int>> board;
vector<int> wall_high;

void pb() {
	cout << "----------------- print board ----------------\n";
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cout << board[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void pwh() {
	cout << "--------------- print wall_high ----------------\n";
	for (auto v : wall_high) {
		cout << v << "\t";
	}
	cout << endl;
}

void input() {
	cin >> N >> W >> H;
	board = vector<vector<int>>(H, vector<int>(W));
	wall_high = vector<int>(W, H);
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> board[i][j];
			if (board[i][j] > 0 && wall_high[j] > i) {
				wall_high[j] = i;
			}
		}
	}
}

int dr[4] = { 0, 1, 0, -1 };
int dc[4] = { 1, 0, -1, 0 };

bool in_range(int r, int c) {
	return 0 <= r && r < H && 0 <= c && c < W;
}

struct point {
	int r;
	int c;
	int d;
};
int boom(int sr, int sc) {
	queue<point> q;
	q.push({ sr, sc, board[sr][sc] });
	board[sr][sc] = 0;
	int count = 1;

	while (!q.empty()) {
		int r = q.front().r;
		int c = q.front().c;
		int d = q.front().d;
		q.pop();

		for (int i = 0; i < 4; i++) {
			for (int j = 1; j < d; j++) {
				int nr = r + dr[i] * j;
				int nc = c + dc[i] * j;
				if (!in_range(nr, nc)
					|| board[nr][nc] == 0) {
					continue;
				}

				
				if (board[nr][nc] > 1) {
					q.push({ nr, nc, board[nr][nc] });
				}
				board[nr][nc] = 0;
				count++;
			}
		}
	}

	return count;
}

void down() {
	for (int j = 0; j < W; j++) {
		int top = -1;
		for (int i = H - 1; i >= 0; i--) {
			if (board[i][j] == 0) {
				top = i;
				break;
			}
		}

		for (int i = top - 1; i >= 0; i--) {
			if (board[i][j] > 0) {
				board[top--][j] = board[i][j];
				board[i][j] = 0;
			}
		}

		wall_high[j] = top + 1;
	}
}

void play(int n, int remain) {
	if (ans == 0) {
		return;
	}

	if (n == N) {
		if (ans > remain) {
			ans = remain;
		}
		return;
	}

	vector<vector<int>> cpy_b = board;
	vector<int> cpy_wh = wall_high;
	for (int i = 0; i < W; i++) {
		if (wall_high[i] == H) {
			continue;
		}

		int count = boom(wall_high[i], i);
		if (count == remain) {
			ans = 0;
			return;
		}
		down();
		play(n + 1, remain - count);
		board = cpy_b;
		wall_high = cpy_wh;
	}
}

int main(int argc, char** argv) {
	int test_case, T;
	cin >> T;
	for (test_case = 1; test_case <= T; test_case++) {
		input();
		int s = 0;
		for (int v : wall_high) {
			s += H - v;
		}
		ans = s;

		play(0, s);

		cout << "#" << test_case << " " << ans << endl;
	}

	return 0;
}
