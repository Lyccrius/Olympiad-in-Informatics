#include <cstdio>
#include <algorithm>
#include <queue>

const int maxn = 1e5 + 10;

int n, k;
long long w;

long long ans = 0;

struct Node {
    long long w;
    long long h;
    bool operator<(Node other) const {
        if (w == other.w) return h > other.h;
        return w > other.w;
    }
};

std::priority_queue<Node> q;

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &w);
        q.push((Node){w, 1});
    }
    while ((q.size() - 1) % (k - 1)) q.push((Node){0, 1});
    while (q.size() >= k) {
        long long h = -1;
        w = 0;
        for (int i = 1; i <= k; i++) {
            Node t = q.top();
            q.pop();
            h = std::max(h, t.h);
            w += t.w;
        }
        ans += w;
        q.push((Node){w, h + 1});
    }
    printf("%lld\n%lld\n", ans, q.top().h - 1);
    return 0;
}