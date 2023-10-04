#include <iostream>
#include <vector>

using namespace std;

int N;

struct work{
    int t;
    int p;
};
vector<work> v;
vector<bool> chk;

void input(){
    cin >> N;
    int t,p;
    for(int i=0; i<N; i++){
        cin >> t >> p;
        v.push_back({t,p});
    }
    chk = vector<bool>(N, false);
}

void pv(){
    for(auto a : v){
        cout << a.t << " " << a.p << "\n";
    }
    cout << endl;
}

int ans = 0;
void dfs(int idx, int n, int sp){
    if(n<0){
        return;
    }

    for(int i=idx; i<N; i++){
        if(i + v[i].t <= N && n - v[i].t >= 0){
            dfs(i + v[i].t, n - v[i].t, sp + v[i].p);
        }
    }
    if(ans < sp){
        ans = sp;
    }
}

int main() {
    input();
    dfs(0,N,0);
    cout << ans;
    return 0;
}
