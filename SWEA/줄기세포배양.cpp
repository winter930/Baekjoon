#include<iostream>
#include<vector>
#include<algorithm>
#include<map>

using namespace std;

int N, M, K;
vector<vector<int>> board;

struct plant {
	int r;
	int c;
	int x;//생명력
	int t;//활성화시간
};
vector<plant> plants;//비활성화 + 활성화 식물

void pb() {
	cout << "------------- print board -----------\n";
	for (int i = 0; i < N + K; i++) {
		for (int j = 0; j < M + K; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void input() {
	plants.clear();

	cin >> N >> M >> K;
	board = vector<vector<int>>(K + N, vector<int>(K + M));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i+K/2][j+K/2];
			if (board[i + K/2][j + K/2] > 0) {
				plants.push_back({ i+K/2, j+K/2, board[i + K/2][j + K/2], board[i + K/2][j + K/2] });
			}
		}
	}
}

void chk_die(int k) {
	for (int i = 0; i < (int)plants.size();) {
		if (k == plants[i].x + plants[i].t) {
			plants.erase(plants.begin() + i);
			continue;
		}

		i++;
	}
}

int dr[4] = { 0,1,0,-1 };
int dc[4] = { 1,0,-1,0 };


void increase(int k) {
	vector<vector<int>> visit = board;
	map<pair<int, int>, int> m;
	for (int i = 0; i < (int)plants.size(); i++) {
		if (plants[i].t < k) {
			for (int j = 0; j < 4; j++) {
				int nr = plants[i].r + dr[j];
				int nc = plants[i].c + dc[j];
				if (board[nr][nc] > 0) {
					continue;
				}

				if (visit[nr][nc] > 0) {
					if (visit[nr][nc] < plants[i].x) {
						visit[nr][nc] = plants[i].x;
						m[{nr, nc}] = plants[i].x;
					}
				}
				else {
					visit[nr][nc] = plants[i].x;
					m[{nr, nc}] = plants[i].x;
				}
			}
		}
	}

	board = visit;
	for (auto temp = m.begin(); temp != m.end(); temp++) {
		plants.push_back({ temp->first.first, temp->first.second, temp->second, temp->second + k });
	}
}


int main(int argc, char** argv) {
	int test_case, T;
	cin >> T;
	for (test_case = 1; test_case <= T; test_case++) {
		input();
		for (int i = 1; i <= K; i++) {
			increase(i);
			chk_die(i);
			//pb();
		}

		cout << "#" << test_case << " " << plants.size() << endl;
	}

	return 0;
}
