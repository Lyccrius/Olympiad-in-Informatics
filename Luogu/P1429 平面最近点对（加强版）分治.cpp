#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

const int maxN = 2e5;
const int inf = 1e9;

int n;
int x, y;

struct Node {
    int x;
    int y;
} node[maxN + 10];

bool cmpByX(const Node &a, const Node &b) {
    return a.x < b.x;
}

bool cmpByY(const Node &a, const Node &b) {
    return a.y < b.y;
}

double dis(const Node &a, const Node &b) {
    double dX = a.x - b.x;
    double dY = a.y - b.y;
    return std::sqrt(dX * dX + dY * dY);
}

double solve(int l, int r) {
    //printf("solve(%d, %d)\n", l, r);
    int mid = (l + r) / 2;
    if (r == l + 1) return dis(node[l], node[r]);
    if (r == l + 2) return std::min(dis(node[l], node[r]), std::min(dis(node[l], node[l + 1]), dis(node[r - 1], node[r])));
    double d = std::min(solve(l, mid), solve(mid + 1, r));
    //printf("d = %.4lf\n", d);
    std::vector<Node> s;
    std::queue<Node> q;
    for (int i = l; i <= r; i++) if (node[mid].x - d <= node[i].x && node[i].x <= node[mid].x + d) s.push_back(node[i]);
    //printf("sortingByY\n");
    std::sort(s.begin(), s.end(), cmpByY);
    //printf("sortedByY\n");
    for (int i = 0; i < s.size(); i++) {
        for (int j = i + 1; j < s.size(); j++) {
            if (s[i].y + d <= s[j].y) break;
            d = std::min(d, dis(s[i], s[j]));
        }
    }
    return d;
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> x >> y, node[i].x = x, node[i].y = y;
    std::sort(node + 1, node + n + 1, cmpByX);
    printf("%.4lf", solve(1, n));
    return 0;
}