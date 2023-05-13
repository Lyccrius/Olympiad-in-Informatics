#include <iostream>

typedef char chr;
typedef unsigned long long ull;

const int maxN = 1000;
const int maxM = 1000;

int n, m;
ull a[maxN + 10][maxM + 10];
int ans;

struct Hash {
    int n, m;
    ull base1;
    ull base2;
    ull p1[maxN + 10];
    ull p2[maxM + 10];
    ull a[maxN + 10][maxM + 10];

    Hash() {
        base1 = 13331;
        base2 = 131;
    }

    void init() {
        p1[0] = 1;
        p2[0] = 1;
        for (int i = 1; i <= n; i++) p1[i] = p1[i - 1] * base1;
        for (int i = 1; i <= m; i++) p2[i] = p2[i - 1] * base2;
        return;
    }
    
    void calc() {
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) a[i][j] += a[i][j - 1] * base2;
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) a[i][j] += a[i - 1][j] * base1;
        return;
    }

    void show() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                std::cout << a[i][j] << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

    ull hash(int x1, int y1, int x2, int y2) {
        return a[x2][y2] - a[x1 - 1][y2] * p1[x2 - x1 + 1] - a[x2][y1 - 1] * p2[y2 - y1 + 1] + a[x1 - 1][y1 - 1] * p1[x2 - x1 + 1] * p2[y2 - y1 + 1];
    }
} A, X, Y;

bool check1(int x, int y, int len) {
    int x1 = x - len + 1;
    int x2 = x + len - 1;
    int y1 = y - len + 1;
    int y2 = y + len - 1;
    if (A.hash(x1, y1, x2, y2) != X.hash(n - x2 + 1, y1, n - x1 + 1, y2)) return false;
    if (A.hash(x1, y1, x2, y2) != Y.hash(x1, m - y2 + 1, x2, m - y1 + 1)) return false;
    return true;
}

int solve1(int x, int y) {
    int l = 1;
    int r = std::min(std::min(x, n - x + 1), std::min(y, m - y + 1));
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (check1(x, y, mid)) l = mid;
        else r = mid - 1;
    }
    return l;
}

bool check2(int x, int y, int len) {
    int x1 = x - len;
    int x2 = x + len - 1;
    int y1 = y - len;
    int y2 = y + len - 1;
    if (A.hash(x1, y1, x2, y2) != X.hash(n - x2 + 1, y1, n - x1 + 1, y2)) return false;
    if (A.hash(x1, y1, x2, y2) != Y.hash(x1, m - y2 + 1, x2, m - y1 + 1)) return false;
    return true;
}

int solve2(int x, int y) {
    int l = 0;
    int r = std::min(std::min(x - 1, n - x + 1), std::min(y - 1, m - y + 1));
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (check2(x, y, mid)) l = mid;
        else r = mid - 1;
    }
    return l;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) std::cin >> a[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) A.a[i][j] = a[i][j]; A.n = n; A.m = m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) X.a[i][j] = a[n - i + 1][j]; X.n = n; X.m = m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) Y.a[i][j] = a[i][m - j + 1]; Y.n = n; Y.m = m;
    A.init(); A.calc();
    X.init(); X.calc();
    Y.init(); Y.calc();
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) ans += solve1(i, j) + solve2(i, j);
    std::cout << ans << '\n';
    return 0;
}