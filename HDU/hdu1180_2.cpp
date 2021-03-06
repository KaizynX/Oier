#include <bits/stdc++.h>

using namespace std;

const int N = 25;
const int INF = 1e9;
const int d[] = {0, -1, 0, 1, 0};

int n, m;
char a[N][N];
int dis[N][N];

struct Node
{
    int x, y, t;
    Node(){}
    Node(int _x, int _y, int _t) : x(_x), y(_y), t(_t) {}
} q[100000];

int main()
{
    while (scanf("%d %d", &n, &m) == 2) {
        int sx, sy, tx, ty;
        for (int i = 1; i <= n; ++i) {
            scanf("%s", a[i]+1);
            for (int j = 1; j <= m; ++j) {
                dis[i][j] = INF;
                if (a[i][j] == 'S') sx = i, sy = j;
                if (a[i][j] == 'T') tx = i, ty = j;
                if (a[i][j] == '|') a[i][j] = 1;
                if (a[i][j] == '-') a[i][j] = 0;
            }
        }
        int head = 0, tail = 0;
        q[++tail] = Node(sx, sy, 0);
        dis[sx][sy] = 1;
        while (head < tail) {
            Node u = q[++head];
            if (dis[u.x][u.y] < u.t) continue;
            if (u.x == tx && u.y == ty) {
                printf("%d\n", u.t);
                break;
            }
            for (int i = 0, nx, ny; i < 4; ++i) {
                nx = u.x+d[i]; ny = u.y+d[i+1];
                if (nx < 1 || nx > n || ny < 1 || ny > m ||
                    a[nx][ny] == '*' || dis[nx][ny] < u.t+1) continue;
                if (a[nx][ny] < 2) {
                    int val = u.t+1+(i%2 == (a[nx][ny]^(u.t&1)));
                    nx += d[i]; ny += d[i+1];
                    if (nx < 1 || nx > n || ny < 1 || ny > m ||
                        a[nx][ny] == '*' || dis[nx][ny] < u.t+1) continue;
                    dis[nx][ny] = val;
                } else {
                    dis[nx][ny] = u.t+1;
                }
                q[++tail] = Node(nx, ny, dis[nx][ny]);
            }
        }
    }
    return 0;
}
