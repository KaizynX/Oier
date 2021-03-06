/*
 * @Author: Kaizyn
 * @Date: 2020-03-27 23:01:13
 * @LastEditTime: 2020-03-31 16:45:01
 */
#include <bits/stdc++.h>

#define DEBUG

using namespace std;

const int N = 2e5+7;
const int MOD = 1e9+7;
const double eps = 1e-7;
const double PI = acos(-1);
const int INF = 0x3f3f3f3f;
typedef pair<int, int> pii;

struct comp
{
    typedef double T; // maybe long double ?
    T real, imag;
    comp (const double &_real = 0, const double &_imag = 0) : real(_real), imag(_imag) {}
    friend comp operator + (const comp &c1, const comp &c2) { return comp(c1.real+c2.real, c1.imag+c2.imag); }
    friend comp operator - (const comp &c1, const comp &c2) { return comp(c1.real-c2.real, c1.imag-c2.imag); }
    friend comp operator * (const comp &c1, const comp &c2) { return comp(c1.real*c2.real-c1.imag*c2.imag, c1.real*c2.imag+c1.imag*c2.real); }
    comp& operator += (const comp &c) { return *this = *this+c; }
    comp& operator -= (const comp &c) { return *this = *this-c; }
    comp& operator *= (const comp &c) { return *this = *this*c; }
    friend istream& operator >> (istream &is, comp &c) { return is >> c.real >> c.imag; }
    friend ostream& operator << (ostream &os, comp &c) { return os << c.real << setiosflags(ios::showpos) << c.imag << "i";}
    comp conjugate() { return comp(real, -imag); }
    friend comp conjugate(const comp &c) { return comp(c.real, -c.imag); }
};

namespace FFT
{
    static const int SIZE = 262144+3;
    int len, bit;
    int rev[SIZE];
    // #define comp complex<long double>
    void fft(comp a[], int flag = 1) {
        for (int i = 0; i < len; ++i)
            if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int base = 1; base < len; base <<= 1) {
            comp w, wn = {cos(PI/base), flag*sin(PI/base)};
            for (int i = 0; i < len; i += base*2) {
                w = { 1.0, 0.0 };
                for (int j = 0; j < base; ++j) {
                    comp x = a[i+j], y = w*a[i+j+base];
                    a[i+j] = x+y;
                    a[i+j+base] = x-y;
                    w *= wn;
                }
            }
        }
    }
    template <typename TT>
    void work(TT a[], const int &n) {
        static comp f[SIZE];
        len = 1; bit = 0;
        while (len < n+n) len <<= 1, ++bit;
        for (int i = 0; i < len; ++i)
            rev[i] = (rev[i>>1]>>1)|((i&1)<<(bit-1));
        for (int i = 0; i < n; ++i) f[i] = a[i];
        for (int i = n; i < len; ++i) f[i] = 0;
        fft(f, 1);
        for (int i = 0; i < len; ++i) f[i] *= f[i];
        fft(f, -1);
        for (int i = 0; i < n+n; ++i) a[i] = static_cast<TT>(f[i].real/len+.5);
    }
};

int n, m;
int a[N];
long long num[N], sum[N];

inline void solve()
{
    memset(num, 0, sizeof num);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a+i);
        ++num[a[i]];
    }
    sort(a, a+n);
    m = a[n-1];
    FFT::work(num, m+1);
    m = m+m;
    for (int i = 0; i < n; ++i) --num[a[i]+a[i]];
    for (int i = 1; i <= m; ++i) num[i] /= 2, sum[i] = sum[i-1]+num[i];
    #ifdef DEBUG
    for (int i = 1; i <= m; ++i) printf("%lld%c", num[i], " \n"[i==m]);
    #endif
    long long res = 0, tot = n*(n-1ll)*(n-2ll)/6;
    for (int i = 0; i < n; ++i) {
        res += sum[m]-sum[a[i]];
        res -= (n-i-1ll)*i;
        res -= n-1;
        res -= (n-i-1ll)*(n-i-2ll)/2;
    }
    printf("%.7f\n", 1.0*res/tot);
}

signed main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int T;
    scanf("%d", &T);
    while (T--) solve();
    return 0;
}