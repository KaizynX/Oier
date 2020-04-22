/*
 * @Author: Kaizyn
 * @Date: 2020-04-19 13:08:43
 * @LastEditTime: 2020-04-19 13:41:00
 */
#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

const int N = 2e3+7;
const int MOD = 998244353;
const int INF = 0x3f3f3f3f;
const double eps = 1e-7;
const double PI = acos(-1);
typedef pair<int, int> pii;

int n;
string s;

inline void solve()
{
    cin >> n >> s;
    // if (s.size() >= n) return void(cout << s << endl);
    // int t = (n-s.size()+3)/4;
    while ((int)s.size() < n) s += "zsbd";
    cout << s << endl;
}

signed main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int testcase = 1;
    cin >> testcase;
    for (int i = 1; i <= testcase; ++i) {
        solve();
    }
    return 0;
}