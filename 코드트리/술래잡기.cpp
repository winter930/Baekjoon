#include <iostream>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;

int N, M, H, K;
vector<vector<queue<int>>> board;
vector<vector<int>> tree;
struct point{
    int r;
    int c;
    int d;
};

vector<int> runners(1);
point player;

int dr[4] = {-1,0,1,0};
int dc[4] = {0,1,0,-1};

void input(){
    cin >> N >> M >> H >> K;
    board = vector<vector<queue<int>>>(N + 1, vector<queue<int>>(N + 1));
    tree = vector<vector<int>>(N + 1, vector<int>(N + 1, 0));
    int x, y, d;
    for(int i=1; i<=M; i++){
        cin >> x >> y >> d;
        runners.push_back(d);
        board[x][y].push(i);
    }

    for(int i=0; i<H; i++){
        cin >> x >> y;
        tree[x][y] = 1;
    }

    player = {(N+1)/2, (N+1)/2, 0};
}

bool in_range(int r, int c){
    return 1<=r && r<=N && 1<=c && c<=N;
}

void running(){
    vector<point> v;
    for(int i= -3; i<=3; i++){
        for(int j=-3; j<=3; j++){
            if(abs(i)+abs(j) <= 3 && in_range(player.r + i, player.c + j) && board[player.r + i][player.c + j].size() > 0){
                v.push_back({player.r + i, player.c + j, (int)board[player.r + i][player.c + j].size()});
            }
        }
    }

    for(auto temp : v){
        for(int i=0; i<temp.d; i++){
            int n = board[temp.r][temp.c].front();
            board[temp.r][temp.c].pop();
            
            if(!in_range(temp.r + dr[runners[n]], temp.c + dc[runners[n]])){
                runners[n] = (runners[n] + 2) % 4;
            }

            int nr = temp.r + dr[runners[n]];
            int nc = temp.c + dc[runners[n]];
            if(player.r == nr && player.c == nc){
                board[temp.r][temp.c].push(n);
            }
            else{
                board[nr][nc].push(n);
            }
        }
    }
}

int chase(int k){
    int score = 0;
    int distance = 1;
    int dis_count = 0;
    bool flag_dir = true;//방향
    bool flag_cnt = true;//짝수번째 distance ++ or --

    for(int i=1; i<=k; i++){
        running();

        dis_count++;
        player.r += dr[player.d];
        player.c += dc[player.d];

        if(player.r == 1 && player.c == 1){
            player.d = player.d + 2;
            dis_count = 1;
            flag_cnt = false;
            flag_dir = false;
        }
        else if(player.r == (N+1)/2 && player.c == (N+1)/2){
            player.d = player.d - 2;
            dis_count = 0;
            flag_cnt = true;
            flag_dir = true;
        }

        if(dis_count == distance){
            dis_count = 0;
            if(flag_dir){
                flag_cnt ^= 1;
                if(flag_cnt){
                    distance++;
                }
                player.d = (player.d + 1) % 4;
            }
            else{
                flag_cnt ^= 1;
                if(flag_cnt){
                    distance--;
                }
                player.d = (player.d + 3) % 4;
            }
        }
        
        for(int j=0; j<3; j++){
            int nr = player.r + dr[player.d] * j;
            int nc = player.c + dc[player.d] * j;
            if(in_range(nr, nc) && board[nr][nc].size() > 0 && tree[nr][nc] == 0){
                score += i * (int)board[nr][nc].size();
                while(!board[nr][nc].empty()){
                    M--;
                    runners[board[nr][nc].front()] = -1;
                    board[nr][nc].pop();
                    if(M == 0){
                        return score;
                    }
                }
            }
        }
    }

    return score;
}


int main() {
    input();

    int ans = chase(K);

    cout << ans;

    return 0;
}
