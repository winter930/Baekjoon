#include<iostream>
#include<set>
#include<vector>
#include<string>

using namespace std;

int N,K;
struct comp{
    bool operator() (string a, string b){
        return a > b;
    }
};

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> N >> K;
        string line;
        cin >> line;
        line += line.substr(0,N/4);
        
        set<string, comp> s;
        for(int i=0; i<N/4; i++){
            for(int j=0; j<4; j++){
                   s.insert( line.substr(i + j * (N/4) , N/4 ) );
            }
        }
        
        vector<string> v(s.begin(), s.end());
        cout << "#" << test_case << " " << stoi(v[K-1], nullptr, 16) << endl;
	}
    
    
    
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
