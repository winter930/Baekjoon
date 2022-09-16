#include<stdio.h>
#include<iostream>
#include<queue>

using namespace std;

int N, K, L;
int map[101][101];
int playtime = 0;

typedef struct movetime {
	int t;
	char dir;
};

typedef struct sbody {
	int r;
	int c;
};

queue<movetime> mt;
queue<sbody> sb;

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };
int d = 0;

int snakegame() {
	sbody temp;
	temp.r = 1;
	temp.c = 1;
	sb.push(temp);

	map[1][1] = 2;

	while (1) {
		if (!mt.empty()) {
			if (playtime == mt.front().t) {//-----mt�� empty�� ��� ��� �ǳ�
				switch (mt.front().dir)
				{
				case 'L':
					d = (d + 3) % 4;
					break;
				case 'D':
					d = (d + 1) % 4;
					break;
				}
				mt.pop();
			}
		}
		

		temp.r += dy[d];
		temp.c += dx[d];
		playtime++;
		if (temp.r > N || temp.r <1 || temp.c > N || temp.c < 1) {//���� ���� ���
			break;
		}

		if (map[temp.r][temp.c] == 2) {//���� ���� ���
			break;
		}

		
		if (map[temp.r][temp.c] != 1) {//����� ���� ���
			map[sb.front().r][sb.front().c] = 0;
			sb.pop();
		}
		map[temp.r][temp.c] = 2;
		sb.push(temp);
	}

	return playtime;
}

int main() {
	cin >> N >> K;
	for (int i = 0; i < K; i++) {
		int r, c;
		cin >> r >> c;
		map[r][c] = 1;
	}
	cin >> L;
	for (int i = 0; i < L; i++) {
		movetime temp;
		cin >> temp.t >> temp.dir;
		mt.push(temp);
	}

	cout << snakegame();

	return 0;
}