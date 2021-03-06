/*
 * @Author: Kaizyn
 * @Date: 2021-02-09 21:33:15
 * @LastEditTime: 2021-02-09 22:30:09
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
const int N = 2e3+7;

template <typename T, typename H>
inline T qpow(const T &a, const H &p, const int &mo = MOD) {
  long long res = 1, x = a;
  for (H i = p; i; i >>= 1, x = x*x%mo)
    if (i&1) res = res*x%mo;
  return static_cast<T>(res);
}

struct Combination {
  int fac[N], inv[N];
  void init(const int &n) {
    fac[0] = inv[0] = fac[1] = inv[1] = 1;
    for (int i = 2; i <= n; ++i) {
      fac[i] = 1ll*fac[i-1]*i%MOD;
      inv[i] = 1ll*(MOD-MOD/i)*inv[MOD%i]%MOD;
    }
    for (int i = 2; i <= n; ++i) {
      inv[i] = 1ll*inv[i]*inv[i-1]%MOD;
    }
  }
  int A(const int &p, const int &q) {
    return p >= q ? 1ll*fac[p]*inv[p-q]%MOD : 0;
  }
  int C(const int &p, const int &q) {
    return p >= q ? 1ll*fac[p]*inv[q]%MOD*inv[p-q]%MOD : 0;
  }
};

// array [0, n)
namespace NTT {
  static const int SIZE = (1<<18)+3;
  const int G = 3;
  int len, bit, inv;
  int rev[SIZE];
  template <class T>
  void ntt(T a[], int flag = 1) {
    for (int i = 0; i < len; ++i)
      if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int base = 1; base < len; base <<= 1) {
      long long wn = qpow(G, (MOD-1)/(base*2)), w;
      if (flag == -1) wn = qpow(wn, MOD-2);
      for (int i = 0; i < len; i += base*2) {
        w = 1;
        for (int j = 0; j < base; ++j) {
          long long x = a[i+j], y = w*a[i+j+base]%MOD;
          a[i+j] = (x+y)%MOD;
          a[i+j+base] = (x-y+MOD)%MOD;
          w = w*wn%MOD;
        }
      }
    }
  }
  void init(int n) {
    len = 1; bit = 0;
    while (len < n+n) len <<= 1, ++bit;
    for (int i = 0; i < len; ++i)
      rev[i] = (rev[i>>1]>>1)|((i&1)<<(bit-1));
    inv = qpow(len, MOD-2);
  }
  template <class T>
  void work(T f[], const int &n, T g[], const int &m) {
    for (int i = n; i < len; ++i) f[i] = 0;
    ntt(f, 1);
    for (int i = 0; i < len; ++i) f[i] = 1ll*f[i]*g[i]%MOD;
    ntt(f, -1);
    for (int i = 0; i < n; ++i) f[i] = 1ll*f[i]*inv%MOD;
  }
}

int n;
int f[N], g[N][N];
Combination comb;

signed main() {
#ifdef ONLINE_JUDGE
  ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#endif
  cin >> n;
  NTT::init(n+1);
  comb.init(n);
  int res = 0;
  for (int i = 1; i <= n; ++i) {
    for (int k = 0; k <= n; ++k) g[i][k] = comb.inv[k];
    g[i][i] = 0;
    NTT::ntt(g[i]);
  }
  for (int i = 1; i <= n; ++i) {
    memset(f, 0, sizeof(int)*(n+1));
    f[i] = comb.inv[i];
    for (int j = 1; j <= n; ++j) if (i != j) {
      NTT::work(f, n+1, g[j], n+1);
    }
    (res += f[n]) %= MOD;
  }
  cout << 1ll*res*comb.fac[n]%MOD << '\n';
  return 0;
}