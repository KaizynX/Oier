#include <bits/stdc++.h>

#define DEBUG

using namespace std;

const int N = 1e6+7;

int n;
double res[N];
int a[N], stk[N], used[N], tp;

struct Point
{
    long long x, y;
    friend Point operator - (const Point &p1, const Point &p2) {
        Point res;
        res.x = p1.x-p2.x;
        res.y = p1.y-p2.y;
        return res;
    }
    friend Point operator - (const Point &p) {
        Point res;
        res.x = -p.x;
        res.y = -p.y;
        return res;
    }
    friend bool operator == (const Point &p1, const Point &p2) {
        return p1.x == p2.x && p1.y == p2.y;
    }
    friend bool operator != (const Point &p1, const Point &p2) {
        return p1.x != p2.x || p1.y != p2.y;
    }
    friend istream& operator >> (istream &is, Point &p) {
        return is >> p.x >> p.y;
    }
    friend long long operator * (const Point &p1, const Point &p2) {
        return p1.x*p2.y-p1.y*p2.x;
    } 
} p[N];

inline void Andrew()
{
    tp = 0;
    stk[++tp] = 0;
    for (int i = 1; i <= n; ++i) {
        while (tp >= 2 && (p[stk[tp-1]]-p[stk[tp]])*(p[stk[tp]]-p[i]) <= 0)
            used[stk[tp--]] = 0;
        used[i] = 1;
        stk[++tp] = i;
    }
#ifdef DEBUG
    for (int i = 1; i <= tp; ++i) {
        cout << stk[i] << " \n"[i==tp];
    }
#endif
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a+i);
        p[i] = {i, p[i-1].y+a[i]};
    }
    Andrew();
    for (int i = 1; i <= tp; ++i) {
        long long sum = 0;
        for (int j = stk[i-1]+1; j <= stk[i]; ++j)
            sum += a[j];
        double ave = static_cast<double>(sum)/(stk[i]-stk[i-1]);
        for (int j = stk[i-1]+1; j <= stk[i]; ++j)
            res[j] = ave;
    }
    for (int i = 1; i <= n; ++i)
        printf("%.12lf\n", res[i]);
    return 0;
}
