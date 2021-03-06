#include <bits/stdc++.h>

using namespace std;

const int N = 3e2+7;
const int INT_INF = 0x3f3f3f3f;
const long long LL_INF = 1e18;

int n, m, l, q;
int e[N][N], res[N][N];
long long dis[N][N];

int main()
{
    cin >> n >> m >> l;
    for (int i = 1, a, b, c; i <= m; ++i) {
        cin >> a >> b >> c;
        e[a][b] = e[b][a] = c;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) dis[i][j] = 0;
            else dis[i][j] = (e[i][j] ? e[i][j] : LL_INF);
        }
    }
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                dis[i][j] = min(dis[i][j], dis[i][k]+dis[k][j]);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) res[i][j] = 0;
            else res[i][j] = (dis[i][j] <= l ? 0 : INT_INF);
        }
    }
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                res[i][j] = min(res[i][j], res[i][k]+res[k][j]+1);
            }
        }
    }

    int s, t;
    cin >> q;
    while (q--) {
        cin >> s >> t;
        cout << (res[s][t] >= INT_INF ? -1 : res[s][t]) << endl;
    }
    return 0;
}
