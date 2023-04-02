#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <vector>
#include <cmath>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long double dbl;
typedef std::set<int> sit;
typedef std::vector<int> vic;

const int maxN = 1e3;
const dbl inf = 3e18;

int n; int k;
dbl x[maxN + 10], y[maxN + 10];
dbl d[maxN + 10][maxN + 10];
dbl D = inf;
int N = 5;

dbl dis(dbl x1, dbl y1, dbl x2, dbl y2) {
    dbl dx = x1 - x2;
    dbl dy = y1 - y2;
    return std::sqrt(dx * dx + dy * dy);
}

struct Pro {
    int u;
    dbl w;

    bool operator<(const Pro &other) const {
        return w < other.w;
    }
};

std::vector<Pro> pro[maxN + 10];

void init() {
    N = std::min(N, n - 1);
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            dbl t = dis(x[i], y[i], x[j], y[j]);
            d[i][j] = t;
            d[j][i] = t;
            D = std::min(D, t);
        }
        for (int j = 1; j <= n; j++) {
            pro[i].push_back((Pro) {j, d[i][j]});
        }
        std::sort(pro[i].begin(), pro[i].end());
    }
    for (int i = 1; i <= n; i++) {
        if (k == 0 || y[i] > y[k] || y[i] == y[k] && i < k) {
            k = i;
        }
    }
    return;
}

struct Node {
    dbl g;
    dbl h;
    sit s;
    vic v;

    bool operator<(const Node &other) const {
        return g + h > other.g + other.h;
    }
} ans;

void Astar() {
    ans.g = inf;
    Node node;
    node.g = 0;
    node.h = D * (n - 1);
    node.s.insert(k);
    node.v.push_back(k);
    std::priority_queue<Node> q;
    q.push(node);
    while (q.size()) {
        Node node = q.top(); q.pop();
        if (node.g + node.h > ans.g) break;
        //printf("%d, %d, %d\n", node.g, node.h, node.v.size());
        if (node.v.size() == n) {
            //std::cout << node.g << '\n';
            if (node.g < ans.g || ans.v.size() == 0) {
                ans = node;
            }
            continue;
        }
        int u = node.v.back();
        for (int i = 1; i <= N; i++) {
            int v = pro[u][i].u;
            int w = pro[u][i].w;
            if (node.s.count(v)) continue;
            Node n0de = node;
            n0de.g += w;
            n0de.h -= D;
            n0de.s.insert(v);
            n0de.v.push_back(v);
            if (n0de.g + n0de.h <= ans.g) q.push(n0de);
        }
    }
    for (auto i : ans.v) std::cout << i << ' ';
    return;
}

void A() {
    if (k == n) {
        for (int i = n; i >= 1; i--) std::cout << i << ' ';
        return;
    }
    dbl ld = std::fabs(y[k] - y[k - 1]);
    dbl rd = std::fabs(y[k] - y[k + 1]);
    std::cout << k << ' ';
    if (ld < rd) {
        for (int i = k - 1; i >= 1; i--) std::cout << i << ' ';
        for (int i = n; i >= k + 1; i--) std::cout << i << ' ';
    } else {
        for (int i = k + 1; i <= n; i++) std::cout << i << ' ';
        for (int i = 1; i <= k - 1; i++) std::cout << i << ' ';
    }
    return;
}

void B() {
    for (int i = 1; i <= n; i++) std::cout << i << ' ';
    return;
}

void Subtask() {
    if (k == 1) B();
    else A();
    return;
}

int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    promote();
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> x[i] >> y[i]; init();
    if (n <= 18) Astar();
    else Subtask();
    //std::cout << ans.g;
    return 0;
}