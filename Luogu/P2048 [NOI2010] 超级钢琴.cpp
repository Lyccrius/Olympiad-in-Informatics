#include <iostream>
#include <queue>
#include <cmath>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 5e5;
const int maxK = 5e5;
const int logN = 19;

int n, k, L, R;
int A[maxN + 10];
int B[maxN + 10];

struct SpareTable {
    int f[maxN + 10][logN + 5];
    int g[maxN + 10][logN + 5];

    void Init() {
        for (int i = 1; i <= n; i++) f[i][0] = B[i];
        for (int i = 1; i <= n; i++) g[i][0] = i;
        for (int p = 1; p <= logN; p++) {
            for (int i = 1; i <= n; i++) {
                if (i + (1 << p) - 1 > n) break;
                int j = i + (1 << (p - 1));
                if (f[i][p - 1] > f[j][p - 1]) {
                    f[i][p] = f[i][p - 1];
                    g[i][p] = g[i][p - 1];
                } else {
                    f[i][p] = f[j][p - 1];
                    g[i][p] = g[j][p - 1];
                }
            }
        }
        return;
    }

    int Query(int l, int r) {
        int p = std::log2(r - l + 1);
        r = r - (1 << p) + 1;
        if (f[l][p] > f[r][p]) return g[l][p];
        else return g[r][p];
    }
} ST;

struct Node {
    int i;
    int g;
    int l;
    int r;
    int res;

    bool operator<(const Node &other) const {
        return res < other.res;
    }
};

std::priority_queue<Node> q;
lxl ans;

int main() {
    promote();
    std::cin >> n >> k >> L >> R;
    for (int i = 1; i <= n; i++) std::cin >> A[i];
    for (int i = 1; i <= n; i++) B[i] = B[i - 1] + A[i];
    ST.Init();
    for (int i = 1; i + L - 1 <= n; i++) {
        int l = i + L - 1;
        int r = std::min(i + R - 1, n);
        int g = ST.Query(l, r);
        q.push((Node) {i, g, l, r, B[g] - B[i - 1]});
    }
    while (k--) {
        Node node = q.top();
        q.pop();
        ans += node.res;
        if (node.g > node.l) {
            int g = ST.Query(node.l, node.g - 1);
            q.push((Node) {node.i, g, node.l, node.g - 1, B[g] - B[node.i - 1]});
        }
        if (node.g < node.r) {
            int g = ST.Query(node.g + 1, node.r);
            q.push((Node) {node.i, g, node.g + 1, node.r, B[g] - B[node.i - 1]});
        }
    }
    std::cout << ans << '\n';
    return 0;
}