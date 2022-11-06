#include <cstdio>
#include <algorithm>
#include <stack>

const int maxn = 1e5 + 10;

int n;
int h[maxn];

struct Node {
    int height;
    int width;
};

std::stack<Node> rectangle;

int main() {
    while (scanf("%lld", &n) == 1 && n) {
        long long ans = 0;
        while (!rectangle.empty()) rectangle.pop();
        for (int i = 1; i <= n; i++) scanf("%lld", &h[i]); h[n + 1] = 0;
        for (int i = 1; i <= n + 1; i++) {
            if (!rectangle.empty() && rectangle.top().height < h[i]) {
                rectangle.push((Node){h[i], 1});
                continue;
            }
            int w = 0;
            while (!rectangle.empty() && rectangle.top().height > h[i]) {
                Node top = rectangle.top();
                rectangle.pop();
                w += top.width;
                ans = std::max(ans, (long long)w * top.height);
            }
            rectangle.push((Node){h[i], w + 1});
        }
        printf("%lld\n", ans);
    }
    return 0;
}