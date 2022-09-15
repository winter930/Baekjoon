#include<iostream>
#include<stdio.h>
#include<queue>

using namespace std;

int N;
int max_value = 0;

typedef struct board {
	int block[20][20];
	int max_num;
	int count;
};

queue<board> q;

int find_max(board s) {
	q.push(s);

	while (q.front().count != 5) {
		for (int i = 0; i < 4; i++) {
			board temp = q.front();
			int sline, eline;
			switch (i)
			{
			case 0://우로 옮기기
				for (int n = 0; n < N; n++) {
					int pos = N - 1;
					int search = N - 2;
					while (search != -1) {
						if (temp.block[n][search] > 0) {//2이상 발견
							if (temp.block[n][pos] == temp.block[n][search]) {//수가 같은 경우
								temp.block[n][pos] *= 2;
								temp.block[n][search] = 0;
								if (temp.max_num < temp.block[n][pos]) {
									temp.max_num = temp.block[n][pos];
								}
								pos--;
							}
							else if (temp.block[n][pos] == 0) {//옮기는 경우
								temp.block[n][pos] = temp.block[n][search];
								temp.block[n][search] = 0;
								if (temp.max_num < temp.block[n][pos]) {
									temp.max_num = temp.block[n][pos];
								}
							}
							else {//수가 다른 경우
								pos--;
								if (pos != search) {
									temp.block[n][pos] = temp.block[n][search];
									temp.block[n][search] = 0;
								}
								if (temp.max_num < temp.block[n][pos]) {
									temp.max_num = temp.block[n][pos];
								}
							}
						}
						search--;
					}
				}
				break;
			case 1://아래로 옮기기
				for (int n = 0; n < N; n++) {
					int pos = N - 1;
					int search = N - 2;
					while (search != -1) {
						if (temp.block[search][n] > 0) {//2이상 발견
							if (temp.block[pos][n] == temp.block[search][n]) {//수가 같은 경우
								temp.block[pos][n] *= 2;
								temp.block[search][n] = 0;
								if (temp.max_num < temp.block[pos][n]) {
									temp.max_num = temp.block[pos][n];
								}
								pos--;
							}
							else if (temp.block[pos][n] == 0) {//옮기는 경우
								temp.block[pos][n] = temp.block[search][n];
								temp.block[search][n] = 0;
								if (temp.max_num < temp.block[pos][n]) {
									temp.max_num = temp.block[pos][n];
								}
							}
							else {//수가 다른 경우
								pos--;
								if (pos != search) {
									temp.block[pos][n] = temp.block[search][n];
									temp.block[search][n] = 0;
								}
								if (temp.max_num < temp.block[pos][n]) {
									temp.max_num = temp.block[pos][n];
								}
							}
						}
						search--;
					}
				}
				break;
			case 2://좌로 옮기기
				for (int n = 0; n < N; n++) {
					int pos = 0;
					int search = 1;
					while (search != N) {
						if (temp.block[n][search] > 0) {//2이상 발견
							if (temp.block[n][pos] == temp.block[n][search]) {//수가 같은 경우
								temp.block[n][pos] *= 2;
								temp.block[n][search] = 0;
								if (temp.max_num < temp.block[n][pos]) {
									temp.max_num = temp.block[n][pos];
								}
								pos++;
							}
							else if (temp.block[n][pos] == 0) {//옮기는 경우
								temp.block[n][pos] = temp.block[n][search];
								temp.block[n][search] = 0;
								if (temp.max_num < temp.block[n][pos]) {
									temp.max_num = temp.block[n][pos];
								}
							}
							else {//수가 다른 경우
								pos++;
								if (pos != search) {
									temp.block[n][pos] = temp.block[n][search];
									temp.block[n][search] = 0;
								}
								if (temp.max_num < temp.block[n][pos]) {
									temp.max_num = temp.block[n][pos];
								}
							}
						}
						search++;
					}
				}
				break;
			case 3://위로 옮기기
				for (int n = 0; n < N; n++) {
					int pos = 0;
					int search = 1;
					while (search != N) {
						if (temp.block[search][n] > 0) {//2이상 발견
							if (temp.block[pos][n] == temp.block[search][n]) {//수가 같은 경우
								temp.block[pos][n] *= 2;
								temp.block[search][n] = 0;
								if (temp.max_num < temp.block[pos][n]) {
									temp.max_num = temp.block[pos][n];
								}
								pos++;
							}
							else if (temp.block[pos][n] == 0) {//옮기는 경우
								temp.block[pos][n] = temp.block[search][n];
								temp.block[search][n] = 0;
								if (temp.max_num < temp.block[pos][n]) {
									temp.max_num = temp.block[pos][n];
								}
							}
							else {//수가 다른 경우
								pos++;
								if (pos != search) {
									temp.block[pos][n] = temp.block[search][n];
									temp.block[search][n] = 0;
								}
								if (temp.max_num < temp.block[pos][n]) {
									temp.max_num = temp.block[pos][n];
								}
							}
						}
						search++;
					}
				}
				break;
			}
			temp.count++;
			q.push(temp);
		}
		q.pop();
	}

	for (; !q.empty(); q.pop()) {
		if (max_value < q.front().max_num) {
			max_value = q.front().max_num;
		}
	}

	return max_value;
}

int main() {
	cin >> N;
	board init;
	init.max_num = 0;
	init.count = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> init.block[i][j];
			if (init.max_num < init.block[i][j]) {
				init.max_num = init.block[i][j];
			}
		}
	}

	cout << find_max(init);

	return 0;
}
