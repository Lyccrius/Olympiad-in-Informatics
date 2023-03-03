#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 5e4;
const int logN = 16;

int n;
int a[maxN * 2 + 10];
int m;
int x, y;

struct CatTree {
    int N;
    int log[maxN * 4 + 10];
    int res[logN + 1 + 5][maxN * 2 + 10];
    int fix[logN + 1 + 5][maxN * 2 + 10];
    int pos[maxN * 2 + 10];

    void Build(int u, int l, int r, int dep) {
        if (l == r) {
            pos[l] = u;
            return;
        }
        int mid = (l + r) / 2;
        int pre;
        int sum;
        pre = a[mid];
        sum = a[mid]; sum = std::max(sum, 0);
        res[dep][mid] = a[mid];
        fix[dep][mid] = a[mid];
        for (int i = mid - 1; i >= l; i--) {
            pre += a[i];
            sum += a[i];
            res[dep][i] = std::max(res[dep][i + 1], sum);
            fix[dep][i] = std::max(fix[dep][i + 1], pre);
            sum = std::max(sum, 0);
        }
        pre = a[mid + 1];
        sum = a[mid + 1]; sum = std::max(sum, 0);
        res[dep][mid + 1] = a[mid + 1];
        fix[dep][mid + 1] = a[mid + 1];
        for (int i = mid + 2; i <= r; i++) {
            pre += a[i];
            sum += a[i];
            res[dep][i] = std::max(res[dep][i - 1], sum);
            fix[dep][i] = std::max(fix[dep][i - 1], pre);
            sum = std::max(sum, 0);
        }
        Build(u * 2, l, mid, dep + 1);
        Build(u * 2 + 1, mid + 1, r, dep + 1);
        return;
    }

    void Init() {
        N = 2;
        while (N < n) N *= 2;
        for (int i = 2; i <= N * 2; i++) log[i] = log[i / 2] + 1;
        Build(1, 1, N, 1);
        return;
    }

    int Query(int l, int r) {
        if (l == r) return a[l];
        int dep = log[pos[l]] - log[pos[l] ^ pos[r]];
        int ret = std::max(res[dep][l], res[dep][r]);
        ret = std::max(ret, fix[dep][l] + fix[dep][r]);
        return ret;
    }
} CT;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    CT.Init();
    std::cin >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y;
        std::cout << CT.Query(x, y) << '\n';
    }
    return 0;
}