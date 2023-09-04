#include <iostream>

using namespace std;

int main() {
	int N;
	int M;
	int start;
	int K;
	int ans;

	cin >> N >> M >> K;

	if (M - 3 < 1)
	{
		start = N + M - 3;
	}
	else
	{
		start = M - 3;
	}

	int count = K % N;

	ans = (start + count) % N;

	if (ans < 1) { ans += N; }

	cout << ans;

	return 0;
}
