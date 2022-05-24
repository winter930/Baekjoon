#include<cstdio>
#include<iostream>

using namespace std;

int main()
{
	int N, M;
	cin >> N >> M;

	int* a;
	int* b;

	a = (int*)malloc(sizeof(int) * N);
	b = (int*)malloc(sizeof(int) * M);

	for (int i = 0; i < N; i++)
	{
		cin >> a[i];
	}
	for (int i = 0; i < M; i++)
	{
		cin >> b[i];
	}

	int maxvalue = 0;
	for (int i = 0; i < M; i++)
	{
		if (i == N)
		{
			for (int j = N; j < M; j++)
			{
				if (maxvalue < b[j])
				{
					maxvalue = b[j];
				}
			}
			break;
		}

		//max(maxvalue, b[i] - a[i]) 사용해도 된다.
		if (a[i] < b[i] && maxvalue < b[i] - a[i])
		{
			maxvalue = b[i] - a[i];
		}
	}
	cout << maxvalue;

	free(a);
	free(b);
	return 0;
}

