#include <iostream>
#include <algorithm>

const int maxN = 2e5;
const int inf = 2e9 + 10;

int n;
int x[maxN + 10], w[maxN + 10];

struct Node {
    int l, r;

    bool operator<(const Node &other) const {
        if (r != other.r) return r < other.r;
        return l < other.l;
    }
} node[maxN + 10];

int head = - inf;
int ans;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> x[i] >> w[i];
    for (int i = 1; i <= n; i++) node[i].l = x[i] - w[i];
    for (int i = 1; i <= n; i++) node[i].r = x[i] + w[i];
    std::sort(node + 1, node + n + 1);
    for (int i = 1; i <= n; i++) {
        if (node[i].l >= head) {
            head = node[i].r;
            ans++;
        }
    }
    std::cout << ans;
    return 0;
}