#include <iostream>

const int maxN = 1e5;

int t;
int n;
int a[maxN + 10];
int lim;

bool check() {
    for (int i = 1; i <= n; i++) {
        if (a[i] < 0) {
            return false;
        }
    }
    return true;
}

bool DFS(int now, int last) {
    if (now == lim) {
        if (check()) {
            //printf("*%d\n", last);
            return true;
        }
        return false;
    }
    for (int i = 1; i <= n; i++) {
        if (a[i] == 0) continue;
        if (i == last) continue;
        int pre = i - 1;
        int suf = i + 1;
        if (i == 1) pre = n;
        if (i == n) suf = 1;
        a[pre] += a[i];
        a[suf] += a[i];
        a[i] = - a[i];
        if (DFS(now + 1, i)) {
            //printf("*%d\n", i);
            return true;
        }
        a[i] = - a[i];
        a[pre] -= a[i];
        a[suf] -= a[i];
    }
    return false;
}

void mian() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (lim = 0; lim <= 2 * n; lim++) {
        if (DFS(0, 0)) {
            std::cout << lim << '\n';
            //for (int j = 1; j <= n; j++) printf("%d ", a[j]);
            //printf("\n");
            return;
        }
    }
    std::cout << -1 << '\n';
    return;
}

int main() {
    freopen("circle.in", "r", stdin);
    freopen("circle.out", "w", stdout);
    std::cin >> t;
    while (t--) mian();
    return 0;
}