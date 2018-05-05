#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

const int Maxn = 65 + 2;

int n, sum, maxl, need_l,need_n;
int a[Maxn];
bool vis[Maxn];

inline int getint();

bool dfs(int pre_n,int now_l,int now_n)
{
	if(now_n == need_n) return true;
	if(now_l == need_l) return dfs(0,0,now_n+1);
	if(need_l - now_l < a[n-1]) return false;

	for(int i = pre_n, faith = 0; i < n; ++i)
	{
		if(vis[i] || faith == a[i] || a[i] + now_l > need_l) continue;

		vis[i] = true;
		if( dfs(i+1,a[i]+now_l,now_n) ) return true;
		vis[i] = false;
		// there may be two sticks have same length
		faith = a[i];
		// first dfs we must chose first stick
		// wether next has two stick add == a[i], it can't
		if(now_l == 0 || now_l+a[i] == need_l) return false;
	}
	return false;
}

int main()
{
	n = getint();
	for(register int i = 0; i < n; ++i)
		if((a[i] = getint()) > 50) { --n; --i; }
		else { sum += a[i]; if(a[i] > maxl) maxl = a[i]; }

	sort(a,a+n); reverse(a,a+n);

	for(need_l = maxl; need_l <= sum/2; ++need_l)
	{
		if(sum % need_l) continue;
		memset(vis,0,sizeof vis);
		need_n = sum / need_l;
		if(dfs(0,0,0))
		{
			printf("%d\n",need_l);
			return 0;
		}
	}
	printf("%d\n",sum); // need_l == sum
	return 0;
}

inline int getint()
{
	char c;
	while((c=getchar()) < '0' || c > '9');
	int res = c - '0';
	while((c=getchar()) >= '0' && c <='9') res = (res<<1) + (res<<3) + c -'0';
	return res;
}
