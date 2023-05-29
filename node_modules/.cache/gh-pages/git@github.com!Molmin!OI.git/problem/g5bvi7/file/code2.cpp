#include <bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int, int>
#define mkp make_pair
#define INF INT_MAX
template <typename T> inline void rd(T &x){
	x = 0; bool f = true; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = false; ch = getchar();}
	while(ch >= '0' && ch <= '9'){ x = (x << 1) + (x << 3) + (ch ^ '0'); ch = getchar();}
	if(!f) x = -x;
}
template <typename T, typename ...Args> inline void rd(T &x, Args &...args){ rd(x); rd(args...);}
const int N = 2e7 + 100;
const int mod = 998244353;
int p, r, s, inv[N], fac[N];
int ans;
int qpow(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
void init() {
    fac[0] = 1;
    for(int i = 1; i <= 20000000; ++i) fac[i] = fac[i - 1] * i % mod;
    inv[20000000] = qpow(fac[20000000], mod - 2);
    for(int i = 19999999; i >= 0; --i) inv[i] = inv[i + 1] * (i + 1) % mod;
}
int C(int a, int b) {
    if(a < b) return 0;
    return fac[a] * inv[a - b] % mod * inv[b] % mod;
} 
signed main() {
    // freopen("probability.in", "r", stdin);
    // freopen("probability.out", "w", stdout);
    init();
	rd(p, s, r);
    for(int i = 1; i * r <= s && i <= p; ++i) {
        if(i & 1) {
            ans = (C(p, i) * C(s - i * r + p - 1, p - 1) % mod + ans) % mod;
        } else {
            ans = (ans - C(p, i) * C(s - i * r + p - 1, p - 1) % mod + mod) % mod;
        }
    }
    ans = ans * qpow(p, mod - 2) % mod;
    ans = ans * qpow(C(s - r + p - 1, p - 1), mod - 2) % mod;
    cout << ans << endl;
    return 0;
}