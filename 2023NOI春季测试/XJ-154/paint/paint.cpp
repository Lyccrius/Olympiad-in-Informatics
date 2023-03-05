#include <iostream>
#include <cstring>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e5;
const int maxM = 1e5;
const int maxQ = 1e5;

int T;
int n, m, q;
int op, x, c;
int rc[maxN + 10];
int rt[maxN + 10];
int cc[maxN + 10];
int ct[maxN + 10];

void init() {
    std::memset(rt, 0, sizeof(rt));
    std::memset(ct, 0, sizeof(ct));
    return;
}

void mian() {
    std::cin >> n >> m >> q; init();
    for (int i = 1; i <= q; i++) {
        std::cin >> op >> x >> c;
        if (op == 0) {
            rc[x] = c;
            rt[x] = i;
        } else if (op == 1) {
            cc[x] = c;
            ct[x] = i;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (rt[i] || ct[j]) {
                if (rt[i] > ct[j]) {
                    std::cout << rc[i] << ' ';
                } else {
                    std::cout << cc[j] << ' ';
                }
            } else {
                std::cout << 0 << ' ';
            }
        }
        std::cout << '\n';
    }
    return;
}

int main() {
    freopen("paint.in", "r", stdin);
    freopen("paint.out", "w", stdout);
    promote();
    std::cin >> T;
    while (T--) mian();
    return 0;
}