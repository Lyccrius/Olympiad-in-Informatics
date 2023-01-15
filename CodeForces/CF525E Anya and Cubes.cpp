#include <iostream>
#include <map>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;
typedef std::pair<lxl, lxl> pll;

const int maxN = 26;

lxl n, k, S;
lxl a[maxN + 10];
lxl b[maxN + 10];
lxl m;
lxl st[2];
lxl ed[2];
lxl ans;
std::map<pll, lxl> res[2];

lxl factorial(lxl x) {
    lxl ret = 1;
    while (x) {
        ret *= x;
        x--;
        if (ret > S) {
            ret = -1;
            break;
        }
    }
    return ret;
}

lxl query(lxl x, lxl s) {
    if (res[1].count(std::make_pair(x, s))) return res[1][std::make_pair(x, s)];
    return res[1][std::make_pair(x, s)] = res[0][std::make_pair(x, s)] + (x ? query(x - 1, s) : 0);
}

void check(int type) {
    lxl cnt = 0;
    lxl sum = 0;
    for (int i = st[type]; i <= ed[type]; i++) {
        if (b[i] == 1) sum += a[i];
        else if (b[i] == 2) {
            cnt++;
            lxl s = factorial(a[i]);
            if (s == -1 || (cnt > k) || ((sum + s) > S)) return;
            sum += s;
        }
    }
    if (type == 0) {
        ++res[0][std::make_pair(cnt, sum)];
        ++res[0][std::make_pair(-1, sum)];
    } else if (res[0].count(std::make_pair(-1, S - sum))) ans += query(k - cnt, S - sum);
}

void DFS(int now, int type) {
    if (now > ed[type]) check(type);
    else for (int i = 0; i <= 2; i++) {
        b[now] = i;
        DFS(now + 1, type);
    }
    return;
}

int main() {
    promote();
    std::cin >> n >> k >> S;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    m = n >> 1;
    st[0] = 1;
    ed[0] = m;
    st[1] = m + 1;
    ed[1] = n;
    DFS(1, 0);
    DFS(m + 1, 1);
    std::cout << ans << "\n";
    return 0;
}