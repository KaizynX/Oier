/*
 * @Author: Kaizyn
 * @Date: 2020-08-05 20:57:30
 * @LastEditTime: 2020-08-07 20:41:33
 */
#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

const double eps = 1e-7;
const double PI = acos(-1);
typedef pair<int, int> pii;
const int MOD = 998244353;
const int INF = 0x3f3f3f3f;
const int N = 2e4+7;
const int NN = (int)log2(N)+3;

// template <typename T>
struct Dinic {
  typedef int T;
  struct EDGE {
    int v, nex;
    T w;
    EDGE(const int &_v, const int &_nex, const T &_w) : v(_v), nex(_nex), w(_w) {}
  };
  vector<EDGE> e;
  int n, s, t;
  T maxflow;
  int fir[N*3], dep[N*3], cur[N*3];
  T work(const int &_s, const int &_t) {
    s = _s; t = _t;
    T flow;
    while (bfs())
      while ((flow = dfs(s, INF)))
        maxflow += flow;
    return maxflow;
  }
  void init(const int &_n) {
    n = _n;
    e.clear();
    maxflow = 0;
    memset(fir, -1, sizeof(int)*(n+3));
  }
  void add_edge(const int &u, const int &v, const T &w) {
    e.emplace_back(v, fir[u], w); fir[u] = e.size()-1;
    e.emplace_back(u, fir[v], 0); fir[v] = e.size()-1;
  }
  bool bfs() {
    queue<int> q;
    memset(dep, 0, sizeof(int)*(n+3));
    q.push(s);
    dep[s] = 1;
    for (int i = 0; i <= n; ++i) cur[i] = fir[i];
    while (q.size()) {
      int u = q.front();
      q.pop();
      for (int i = fir[u], v; i != -1; i = e[i].nex) {
        v = e[i].v;
        if (dep[v] || !e[i].w) continue;
        dep[v] = dep[u]+1;
        if (v == t) return true;
        q.push(v);
      }
    }
    return false;
  }
  T dfs(const int &u, const T &flow) {
    if (!flow || u == t) return flow;
    T rest = flow, now;
    for (int &i = cur[u], v; i != -1; i = e[i].nex) {
      v = e[i].v;
      if (dep[v] != dep[u]+1 || !e[i].w) continue;
      now = dfs(v, min(rest, e[i].w));
      if (!now) {
        dep[v] = 0;
      } else {
        e[i].w -= now;
        e[i^1].w += now;
        rest -= now;
        if (rest == flow) break;
      }
    }
    return flow-rest;
  }
};
Dinic dinic, dinic2;

struct SegmentTreeGarph {
  struct TreeNode {
    int l, r, ls, rs;
    int len() const { return r-l+1; }
  } tr[N<<1];
  int tot, root;
  void build(const int &n) {
    tot = n;
    for (int i = 1; i <= n; ++i) tr[i].l = tr[i].r = i;
    build(1, n, root);
  }
  void build(const int &l, const int &r, int &i) {
    if (l == r) return i = l, void();
    i = ++tot;
    tr[i].l = l; tr[i].r = r;
    int mid = (l+r)>>1;
    build(l, mid, tr[i].ls);
    build(mid+1, r, tr[i].rs);
    dinic.add_edge(tr[i].ls, i, INF);
    dinic.add_edge(tr[i].rs, i, INF);
  }
  void insert(const int &o, int l, int r) {
    if (l > r) swap(l, r);
    insert(o, l, r, root);
  }
  void insert(const int &o, const int &l, const int &r, const int &i) {
    if (tr[i].l >= l && tr[i].r <= r) return dinic.add_edge(i, o, INF);
    int mid = (tr[i].l+tr[i].r)>>1;
    if (l <= mid) insert(o, l, r, tr[i].ls);
    if (r >  mid) insert(o, l, r, tr[i].rs);
  }
} stg;

