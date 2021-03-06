#include <bits/stdc++.h>

using namespace std;

const int Maxn = 107;

int n, b[Maxn];
string a;

int main()
{
	cin >> n >> a;
	for(int i = 1; i <= n; ++i)
		b[i] = a[i-1]-'0';
	for(int i = 1, j, fir = 0, cur; i < n; ++i)
	{
		fir += b[i];
		cur = 0;
		for(j = i+1; j <= n; ++j)
		{
			cur += b[j];
			if(cur == fir && j != n)
				cur = 0;
			else if(cur > fir) break;
		}
		if(j > n && cur == fir)
		{
			puts("YES");
			return 0;
		}
	}
	puts("NO");
	return 0;
}
