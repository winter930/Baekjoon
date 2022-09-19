#include<iostream>
#include<queue>
#include<algorithm>
#include<memory.h>

using namespace std;

int N, M;
int map[20][20];
int visited[20][20] = {};//0: ��湮   0:������   -1: �湮   -1: ���� ���

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

typedef struct shape {
	int minr;//���غ�� ��
	int minc;//���غ�� ��
	int rbnum;//������
	queue<pair<int, int>> block;
};

shape maxshape;

queue<pair<int, int>> rainbow;
queue<pair<int, int>> search_q;

void gravity() {
	int temp;
	for (int j = 0; j < N; j++) {
		int i, k;
		for (i = N - 1; i >= 1; i--) {
			if (map[i][j] == 6) {
				k = i - 1;
				break;
			}
		}
		while (i>=1 && k >=0) {
			if (map[k][j] == -1) {
				if (k <= 1) {
					break;
				}
				for (i = k -1; i >= 1; i--) {
					if (map[i][j] == 6) {
						k = i - 1;
						break;
					}
				}
				continue;
			}

			if (map[k][j] != 6) {
				map[i][j] = map[k][j];
				map[k][j] = 6;
				i--;
			}

			k--;
		}
	}
}

void rotate90() {
	int rotatemap[20][20] = {};
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			rotatemap[i][j] = map[j][N - 1 - i];
		}
	}
	memcpy(map, rotatemap, sizeof(map));
}

shape compare_shape(shape a, shape b) {
	if (a.block.size() < b.block.size()) {//ũ��
		return b;
	}

	if (a.block.size() == b.block.size()) {//ũ��
		if (a.rbnum < b.rbnum) {//��������ϼ�
			return b;
		}

		if (a.rbnum == b.rbnum) {//��������ϼ�
			if (a.minr < b.minr) {//��
				return b;
			}

			if (a.minr == b.minr) {//��
				if (a.minc < b.minc) {//��
					return b;
				}
			}
		}
	}

	return a;
}

shape BFS(int color, shape s) {
	shape temp = s;
	for (; !search_q.empty(); search_q.pop()) {
		for (int i = 0; i < 4; i++) {
			int r = search_q.front().first + dy[i];
			int c = search_q.front().second + dx[i];
			if (r > N -1 || r < 0 || c > N - 1 || c < 0) {//��� ����
				continue;
			}

			if (visited[r][c] == -1 || map[r][c] == -1 || map[r][c] == 6) {//�湮���� ���� ��, ���� ���, �����
				continue;
			}

			if (map[r][c] == color || map[r][c] == 0) {
				if (map[r][c] == 0) {//������
					rainbow.push({ r, c });
					temp.rbnum++;
				}
				visited[r][c] = -1;
				search_q.push({ r, c });

				if (map[r][c] != 0 && temp.minr >= r) {
					if (temp.minr > r || (temp.minr == r && temp.minc > c)) {
						temp.minr = r;
						temp.minc = c;
					}
				}
				
				temp.block.push({ r, c });
			}
		}
	}

	for (; !rainbow.empty(); rainbow.pop()) {
		visited[rainbow.front().first][rainbow.front().second] = 0;
	}

	return temp;
}

void findblock() {
	maxshape.minr = -1;
	maxshape.minc = -1;
	maxshape.rbnum = 0;
	int i, j;
	while (1) {
		int flag = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (visited[i][j] == 0 && map[i][j] >= 1 && map[i][j] <= 5) {
					visited[i][j] = -1;

					shape temp;
					temp.minr = i;
					temp.minc = j;
					temp.rbnum = 0;
					temp.block.push({ i, j });
					search_q.push({ i, j });
					maxshape = compare_shape(maxshape, BFS(map[i][j], temp));
				}
			}
		}
		if (flag == 0) {
			break;
		}
	}
	memset(visited, 0, sizeof(visited));
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	int score = 0;
	while (1) {
		findblock();
		if (maxshape.block.size() < 2) {
			break;
		}
		score += maxshape.block.size() * maxshape.block.size();
		for (; !maxshape.block.empty(); maxshape.block.pop()) {
			map[maxshape.block.front().first][maxshape.block.front().second] = 6;
		}
		gravity();
		rotate90();
		gravity();
	}
	
	cout << score;

	return 0;
}