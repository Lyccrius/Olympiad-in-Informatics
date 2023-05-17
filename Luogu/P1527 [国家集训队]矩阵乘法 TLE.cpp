#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

typedef std::vector<int > vic;

const int maxN = 500;
const int maxQ = 6e4;
const int maxA = 1e9;

int n, q;
int a[maxN + 10][maxN + 10];
int b[maxN + 10][maxN + 10];
int x_1, y_1, x_2, y_2, k;
int ans[maxQ + 10];
vic raw;

struct Query {
    int i;
    int x_1, y_1;
    int x_2, y_2;
    int k;
};

std::deque<Query> querys;

void solve(int l, int r, std::deque<Query> q) {
    if (l == r) {
        for (int i = 0; i < q.size(); i++) ans[q[i].i] = l;
        return;
    }
    std::deque<Query> ql;
    std::deque<Query> qr;
    int mid = (l + r) / 2;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (l <= a[i][j] && a[i][j] <= mid) b[i][j] = 1; else b[i][j] = 0;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) b[i][j] = b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1] + b[i][j];
    for (int i = 0; i < q.size(); i++) {
        int x_1 = q[i].x_1;
        int y_1 = q[i].y_1;
        int x_2 = q[i].x_2;
        int y_2 = q[i].y_2;
        int t = b[x_2][y_2] - b[x_1 - 1][y_2] - b[x_2][y_1 - 1] + b[x_1 - 1][y_1 - 1];
        if (t >= q[i].k) ql.push_back(q[i]);
        else q[i].k -= t, qr.push_back(q[i]);
    }
    if (ql.size()) solve(l, mid, ql);
    if (qr.size()) solve(mid + 1, r, qr);
    return;
}

int main() {
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) std::cin >> a[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) raw.push_back(a[i][j]);
    std::sort(raw.begin(), raw.end());
    raw.erase(std::unique(raw.begin(), raw.end()), raw.end());
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) a[i][j] = std::lower_bound(raw.begin(), raw.end(), a[i][j]) - raw.begin();
    for (int i = 1; i <= q; i++) {
        std::cin >> x_1 >> y_1 >> x_2 >> y_2 >> k;
        querys.push_back((Query) {i, x_1, y_1, x_2, y_2, k});
    }
    solve(0, raw.size(), querys);
    for (int i = 1; i <= q; i++) std::cout << raw[ans[i]] << '\n';
    return 0;
}