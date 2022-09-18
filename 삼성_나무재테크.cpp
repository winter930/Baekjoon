#include<iostream>
#include<vector>

using namespace std;

int N, M, K;
int A[11][11];
int map1[11][11];
int treemap[11][11];

vector<int> map2[11][11];
vector<pair<int, int>> tp;

int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};

int main() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			map1[i][j] = 5;
			cin >> A[i][j];
		}
	}

	int x, y, t;
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> t;
		treemap[x][y] = 1;
		tp.emplace_back(x, y);
		map2[x][y].emplace_back(t);
	}

	for (int i = 0; i < K; i++) {
		//봄, 여름
		for (int j = 0; j < tp.size(); ) {//나무가 있는 칸 만큼 반복
			int cx = tp.at(j).first;
			int cy = tp.at(j).second;

			int da = 0;//죽은 나무 양분
			for (int h = map2[cx][cy].size() - 1; h >= 0 ; h--) {//칸의 나무개수만큼 반복
				if (map1[cx][cy] >= map2[cx][cy].at(h)) {
					map1[cx][cy] -= map2[cx][cy].at(h);
					map2[cx][cy].at(h)++;
				}
				else {
					da += map2[cx][cy].at(h) / 2;
					map2[cx][cy].erase(map2[cx][cy].begin() + h);
					treemap[cx][cy]--;
					M--;
				}

				if (h == 0 && da > 0) {
					map1[cx][cy] += da;
					da = 0;
				}
			}

			if (treemap[cx][cy] == 0) {
				tp.erase(tp.begin() + j);
				continue;
			}
			j++;
		}

		int tsize = tp.size();
		for (int j = 0; j < tsize; j++) {
			int cx = tp.at(j).first;
			int cy = tp.at(j).second;

			//가을
			for (int h = map2[cx][cy].size() - 1; h >= 0; h--) {//칸의 나무개수만큼 반복
				if (map2[cx][cy].at(h) % 5 == 0) {
					for (int g = 0; g < 8; g++) {
						if (cx + dx[g] <= N && cx + dx[g] > 0 && cy + dy[g] <= N && cy + dy[g] > 0) {
							if (treemap[cx + dx[g]][cy + dy[g]] == 0) {
								tp.emplace_back(cx + dx[g], cy + dy[g]);
							}
							map2[cx + dx[g]][cy + dy[g]].emplace_back(1);
							treemap[cx + dx[g]][cy + dy[g]]++;
							M++;
						}
					}
				}
			}
		}

		//겨울
		for (int j = 1; j <= N; j++) {
			for (int h = 1; h <= N; h++) {
				map1[j][h] += A[j][h];
			}
		}
	}

	cout << M;

	return 0;
}