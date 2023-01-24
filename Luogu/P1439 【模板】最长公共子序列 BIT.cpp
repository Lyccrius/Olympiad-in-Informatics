#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e5;

int n;
int P1[maxN + 10];
int P2[maxN + 10];
int P[maxN + 10];
int f[maxN + 10];
int ans;

int lowbit(int val) {
    return val & -val;
}

struct BinaryIndexedTree {
    int node[maxN + 10];

    void Add(int pos, int val) {
        while (pos <= n) {
            node[pos] = std::max(node[pos], val);
            pos += lowbit(pos);
        }
        return;
    }

    int Ask(int pos) {
        int ret = 0;
        while (pos >= 1) {
            ret = std::max(ret, node[pos]);
            pos -= lowbit(pos);
        }
        return ret;
    }
} BIT;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> P1[i];
    for (int i = 1; i <= n; i++) std::cin >> P2[i], P[P2[i]] = i;
    for (int i = 1; i <= n; i++) {
        f[i] = BIT.Ask(P[P1[i]]) + 1;
        BIT.Add(P[P1[i]], f[i]);
        ans = std::max(ans, f[i]);
    }
    std::cout << ans << '\n';
    return 0;
}