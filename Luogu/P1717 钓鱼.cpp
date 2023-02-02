#include <iostream>
#include <algorithm>
#include <queue>

const int maxN = 25;
const int maxH = 16;

int n;
int H;
int f[maxN + 10];
int d[maxN + 10];
int t[maxN + 10];
int res;
int ans;

struct Node {
    int f;
    int i;

    bool operator<(const Node &other) const {
        return f < other.f;
    }
};

int main() {
    std::cin >> n;
    std::cin >> H;
    H *= 12;
    for (int i = 1; i <= n; i++) std::cin >> f[i];
    for (int i = 1; i <= n; i++) std::cin >> d[i];
    for (int i = 1; i < n; i++) std::cin >> t[i];
    for (int i = 1; i <= n; i++) {
        res = 0;
        H -= t[i - 1];
        if (H <= 0) break;
        std::priority_queue<Node> q;
        for (int j = 1; j <= i; j++) q.push((Node) {f[j], j});
        for (int j = 1; j <= H; j++) {
            Node node = q.top();
            q.pop();
            if (node.f < 0) break;
            res += node.f;
            q.push((Node) {node.f - d[node.i], node.i});
        }
        ans = std::max(ans, res);
    }
    std::cout << ans;
    return 0;
}