#include <iostream>
#include <map>
#include <cstring>

typedef char chr;
typedef std::map<int, int> mii;

const int maxN = 2000;

const int mod = 1e9 + 7;

int C;
chr S[maxN + 10];
chr T[maxN + 10];
int s;
int t;
int n;
int tot;
int ans;
mii vis;
mii del;

void DFS(int now) {
    if (now > t) return;
    //printf("DFS(%d)\n", now);
    //printf("DFS(%d)\n", now);
    if (now == t) {
        ans++;
        return;
    }
    if (vis[now]) {
        ans += del[now];
        return;
    }
    int ori = ans;
    for (int nxt = (tot ^ now); nxt; nxt = (nxt - 1) & tot) {
        if (nxt <= now) {
            break;
        }
        if (nxt & now) continue;
        DFS(nxt);
    }
    vis[now] = true;
    del[now] = ans - ori;
    //printf("del[%d] = %d\n", now, del[now]);
    return;
}

int lowbit(int x) {
    return x & - x;
}

int highbit(int x) {
    int ret = 0;
    while (x) {
        ret = lowbit(x);
        x -= lowbit(x);
    }
    return ret;
}

void mian() {
    ans = 0;
    vis.clear();
    //res.clear();
    std::cin >> (S);
    std::cin >> (T);
    n = std::strlen(S);
    for (int i = s; i <= t; i++) del[i] = 0;
    s = S[0] - '0'; for (int i = 1; i < n; i++) s = s * 2 + S[i] - '0';
    t = T[0] - '0'; for (int i = 1; i < n; i++) t = t * 2 + T[i] - '0';
    tot = (highbit(t) << 1) - 1;
    //std::cout << tot << '\n';
    for (int i = s; i <= t; i++) del[i] = 0;
    DFS(s);
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> C;
    while (C--) mian();
    return 0;
}