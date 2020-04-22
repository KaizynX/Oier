/*
 * @Author: Kaizyn
 * @Date: 2020-04-13 17:42:06
 * @LastEditTime: 2020-04-13 17:55:12
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
int res[N][N];
ISAP<int> isap;

signed main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    // turn pt i to i*2-1, i*2
    int s = 2*n+1, t = 2*n+2,
        suma = 0, sumb = 0;
    isap.init(t);
    for (int i = 1, a; i <= n; ++i) {
        cin >> a;
        suma += a;
        isap.add_edge(s, i*2-1, a);
        isap.add_edge(i*2-1, i*2, INF);
    }
    for (int i = 1, b; i <= n; ++i) {
        cin >> b;
        sumb += b;
        isap.add_edge(i*2, t, b);
    }
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        isap.add_edge(u*2-1, v*2, INF);
        isap.add_edge(v*2-1, u*2, INF);
    }
    if (suma != sumb || isap.work(s, t) != sumb) return cout << "NO\n", 0;
    for (int u = 1; u <= n; ++u) {
        for (int i = isap.fir[u*2], v; i != -1; i = isap.e[i].nex) {
            v = (isap.e[i].v+1)/2;
            res[v][u] = isap.e[i].w;
        }
    }
    cout << "YES\n";
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << res[i][j] << " \n"[j==n];
        }
    }
    return 0;
}