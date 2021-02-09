/*
 * @Author: Kaizyn
 * @Date: 2021-01-16 20:07:37
 * @LastEditTime: 2021-01-16 20:15:43
 */
#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

const double eps = 1e-7;
const double PI = acos(-1);
typedef pair<int, int> pii;
typedef long long ll;
const int MOD = 998244353;
const int INF = 0x3f3f3f3f;
// const ll INF = 1e18;
const int N = 3e5+7;

int n, k;
int a[N];

inline void solve() {
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  ll res = 0, v = 0;;
  sort(a+1, a+n+1);
  for (int i = 1, j; i <= n; ++v) {
     j = i;
     while (j <= n && a[j] == v) ++j;
     res += max(0, k-(j-i))*1ll*v;
     k = min(k, j-i);
     i = j;
  }
  res += 1ll*k*v;
  cout << res << endl;
}

signed main() {
#ifdef ONLINE_JUDGE
  ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#endif
  int T = 1;
  // cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve();
  }
  return 0;
}