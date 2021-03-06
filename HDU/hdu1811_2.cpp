/*
 * @Author: Kaizyn
 * @Date: 2020-05-08 19:36:50
 * @LastEditTime: 2020-05-08 21:05:50
 */
#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

const double eps = 1e-7;
const double PI = acos(-1);
typedef pair<int, int> pii;
const int MOD = 998244353;
const int INF = 0x3f3f3f3f;
const int N = 1e4+7;

struct DSU
{
    int fa[N];
    void init(int sz) { for (int i = 0; i <= sz; ++i) fa[i] = i; }
    int get(int s) { return s == fa[s] ? s : fa[s] = get(fa[s]); }
    int& operator [] (int i) { return fa[get(i)]; }
    bool merge(int x, int y) {
        int fx = get(x), fy = get(y);
        if (fx == fy) return false;
        fa[fx] = fy; return true;
    }
};

int n, m;
int deg[N];
DSU pt;
queue<int> q;
vector<pii> edge;
vector<int> e[N];

inline void solve() {
    pt.init(n);
    queue<int>().swap(q);
    vector<pii>().swap(edge);
    for (int i = 1; i <= n; ++i) {
        vector<int>().swap(e[i]);
        deg[i] = 0;
    }
    char ch;
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> ch >> v;
        ++u; ++v;
        if (ch == '=') pt.merge(u, v);
        else if (ch == '>') edge.emplace_back(u, v);
        else if (ch == '<') edge.emplace_back(v, u);
    }
    int res = 0; // 1 un 2 con
    for (const pii &p : edge) {
        int u = pt[p.first], v = pt[p.second];
        if (u == v) res |= 2;
        // if (u == v) return void(cout << "CONFLICT" << endl);
        e[u].emplace_back(v);
        ++deg[v];
    }
    int pt_num = 0, pt_cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (pt[i] == i) {
            ++pt_num;
            if (deg[i] == 0) q.push(i);
        }
    }
    while (q.size()) {
        if (q.size() > 1) res |= 1;
        // if (q.size() > 1) return void(cout << "UNCERTAIN" << endl);
        int u = q.front();
        q.pop();
        ++pt_cnt;
        for (const int &v : e[u]) {
            if (--deg[v] == 0) q.push(v);
        }
    }
    if (pt_num > pt_cnt) res |= 2;
    // if (pt_num > pt_cnt) return void(cout << "CONFLICT" << endl);
    if (res == 0) cout << "OK" << endl;
    else if (res == 1) cout << "UNCERTAIN" << endl;
    else cout << "CONFLICT" << endl;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    while (cin >> n >> m) solve();
    return 0;
}