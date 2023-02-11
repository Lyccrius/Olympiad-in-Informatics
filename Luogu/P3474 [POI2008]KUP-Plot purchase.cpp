#include <iostream>
#include <stack>

typedef long long lxl;

const int maxN = 2000;

lxl k, n;
lxl a[maxN + 10][maxN + 10];
lxl b[maxN + 10][maxN + 10];
lxl u[maxN + 10][maxN + 10];
lxl l[maxN + 10];
lxl r[maxN + 10];
std::stack<int> s;
lxl mat;
int x1, x2;
int y1, y2;

bool check(lxl x) {
    return k <= x && x <= k * 2;
}

int main() {
    std::cin >> k >> n;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) std::cin >> a[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) b[i][j] = b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1] + a[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
        if (check(a[i][j])) {
            std::cout << j << ' ' << i << ' ' << j << ' ' << i;
            return 0;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] < k) {
                u[i][j] = u[i - 1][j] + 1;
            }
        }
        while (!s.empty()) s.pop();
        s.push(0);
        u[i][0] = -1;
        for (int j = 1; j <= n; j++) {
            while (!s.empty() && u[i][s.top()] >= u[i][j]) s.pop();
            if (!s.empty()) l[j] = s.top(); l[j]++;
            s.push(j);
        }
        while (!s.empty()) s.pop();
        s.push(n + 1);
        u[i][n + 1] = -1;
        for (int j = n; j >= 1; j--) {
            while (!s.empty() && u[i][s.top()] >= u[i][j]) s.pop();
            if (!s.empty()) r[j] = s.top(); r[j]--;
            s.push(j);
        }
        for (int j = 1; j <= n; j++) {
            if (u[i][j]) {
                int sx = i - u[i][j] + 1;
                int sy = l[j];
                int tx = i;
                int ty = r[j];
                lxl sum = b[tx][ty] - b[sx - 1][ty] - b[tx][sy - 1] + b[sx - 1][sy - 1];
                if (sum >= mat) {
                    mat = sum;
                    x1 = sx;
                    y1 = sy;
                    x2 = tx;
                    y2 = ty;
                }
                if (check(sum)) {
                    std::cout << sy << ' ' << sx << ' ' << ty << ' ' << tx;
                    return 0;
                }
            }
        }
    }
    if (mat < k) {
        std::cout << "NIE";
        return 0;
    }
    for (int x = x2; x >= x1; x--) {
        lxl sum = b[x][y2] - b[x - 1][y2] - b[x][y1 - 1] + b[x - 1][y1 - 1];
        if (check(sum)) {
            std::cout << y1 << ' ' << x << ' ' << y2 << ' ' << x;
            return 0;
        }
        if (sum > k * 2) {
            mat = sum;
            for (int y = y2; y >= y1; y--) {
                mat -= a[x][y];
                if (check(mat)) {
                    std::cout << y1 << ' ' << x << ' ' << y - 1 << ' ' << x;
                    return 0;
                }
            }
        } else {
            mat -= sum;
            if (check(mat)) {
                std::cout << y1 << ' ' << x1 << ' ' << y2 << ' ' << x - 1;
                return 0;
            }
        }
    }
    return 0;
}