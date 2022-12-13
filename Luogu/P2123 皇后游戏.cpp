#include <cstdio>
#include <cmath>
#include <algorithm>

const int maxN = 20000 + 10;

int T;
int n;
int a[maxN], b[maxN];

struct Node {
    int a, b;
    long long c;
    int d;

    bool operator<(Node other) const {
        if (d != other.d) return d < other.d;
        if (d <= 0) return a < other.a;
        return b > other.b;
    }
} node[maxN];

void mian() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]);
    for (int i = 1; i <= n; i++) node[i].a = a[i], node[i].b = b[i];
    for (int i = 1; i <= n; i++) if (a[i] < b[i]) node[i].d = -1; else if (a[i] == b[i]) node[i].d = 0; else node[i].d = 1;
    std::sort(node + 1, node + n + 1);
    long long sum = 0;
    for (int i = 1; i <= n; i++) sum += node[i].a, node[i].c = std::max(node[i - 1].c, sum) + node[i].b;
    printf("%lld\n", node[n].c);
    return;
}

int main() {
    scanf("%d", &T);
    while (T--) mian();
    return 0;
}