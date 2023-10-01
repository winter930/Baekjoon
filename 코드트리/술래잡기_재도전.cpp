#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int ans = 0;
int N, M, H, K;//크기, 도망자 수, 트리 수 , 횟수
vector<vector<queue<int>>> board(100, vector<queue<int>>(100));//도망자 지도
int tree[100][100];//트리 지도
struct point{
    int r;
    int c;
    int d;
};
point player;//술래


int dr[4] = {-1,0,1,0};
int dc[4] = {0,1,0,-1};

void input(){
    cin >> N >> M >> H >> K;
    int x,y,d;
    for(int i=0; i<M; i++){
        cin >> x >> y >> d;
        board[x][y].push(d);
    }

    for(int i=0; i<H; i++){
        cin >> x >> y;
        tree[x][y] = 1;
    }

    player.r = N/2 + 1, player.c = N/2 + 1, player.d = 0;
}

void pb(){
    cout << "---------- print board --------------\n";
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cout << board[i][j].size() << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void pt(){
    cout << "---------- print tree --------------\n";
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cout << tree[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

bool in_range(int r, int c){
    return 1<=r && r<=N && 1<=c && c<=N;
}

vector<point> find_runner(){
    vector<point> v;
    queue<point> q;
    int visit[100][100] = {0, };
    
    q.push({player.r, player.c, 0});
    visit[player.r][player.c] = 1;

    while(!q.empty()){
        int r = q.front().r;
        int c = q.front().c;
        int d = q.front().d;
        if(board[r][c].size() > 0){
            v.push_back({r, c, (int)board[r][c].size()});
        }
        q.pop();
        if(d == 3){
            continue;
        }

        for(int i=0; i<4; i++){
            if(!in_range(r+dr[i], c+dc[i])
                || visit[r+dr[i]][c+dc[i]] == 1){
                continue;
            }
            
            visit[r+dr[i]][c+dc[i]] = 1;
            if(d == 3){
                continue;
            }
            q.push({r+dr[i], c+dc[i], d+1});
        }
    }

    return v;
}

void run(){
    vector<point> v = find_runner();
    for(auto temp : v){
        for(int i=0; i<temp.d; i++){
            int d = board[temp.r][temp.c].front();
            board[temp.r][temp.c].pop();
            if(!in_range(temp.r + dr[d], temp.c + dc[d])){
                d = (d+2)%4;
            }

            if(player.r == temp.r + dr[d] && player.c == temp.c + dc[d]){
                board[temp.r][temp.c].push(d);
            }
            else{
                board[temp.r + dr[d]][temp.c + dc[d]].push(d);
            }
        }
    }
}

int catch_runner(int k){
    int r = player.r, c = player.c, d = player.d, score = 0;
    for(int i=0; i<3; i++){
        if(in_range(r,c) && board[r][c].size() > 0 && tree[r][c] != 1){
            score += k * board[r][c].size();
            M -= board[r][c].size();
            board[r][c] = queue<int>();
        }
        r += dr[d];
        c += dc[d];
    }

    return score;
}

void move(){
    int distance = 1;
    int dis_move = 0;
    bool dis_plus = true, dis_change = false;
    for(int i=1; i<=K; i++){
        run();

        player.r += dr[player.d];
        player.c += dc[player.d];

        if(player.r == 1 && player.c == 1){
            player.d = (player.d + 2) % 4;
            dis_plus = false, dis_change = true;
            dis_move = 1;
        }
        else {
            dis_move++;
            if(dis_move == distance){
                if(dis_plus){
                    player.d = (player.d + 1) % 4;
                    if(dis_change){
                        distance++;
                    }
                }
                else{
                    player.d = (player.d + 3) % 4;
                    if(dis_change){
                        distance--;
                        if(distance == 0){//중앙에 왔을 때
                            player.d = (player.d + 3) % 4;
                            distance = 1;
                            dis_plus = true;
                        }
                    }
                }
                dis_change ^= 1;
                dis_move = 0;
            }
        }

        // cout << "before\n";
        // pb();
        ans += catch_runner(i);
        if(M == 0){
            break;
        }
        // cout << "after\n";
        // cout << ans << endl;
        // pb();
    }

}



int main() {
    input();
    // pt();
    // pb();
    move();
    cout << ans;
    return 0;
}
