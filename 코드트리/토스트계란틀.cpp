#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int N, L, R;
int board[50][50];

struct point{
    int r;
    int c;
};

int dr[4] = {0,1,0,-1};
int dc[4] = {1,0,-1,0};

void pb(){
    cout << "--------- print board -----------\n";
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void input(){
    cin >> N >> L >> R;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> board[i][j];
        }
    }
}

bool in_range(int r, int c){
    return 0<=r && r<N && 0<=c && c<N;
}

bool egg_chk(){
    bool flag = false;
    int visit[50][50] = {0,};
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(visit[i][j] == 1){
                continue;
            }

            int front = 0, rear = 1;
            vector<point> v;
            v.push_back({i,j});
            visit[i][j] = 1;
            int sum_egg = board[i][j];
            
            while(front < rear){
                for(int d=0; d<4; d++){
                    if(!in_range(v[front].r + dr[d], v[front].c + dc[d])
                        || visit[v[front].r + dr[d]][v[front].c + dc[d]] == 1){
                        continue;
                    }

                    int temp = abs(board[v[front].r][v[front].c] - board[v[front].r + dr[d]][v[front].c + dc[d]]);
                    if(L <= temp && temp <= R){
                        rear++;
                        v.push_back({v[front].r + dr[d], v[front].c + dc[d]});
                        visit[v[front].r + dr[d]][v[front].c + dc[d]] = 1;
                        sum_egg += board[v[front].r + dr[d]][v[front].c + dc[d]];
                    }
                }
                front++;
            }

            if(front == 1){
                continue;
            }
            
            if(!flag){
                flag = true;
            }
            for(int k=0; k<rear; k++){
                board[v[k].r][v[k].c] = sum_egg / rear;
            }
        }
    }

    return flag;
}

int main() {
    input();
    int ans = 0;
    while(egg_chk()){
        ans++;
    }

    cout << ans;
    return 0;
}
