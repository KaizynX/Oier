/*
 * @Author: Kaizyn
 * @Date: 2021-07-07 22:58:37
 * @LastEditTime: 2021-07-07 23:14:41
 */
#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

const double eps = 1e-7;
const double PI = acos(-1);
typedef pair<int, int> pii;
typedef long long ll;
const int MOD = 998244353; // 1e9+7;
const int INF = 0x3f3f3f3f;
// const ll INF = 1e18;
const int N = 2e5+7;

int n, k;

int f(int x) {
  if (x == 0) return 0;
  int p = 1, r = 0;
  while (x/p%k == 0) {
    r += (k-1)*p;
    p *= k;
  }
  return (x/p%k+(x-1)/p%k)%k*p+r;
}

inline void solve() {
  cin >> n >> k;
  for (int i = 0, y; i < n; ++i) {
    cout << f(i) << endl;
    cin >> y;
    if (y) return;
  }
}

signed main() {
#ifdef ONLINE_JUDGE
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#endif
  int T = 1;
  cin >> T; // scanf("%d", &T);
  for (int t = 1; t <= T; ++t) {
    solve();
  }
  return 0;
}