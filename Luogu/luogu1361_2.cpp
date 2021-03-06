/*
 * @Author: Kaizyn
 * @Date: 2020-04-13 16:18:03
 * @LastEditTime: 2020-04-13 16:32:59
 */
#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

const int N = 3e3+7;
const int MOD = 998244353;
const int INF = 2e9+7;
const double eps = 1e-7;
const double PI = acos(-1);
typedef pair<int, int> pii;

template <typename T>
struct ISAP
{
    struct EDGE
    {
        int v, nex;
        T w;
        EDGE(const int &_v, const int &_nex, const T &_w) : v(_v), nex(_nex), w(_w) {}
    };
    vector<EDGE> e;
    int n, s, t;
    T maxflow;
    int fir[N], gap[N], dep[N];
    T work(const int &_s, const int &_t) {
        s = _s; t = _t;
        maxflow = 0;
        bfs();
        while (dep[s] < n) dfs(s, INF);
        return maxflow;
    }
    void init(const int &_n) {
        n = _n;
        e.clear();
        e.reserve(N<<2);
        memset(fir, -1, sizeof(int)*(n+3));
    }
    void add_edge(const int &u, const int &v, const T &w) {
        e.emplace_back(v, fir[u], w); fir[u] = e.size()-1;
        e.emplace_back(u, fir[v], 0); fir[v] = e.size()-1;
    }
    void bfs() {
        queue<int> q;
        memset(dep, -1, sizeof(int)*(n+3));
        memset(gap, 0, sizeof(int)*(n+3));
        dep[t] = 0;
        gap[0] = 1;
        q.push(t);
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (int i = fir[u], v; i != -1; i = e[i].nex) {
                v = e[i].v;
                if (dep[v] != -1) continue;
                q.push(v);
                dep[v] = dep[u]+1;
                ++gap[dep[v]];
            }
        }
    }
    T dfs(const int &u, const T &flow) {
        if (u == t) {
            maxflow += flow;
            return flow;
        }
        T used = 0;
        for (int i = fir[u], v; i != -1; i = e[i].nex) {
            v = e[i].v;
            if (!e[i].w || dep[v]+1 != dep[u]) continue;
            T minf = dfs(v, min(e[i].w, flow-used));
            if (minf) {
                e[i].w -= minf;
                e[i^1].w += minf;
                used += minf;
            }
            if (used == flow) return used;
        }
        if (--gap[dep[u]] == 0) dep[s] = n+1;
        ++gap[++dep[u]];
        return used;
    }
};

int n, m;
int a[N], b[N];
ISAP<int> isap;

signed main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    cin >> m;
    // plant [1, n] combination n+i*2-1, n+i*2
    isap.init(n+m*2+2);
    int s = n+m*2+1, t = n+m*2+2, sum = 0;
    for (int i = 1, k, c1, c2; i <= m; ++i) {
        cin >> k >> c1 >> c2;
        isap.add_edge(s, n+i*2-1, c1);
        isap.add_edge(n+i*2, t, c2);
        sum += c1+c2;
        for (int j = 1, x; j <= k; ++j) {
            cin >> x;
            isap.add_edge(n+i*2-1, x, INF);
            isap.add_edge(x, n+i*2, INF);
        }
    }
    for (int i = 1; i <= n; ++i) {
        sum += a[i]+b[i];
        isap.add_edge(s, i, a[i]);
        isap.add_edge(i, t, b[i]);
    }
    cout << sum-isap.work(s, t) << endl;
    return 0;
}