struct HLD {
  int dfn;
  int fa[N], d[N], num[N], son[N], id[N], tp[N];
  vector<int> *e;
  template <typename E>
  void build(E *_e, const int &rt = 1) {
    e = _e;
    fa[rt] = dfn = 0;
    dfs1(rt);
    dfs2(rt);
  }
  void dfs1(const int &u = 1) {
    d[u] = d[fa[u]]+1;
    num[u] = 1;
    son[u] = 0;
    for (const int &v : e[u]) if (v != fa[u]) {
      fa[v] = u;
      dfs1(v);
      num[u] += num[v];
      if (num[v] > num[son[u]]) son[u] = v;
    }
  }
  void dfs2(const int &u = 1) {
    tp[u] = son[fa[u]] == u ? tp[fa[u]] : u;
    id[u] = ++dfn;
    if (son[u]) dfs2(son[u]);
    for (const int &v : e[u]) if (v != son[u] && v != fa[u])
      dfs2(v);
  }
  int lca(int x, int y) {
    while (tp[x] != tp[y]) {
      if (d[tp[x]] < d[tp[y]]) swap(x, y);
      x = fa[tp[x]];
    }
    return d[x] < d[y] ? x : y;
  }
  void add_edge(int o, int x, int y) {
    if (d[x] < d[y]) swap(x, y); // x is son of y
    while (tp[x] != tp[y]) {
      dinic.add_edge(id[x], o, INF);
      x = fa[tp[x]];
    }
    if (x != y) stg.insert(o, id[y]+1, id[x]);
  }
} hld;

int n, C, last_mid, last_mid2;
int c[N], vfa[N];
vector<int> e[N], ve[N], col[N];

// VirtualTree begin
void virtual_tree_clear(const int &u = 1) {
  for (const int &v : ve[u]) virtual_tree_clear(v);
  vfa[u] = 0;
  ve[u].clear();
}

// build a VirtualTree return the root
int virtual_tree_build(vector<int> &vset) {
  // id ==> dfn rank, d ==> depth
  static int stk[N], top;
  static int *id = hld.id, *d = hld.d;
  sort(vset.begin(), vset.end(), [&](const int &x, const int &y) {
    return id[x] < id[y];
  });
  top = 0;
  int x, z;
  for (const int &v : vset) {
    if (top && (z = hld.lca(v, stk[top])) != stk[top]) {
      x = stk[top--];
      while (top && d[stk[top]] > d[z]) {
        ve[stk[top]].emplace_back(x);
        vfa[x] = stk[top];
        x = stk[top--];
      }
      ve[z].emplace_back(x);
      vfa[x] = z;
      if (!top || stk[top] != z) stk[++top] = z;
    }
    stk[++top] = v;
  }
  x = stk[top--];
  while (top) {
    ve[stk[top]].emplace_back(x);
    vfa[x] = stk[top];
    x = stk[top--];
  }
  return x;
}
// VirtualTree end

// (k*d) ==> 2*n+(k*d)
int build_stg(const int &u = 1) {
  int sum = c[u] == C;
  for (const int &v : ve[u])
    sum += build_stg(v);
  if (sum*C < n)
    hld.add_edge(2*n+sum*C, u, vfa[u]);
  return sum;
}

void build_network() {
  dinic.init(n*3+2);
  stg.build(n);
  assert(stg.tot < n*2);
  for (C = 1; C <= n; ++C) if (col[C].size()) {
    int rt = virtual_tree_build(col[C]);
    build_stg(rt);
    virtual_tree_clear(rt);
  }
  int st = n*3+1, ed = n*3+2;
  dinic.add_edge(2*n, ed, 1); // k*d == 0
  for (int i = 1; i <= n; ++i) {
    dinic.add_edge(st, i, 1);
    dinic.add_edge(i, 2*n, 1);
    // dinic.add_edge(2*n+i, ed, 0); // key
    if (hld.fa[i] && hld.tp[i] != i)
      dinic.add_edge(hld.fa[i], i, INF);
  }
}

bool check(const int &mid) {
  int st = n*3+1, ed = n*3+2;
  while (last_mid < mid) dinic.add_edge(2*n+(++last_mid), ed, 1);
  return dinic.work(st, ed) >= mid+1;
}

void save_graph() {
  dinic2 = dinic;
  last_mid2 = last_mid;
}

void get_graph() {
  dinic = dinic2;
  last_mid = last_mid2;
}

signed main() {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(NULL);

  cin >> n;
  for (int i = 2, p; i <= n; ++i) {
    cin >> p;
    e[p].emplace_back(i);
  }
  for (int i = 1; i <= n; ++i) {
    cin >> c[i];
    col[c[i]].emplace_back(i);
  }

  hld.build(e);
  int l = 0, r = n-1, mid;
  last_mid = 0;
  build_network();
  save_graph();
  while (l < r) {
    mid = (l+r+1)>>1;
    if (check(mid)) {
      l = mid;
      save_graph();
    } else {
      r = mid-1;
      get_graph();
    }
  }
  cout << l+1 << endl;
  return 0;
}