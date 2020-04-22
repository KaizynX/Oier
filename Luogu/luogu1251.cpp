/*
 * @Author: Kaizyn
 * @Date: 2020-04-16 14:55:47
 * @LastEditTime: 2020-04-16 16:04:44
 */
#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

const int N = 4e3+7;
const int MOD = 998244353;
const long long INF = 3e10;

template <typename T>
struct ZKW_SPFA
{
    struct Edge
    {
        int v, nex;
        T w, c; // edge wight and cost
        Edge(const int &_v, const int &_nex, const T &_w, const T &_c) \
        : v(_v), nex(_nex), w(_w), c(_c) {}
    };
    vector<Edge> e;
    int n, s, t;
    int fir[N], vis[N];
    T maxflow, mincost;
    T dis[N];
    ZKW_SPFA() { e.reserve(N<<4); }
    void init(const int &_n) {
        n = _n;
        maxflow = mincost = 0;
        e.clear();
        memset(fir, -1, sizeof(int)*(n+3));
    }
    void add_edge(const int &u, const int &v, const T &w = 1, const T &c = 0) {
        e.emplace_back(v, fir[u], w, c); fir[u] = e.size()-1;
        e.emplace_back(u, fir[v], 0, -c); fir[v] = e.size()-1;
    }
    pair<T, T> work(const int &_s, const int &_t) {
        s = _s; t = _t;
        while (spfa()) {
            vis[t] = 1;
            while (vis[t]) {
                memset(vis, 0, sizeof(int)*(n+3));
                maxflow += dfs(s, INF);
            }
        }
        return {maxflow, mincost};
    }
  private:
    bool spfa() {
        memset(dis, 0x3f, sizeof(T)*(n+3));
        memset(vis, 0, sizeof(int)*(n+3));
        deque<int> q;
        q.push_back(t);
        dis[t] = 0;
        vis[t] = 1;
        while (q.size()) {
            int u = q.front(); q.pop_front();
            for (int i = fir[u], v; ~i; i = e[i].nex) {
                v = e[i].v;
                if (!e[i^1].w || dis[v] <= dis[u]+e[i^1].c) continue;
                dis[v] = dis[u]+e[i^1].c;
                if (vis[v]) continue;
                vis[v] = 1;
                if (q.size() && dis[v] < dis[q.front()]) q.push_front(v);
                else q.push_back(v);
            }
            vis[u] = 0;
        }
        return dis[s] < INF;
    }
    T dfs(const int &u, const T &flow) {
        vis[u] = 1;
        if (u == t || flow <= 0) return flow;
        T res, used = 0;
        for (int i = fir[u], v; ~i; i = e[i].nex) {
            v = e[i].v;
            if (vis[v] || !e[i].w || dis[u] != dis[v]+e[i].c) continue;
            res = dfs(v, min(e[i].w, flow-used));
            if (!res) continue;
            mincost += res*e[i].c;
            e[i].w -= res;
            e[i^1].w += res;
            used += res;
            if (used == flow) break;
        }
        return used;
    }
};

int n, p, df, f, ds, s;
int r[N];
ZKW_SPFA<long long> zkw;

signed main()
{
    // day i ==> (i*2-1) to wash | evening, (i*2) can use | morning
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> r[i];
    cin >> p >> df >> f >> ds >> s;
    int s = n*2+1, t = n*2+2;
    zkw.init(t);
    for (int i = 1; i <= n; ++i) {
        zkw.add_edge(s, i*2-1, r[i], 0);
        zkw.add_edge(i*2, t, r[i], 0);
        zkw.add_edge(s, i*2, INF, p); // buy new
        if (i < n) zkw.add_edge(i*2-1, i*2+1, INF, 0); // do not wath
        if (i+df <= n) zkw.add_edge(i*2-1, (i+df)*2, INF, f); // fast
        if (i+ds <= n) zkw.add_edge(i*2-1, (i+ds)*2, INF, s); // slow
    }
    cout << zkw.work(s, t).second << endl;
    return 0;
}