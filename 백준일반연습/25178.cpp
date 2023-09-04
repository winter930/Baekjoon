#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

int main()
{
	int N;
	string a;
	string b;

	cin >> N;
	cin >> a;
	cin >> b;

	if (a[0] != b[0] || a[N - 1] != b[N - 1])
	{
		cout << "NO";
		return 0;
	}
	
	string a2;
	string b2;
	string a3;
	string b3;

	

	for (int i = 1; i < N - 1; i++)
	{
		//for (char c : a) if (string("aeiou").find(c) == -1) a2.push_back(c); °¡´É ¹®ÀÚ¿­¼Ó ¹®ÀÚ ¹Ýº¹!!
		if (a[i] != 'a' && a[i] != 'e' && a[i] != 'i' && a[i] != 'o' && a[i] != 'u')
		{
			a2.append(1, a[i]);//or a2.push_back(a[i]);
		}
		else
		{
			a3.append(1, a[i]);
		}
		
		if (b[i] != 'a' && b[i] != 'e' && b[i] != 'i' && b[i] != 'o' && b[i] != 'u')
		{
			b2.append(1, b[i]);
		}
		else
		{
			b3.append(1, b[i]);
		}
	}

	sort(a3.begin(), a3.end());
	sort(b3.begin(), b3.end());

	if (a2.compare(b2) != 0 || a3.compare(b3) != 0)
	{
		cout << "NO";
		return 0;
	}
	
	cout << "YES";
	return 0;
}
