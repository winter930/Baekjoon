#include<cstdio>
#include<iostream>

using namespace std;

int main()
{
	int N;
	cin >> N;

	int num=1;
	for (int i = 1; i <= N; i++)
	{
		num *= i;
	}

	cout << num;

	return 0;
}
