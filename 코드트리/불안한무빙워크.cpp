#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int N, K;
vector<int> belt;
deque<int> person;
int start = 0;

void input(){
    cin >> N >> K;
    belt = vector<int>(2*N);
    for(int i=0; i<2*N; i++){
        cin >> belt[i];
    }
}

void pb(){
    for(int i=0; i<N*2; i++){
        cout << belt[i] << "\t";
    }
    cout << endl;

    for(int i=0; i<start; i++){
        cout << "\t";
    }
    cout << "s" << endl;

    int temp = 0;
    for(int i=0; i<person.size(); i++){
        cout << person[i] << "\t";
    }
    cout << endl;

    cout << (start+N-1) % (2*N) << endl;
}

void belt_moving(){
    if(start > 0){
        start--;
    }
    else{
        start = 2 * N - 1;
    }
}

void person_moving(){
    int finish = (start+N-1) % (2*N);
    for(int i=0; i<person.size();){
        if(person[i] == finish){//벨트 이동 후 마지막 칸인 경우
            person.pop_front();
            continue;
        }

        if(belt[(person[i] + 1) % (2*N)] == 0                       //앞의 칸의 안정성이 0인 경우
            || (i != 0 && person[i-1] == (person[i] + 1) % (2*N))){ //앞에 사람이 있는 경우      
            i++;
            continue;
        }
        

        person[i] = (person[i] + 1) % (2*N);
        belt[person[i]]--;
        if(belt[person[i]] == 0){
            K--;
        }
        if(person[i] == finish){//사람 이동 후 마지막 칸인 경우
            person.pop_front();
            continue;
        }
        i++;
    }
}

void add_person(){
    if(person.size() > 0 && start == person[person.size() - 1]){
        return;
    }

    if(belt[start] > 0){
        person.push_back(start);
        belt[start]--;
        if(belt[start] == 0){
            K--;
        }
    }
}

void test(){
    belt_moving();
    person_moving();
    add_person();
    //pb();
}

int main() {
    input();
    int ans = 0;
    while(K > 0){
        ans++;
        test();
    }

    cout << ans;
    return 0;
}
