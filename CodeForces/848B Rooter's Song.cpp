#include <iostream>
#include <algorithm>
#include <vector>

const int maxN = 1e5;
const int maxW = 1e5;
const int maxH = 1e5;

int n, w, h;
int g[maxN + 10], p[maxN + 10], t[maxN + 10];

struct Node {
    int i;
    int x, y;

    bool operator<(const Node &other) const {
        if (y != other.y) return y > other.y;
        return x < other.x;
    }
};

typedef std::vector<Node> vnc;

vnc vec[maxW + maxH + 10];
vnc que[maxW + maxH + 10];
Node ans[maxN + 10];

int main() {
    std::cin >> n >> w >> h;
    for (int i = 1; i <= n; i++) {
        std::cin >> g[i] >> p[i] >> t[i];
        if (g[i] == 1) vec[p[i] - t[i] + maxH].push_back((Node) {i, p[i], 0});
        if (g[i] == 2) vec[p[i] - t[i] + maxH].push_back((Node) {i, 0, p[i]});
    }
    for (int i = 1; i <= maxW + maxH; i++) {
        for (auto j : vec[i]) {
            if (j.y == 0) que[i].push_back((Node) {i, j.x, h});
            if (j.y != 0) que[i].push_back((Node) {i, w, j.y});
        }
        std::sort(vec[i].begin(), vec[i].end());
        std::sort(que[i].begin(), que[i].end());
        for (int j = 0; j < vec[i].size(); j++) ans[vec[i][j].i] = que[i][j];
    }
    for (int i = 1; i <= n; i++) std::cout << ans[i].x << ' ' << ans[i].y << '\n';
    return 0;
}