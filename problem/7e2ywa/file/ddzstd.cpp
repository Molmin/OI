#include <bits/stdc++.h>
using namespace std;
#define ll long long
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
const int N = 3e5 + 10;
struct circle {
    int x, r;
}c[N];
bool cmp(circle A, circle B) {
    if(A.x + A.r != B.x + B.r) return A.x + A.r < B.x + B.r;
    else return A.x - A.r > B.x - B.r;
}
int n, st[N], top, ans;
int main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    rd(n);
    for(int i = 1; i <= n; ++i) rd(c[i].x, c[i].r);
    sort(c + 1, c + n + 1, cmp);
    for(int i = 1; i <= n; ++i) {
        int now = c[i].x - c[i].r, sum = 0;
        while(c[st[top]].x - c[st[top]].r >= now && top >= 1) {
            sum += 2 * c[st[top]].r;
            top --;
        }
        st[++top] = i;
        if(sum == 2 * c[i].r) ans ++;
    }
    cout << ans + n + 1 << endl;
    return 0;
}