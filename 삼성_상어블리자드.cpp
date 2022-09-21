#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int N, M;

//0:±¸½½ 1:Ä­¹øÈ£
int map[2][51][51];

int shark;

//ÁÂÇÏ¿ì»ó
int dx[] = { -1,0, 1, 0 };
int dy[] = { 0,1, 0, -1 };

void remake_bubble() {
	queue<pair<int, int>> bubble_group;
	int x = shark - 1, y = shark, count = 0, dir = 1;
	int target = map[0][y][x];

	int dirb = dir;
	int by = y;
	int bx = x;
	while (1) {
		y += dy[dir];
		x += dx[dir];

		if (map[0][y][x] == target) {
			count++;
		}
		else {
			bubble_group.push({ target, count + 1 });
			for (int i = 0; i <= count; i++) {
				map[0][by][bx] = 0;
				if (map[1][by][bx] + 1 != map[1][by + dy[dirb]][bx + dx[dirb]]) {
					dirb = (dirb + 1) % 4;
				}
				by += dy[dirb];
				bx += dx[dirb];
			}
			count = 0;
			dirb = dir;
			by = y;
			bx = x;
			target = map[0][y][x];
			if (target == 0) {
				break;
			}
		}

		if (map[1][y][x] == N * N - 1) {
			bubble_group.push({ target, count + 1 });
			for (int i = 0; i <= count; i++) {
				map[0][by][bx] = 0;
				if (map[1][by][bx] + 1 != map[1][by + dy[dirb]][bx + dx[dirb]]) {
					dirb = (dirb + 1) % 4;
				}
				by += dy[dirb];
				bx += dx[dirb];
			}
			break;
		}

		if (map[1][y][x] + 1 != map[1][y + dy[dir]][x + dx[dir]]) {
			dir = (dir + 1) % 4;
		}
	}

	x = shark - 1, y = shark, dir = 1;
	while (!bubble_group.empty()) {
		map[0][y][x] = bubble_group.front().second;
		if (map[1][y][x] == N * N - 1) {
			break;
		}
		if (map[1][y][x] + 1 != map[1][y + dy[dir]][x + dx[dir]]) {
			dir = (dir + 1) % 4;
		}
		y += dy[dir];
		x += dx[dir];

		map[0][y][x] = bubble_group.front().first;
		if (map[1][y][x] == N * N - 1) {
			break;
		}
		if (map[1][y][x] + 1 != map[1][y + dy[dir]][x + dx[dir]]) {
			dir = (dir + 1) % 4;
		}
		y += dy[dir];
		x += dx[dir];

		bubble_group.pop();
	}
}

int boom() {
	int score = 0;
	int x = shark - 1, y = shark, count = 0, dir = 1;
	int target = map[0][y][x];

	int dirb = dir;
	int by = y;
	int bx = x;
	while (1) {
		y += dy[dir];
		x += dx[dir];

		if (map[0][y][x] == target) {
			count++;
		}
		else {
			if (count >= 3) {
				score += target * (count + 1);
				for (int i = 0; i <= count; i++) {
					map[0][by][bx] = 0;
					if (map[1][by][bx] + 1 != map[1][by + dy[dirb]][bx + dx[dirb]]) {
						dirb = (dirb + 1) % 4;
					}
					by += dy[dirb];
					bx += dx[dirb];
				}
			}
			count = 0;
			dirb = dir;
			by = y;
			bx = x;
			target = map[0][y][x];
			if (target == 0) {
				break;
			}
		}


		if (map[1][y][x] == N * N - 1) {
			if (count >= 3) {
				score += target * (count + 1);
				for (int i = 0; i <= count; i++) {
					map[0][by][bx] = 0;
					if (map[1][by][bx] + 1 != map[1][by + dy[dirb]][bx + dx[dirb]]) {
						dirb = (dirb + 1) % 4;
					}
					by += dy[dirb];
					bx += dx[dirb];
				}
			}
			break;
		}

		if (map[1][y][x] + 1 != map[1][y + dy[dir]][x + dx[dir]]) {
			dir = (dir + 1) % 4;
		}
	}

	return score;
}

void moving() {
	int sr = shark, sc = shark - 1;
	int dirs = 1, dirm;
	while (map[1][sr][sc] != N * N - 1) {//ÃÖÃÊ 0 À§Ä¡ Å½»ö
		if (map[0][sr][sc] == 0) {
			if (map[1][sr][sc] + 1 != map[1][sr + dy[dirs]][sc + dx[dirs]]) {
				dirs = (dirs + 1) % 4;
			}
			dirm = dirs;
			break;
		}

		if (map[1][sr][sc] + 1 != map[1][sr + dy[dirs]][sc + dx[dirs]]) {
			dirs = (dirs + 1) % 4;
		}
		sr += dy[dirs];
		sc += dx[dirs];
	}

	int mr = sr + dy[dirm];
	int mc = sc + dx[dirm];

	while (1) {
		if (map[0][mr][mc] != 0) {
			map[0][sr][sc] = map[0][mr][mc];
			map[0][mr][mc] = 0;
			if (map[1][sr][sc] + 1 != map[1][sr + dy[dirs]][sc + dx[dirs]]) {
				dirs = (dirs + 1) % 4;
			}
			sr += dy[dirs];
			sc += dx[dirs];
		}

		if (map[1][mr][mc] == N * N - 1) {
			break;
		}

		if (map[1][mr][mc] + 1 != map[1][mr + dy[dirm]][mc + dx[dirm]]) {
			dirm = (dirm + 1) % 4;
		}
		mr += dy[dirm];
		mc += dx[dirm];
	}
}


void shooting(int d, int s) {
	int dir;
	switch (d) {
	case 1:
		dir = 3;
		break;
	case 2:
		dir = 1;
		break;
	case 3:
		dir = 0;
		break;
	case 4:
		dir = 2;
		break;
	default:
		break;
	}

	int x = shark, y = shark;
	for (int i = 0; i < s; i++) {
		y += dy[dir];
		x += dx[dir];
		map[0][y][x] = 0;
	}
}

int main() {
	cin >> N >> M;
	shark = (N + 1) / 2;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[0][i][j];
		}
	}

	int x = shark, y = shark, dir=0, turn_count = 2, distance = 1;
	
	for (int i = 1; i < N * N;) {
		for (int j = 0; j < distance; j++) {
			x += dx[dir];
			y += dy[dir];
			map[1][y][x] = i++;
			if (i == N * N) {
				break;
			}
		}
		turn_count--;
		if (turn_count == 0) {
			turn_count = 2;
			distance++;
		}
		dir = (dir + 1) % 4;
	}

	int d, s;
	queue<pair<int, int>> magic;
	for (int i = 0; i < M; i++) {
		cin >> d >> s;
		magic.push({ d, s });
	}

	int boom_score = 0;
	for (; !magic.empty(); magic.pop()) {
		shooting(magic.front().first, magic.front().second);
		moving();
		while (int i = boom()) {
			boom_score += i;
			moving();
		}
		remake_bubble();
	}

	cout << boom_score;

	return 0;
}