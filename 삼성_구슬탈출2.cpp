#include<stdio.h>
#include<iostream>
#include<queue>

using namespace std;

int dirx[4] = {1, 0, -1, 0};
int diry[4] = {0, 1, 0, -1};

typedef struct point {
	int rx;
	int ry;
	int bx;
	int by;
	int count;
};

queue<point> ballpoint;

int visited[10][10][10][10];

int N;
int M;
char board[10][10];

int BFS(point start) {
	ballpoint.push(start);

	visited[start.ry][start.rx][start.by][start.bx] = 1;


	while (!ballpoint.empty()) {
		for (int dir = 0; dir < 4; dir++) {
			int nrx, nry, nbx, nby, c;
			nrx = ballpoint.front().rx;
			nry = ballpoint.front().ry;
			nbx = ballpoint.front().bx;
			nby = ballpoint.front().by;
			c = ballpoint.front().count;

			int rd = 0;
			int bd = 0;

			int redflag = 0;
			int blueflag = 0;

			while (redflag != 1 || blueflag != 1) {
				if (board[nry + diry[dir]][nrx + dirx[dir]] != '#' && board[nry][nrx] != 'O') {
					nry += diry[dir];
					nrx += dirx[dir];
					rd++;
				}
				else {
					redflag = 1;
				}

				if (board[nby + diry[dir]][nbx + dirx[dir]] != '#' && board[nby][nbx] != 'O') {
					nby += diry[dir];
					nbx += dirx[dir];
					bd++;
				}
				else {
					blueflag = 1;
				}
			}

			if (board[nby][nbx] == 'O') {
				continue;
			}

			if (board[nry][nrx] == 'O') {
				return c + 1;
			}

			if (nrx == nbx && nry == nby) {
				if (rd > bd) {
					nrx -= dirx[dir];
					nry -= diry[dir];
				}
				else {
					nbx -= dirx[dir];
					nby -= diry[dir];
				}
			}

			if (visited[nry][nrx][nby][nbx] == 1) {
				continue;
			}

			//카운트++
			c += 1;
			if (c >= 10) {
				continue;
			}

			//경로표시, push
			visited[nry][nrx][nby][nbx] = 1;
			ballpoint.push({ nrx,nry,nbx,nby,c });
		}
		ballpoint.pop();
	}
	return -1;
}

int main() {
	point s;

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
			if (board[i][j] == 'R') {
				s.rx = j;
				s.ry = i;
			}

			if (board[i][j] == 'B') {
				s.bx = j;
				s.by = i;
			}
		}
	}
	s.count = 0;

	cout << BFS(s);

	return 0;
}
