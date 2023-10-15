void solve() {
    memset(bel, 0, sizeof(bel));
    memset(sz, 0, sizeof(sz));
    for(int i = 1; i <= tot; ++i) S[i].clear();
    for(int i = 1; i <= tot; ++i) seg[i].first = seg[i].second = xb[i] = 0;
    for(int i = 1; i <= tot; ++i) ed[i].clear();
    sort(p + 1, p + n + 1, cmp);
    for(int i = 1; i <= n; ++i) {
        chk[f(p[i].x, p[i].y)] = i;
    }
    tot = 1;
    bel[1] = 1;
    S[1].push_back(1);
    xb[1] = p[1].x;
    seg[1].first = seg[1].second = p[1].y;
    for(int i = 2; i <= n; ++i) {
        if(p[i].x == p[i - 1].x) {
            if(p[i].y > p[i - 1].y + 1) {
                bel[i] = ++tot;
                S[tot].push_back(i);
                seg[tot].first = seg[tot].second = p[i].y;
                xb[tot] = p[i].x;
            } else {
                seg[tot].second = p[i].y;
                bel[i] = tot;
                S[tot].push_back(i);
            }
        } else {
            ++tot;
            bel[i] = tot;
            S[tot].push_back(i);
            seg[tot].first = seg[tot].second = p[i].y;
            xb[tot] = p[i].x;
        }
    }
    for(int i = 1; i <= tot; ++i) {
        for(int tmp = seg[i].first; tmp <= seg[i].second; ++tmp) {
            if(bel[chk[f(xb[i] + 1, tmp)]] != 0) {
                ed[i].push_back(bel[chk[f(xb[i] + 1, tmp)]]);
                ed[bel[chk[f(xb[i] + 1, tmp)]]].push_back(i);
                tmp = seg[bel[chk[f(xb[i] + 1, tmp)]]].second;
            }
        }
    }
    dfs(1, 0);
}