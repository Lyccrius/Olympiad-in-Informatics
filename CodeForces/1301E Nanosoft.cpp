#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef char chr;

const int maxN = 500;
const int maxM = 500;
const int maxQ = 3e5;

int n, m;
int q;
int r1, c1, r2, c2;
chr mat[maxN + 10][maxM + 10];
int cnt[maxN + 10][maxM + 10][5];
int res[maxN + 10][maxM + 10][250 + 10];

int get(int r1, int c1, int r2, int c2, int col) {
    return cnt[r2][c2][col] - cnt[r1 - 1][c2][col] - cnt[r2][c1 - 1][col] + cnt[r1 - 1][c1 - 1][col];
}

bool is(int i, int j, int k) {
    if (i + k + k - 1 > n) return false;
    if (j + k + k - 1 > m) return false;
    if (get(i, j, i + k - 1, j + k - 1, 1) != k * k) return false;
    if (get(i + k, j, i + k + k - 1, j + k - 1, 2) != k * k) return false;
    if (get(i + k, j + k, i + k + k - 1, j + k + k - 1, 3) != k * k) return false;
    if (get(i, j + k, i + k - 1, j + k + k - 1, 4) != k * k) return false;
    return true;
}

bool check(int r1, int c1, int r2, int c2, int k) {
    if (r2 - k - k + 1 < r1) return false;
    if (c2 - k - k + 1 < c1) return false;
    return res[r2 - k - k + 1][c2 - k - k + 1][k] - res[r1 - 1][c2 - k - k + 1][k] - res[r2 - k - k + 1][c1 - 1][k] + res[r1 - 1][c1 - 1][k];
}

void mian() {
    std::cin >> r1 >> c1 >> r2 >> c2;
    if (!check(r1, c1, r2, c2, 1)) {
        std::cout << 0 << '\n';
        return;
    }
    int l = 1;
    int r = 250;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (check(r1, c1, r2, c2, mid)) l = mid;
        else r = mid - 1;
    }
    std::cout << 4 * l * l << '\n';
    return;
}

int main() {
    promote();
    std::cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) std::cin >> mat[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (mat[i][j] == 'R') cnt[i][j][1]++;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (mat[i][j] == 'Y') cnt[i][j][2]++;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (mat[i][j] == 'B') cnt[i][j][3]++;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (mat[i][j] == 'G') cnt[i][j][4]++;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) for (int k = 1; k <= 4; k++) cnt[i][j][k] += cnt[i - 1][j][k] + cnt[i][j - 1][k] - cnt[i - 1][j - 1][k];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) for (int k = 1; k <= 250; k++) if (is(i, j, k)) res[i][j][k]++;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) for (int k = 1; k <= 250; k++) res[i][j][k] += res[i - 1][j][k] + res[i][j - 1][k] - res[i - 1][j - 1][k];
    while (q--) mian();
    return 0;
}