#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e6;
const int maxM = 1e6;

int n, m;
int a[maxN + 10];
char o; int x, y, k;

struct ZKWSegmentTree {
    struct Node {
        int val;
    } node[maxN * 2 + 10];

    int N;

    void Build() {
        N = 1;
        while (N <= n + 1) N *= 2;
        for (int i = N + 1; i <= N + n; i++) node[i].val = a[i - N];
        for (int i = N - 1; i >= 1; i--) node[i].val = node[i * 2].val + node[i * 2 + 1].val;
        return;
    }

    void Add(int pos, int val) {
        for (int i = N + pos; i; i /= 2) node[i].val += val;
        return;
    }

    int Sum(int s, int t) {
        int ret = 0;
        for (int l = N + s - 1, r = N + t + 1; l / 2 != r / 2; l /= 2, r /= 2) {
            if ((l & 1) == 0) ret += node[l + 1].val;
            if ((r & 1) == 1) ret += node[r - 1].val;
        }
        return ret;
    }
} SGT;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i]; SGT.Build();
    for (int i = 1; i <= m; i++) {
        std::cin >> o;
        if (o == 'M') {
            std::cin >> x >> k;
            SGT.Add(x, - a[x]);
            a[x] = k;
            SGT.Add(x, a[x]);
        } else {
            std::cin >> x >> y;
            std::cout << SGT.Sum(x, y) << '\n';
        }
    }
    return 0;
}