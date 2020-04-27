/*
 * @Author: Kaizyn
 * @Date: 2020-04-26 22:34:22
 * @LastEditTime: 2020-04-27 09:45:22
 */
#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

const int N = 2e2+7;
const int MOD = 998244353;
const int INF = 0x3f3f3f3f;
const double eps = 1e-7;
const double PI = acos(-1);
typedef pair<int, int> pii;

int a, b, q, c;

inline long long calc(const long long &x) {
    long long res = 0;
    res += x/c*b;
    res += min(x%c+1, 1ll*b);
    return res;
}

inline void solve()
{
    cin >> a >> b;
    if (a > b) swap(a, b);
    c = a*b/__gcd(a, b);
    for (int i = b; i < c; ++i) {
        if (i%a == i%b%a) {
            cout << i << " ";
        }
    }
    cout << endl;
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