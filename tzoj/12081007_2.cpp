#include <bits/stdc++.h>

using namespace std;

const int Maxn = 1e2+7;
const int Maxt = 50;

int n;
int E1, E2, E3, t, h;
long long val[Maxt];

int main()
{
    while(cin >> n && n)
    {
        memset(val, 0, sizeof val);
        cin >> E1 >> E2 >> E3;
        for(int i = 0; i < n; ++i)
        {
            cin >> t >> h;
            // 时间 = 深度*2+开采*2
            // 电力 = (传送)k*E2*2次 + (移动)k*深度*2 + (开采)k
            for(int d = 1; d <= h; ++d)
                for(int k = 1; k*25 <= t; ++k)
                    val[d*2+k*2] += max(0, k*25-k*E2*2-k*d*2-k);
        }
        long long ans = 0, cur = -E1;
        // 维持
        for(int i = 1; i <= 40; ++i)
        {
            cur += val[i]-E3;
            ans = max(cur, ans);
        }
        cout << ans << endl;
    }
    return 0;
}
