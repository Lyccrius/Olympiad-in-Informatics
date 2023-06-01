#include <iostream>
#include <vector>

typedef std::vector<int> vic;

const int maxN = 5e4;

int n;
int a, b, c, d, k;
vic p;
int vis[maxN + 10];
int mob[maxN + 10];
int pre[maxN + 10];

void init() {
    mob[1] = 1;
    for (int i = 2; i <= maxN; i++) {
        if (!vis[i]) {
            p.push_back(i);
            mob[i] = -1;
        }
        for (auto j : p) {
            if (i * j > maxN) break;
            vis[i * j] = true;
            if (i % j == 0) {
                mob[i * j] = 0;
                break;
            } else {
                mob[i * j] = - mob[i];
            }
        }
    }
    for (int i = 1; i <= maxN; i++) pre[i] = pre[i - 1] + mob[i];
    return;
}

int solve(int n, int m) {
    int ret = 0;
    for (int l = 1, r; l <= std::min(n, m); l = r + 1) {
        r = std::min(n / (n / l), m / (m / l));
        ret += (pre[r] - pre[l - 1]) * (n / l) * (m / l);
    }
    return ret;
}

void mian() {
    std::cin >> a >> b >> c >> d >> k;
    std::cout << solve(b / k, d / k) - solve(b / k, (c - 1) / k) - solve((a - 1) / k, d / k) + solve((a - 1) / k, (c - 1) / k) << '\n';
    return;
}

int main() {
    init();
    std::cin >> n;
    while (n--) mian();
    return 0;
}