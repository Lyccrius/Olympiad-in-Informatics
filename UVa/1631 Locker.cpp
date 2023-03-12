#include <iostream>
#include <algorithm>
#include <cstring>

typedef char chr;

const int maxN = 1000;
const int inf = 1e9;

int n;
chr A[maxN + 10], B[maxN + 10];
int a[maxN + 10], b[maxN + 10];
int f[maxN + 10][10][10][10];
int g[maxN + 10][10][10][10];

int cnt;

int t(int a, int b) {
    return ((a + b) % 10 + 10) % 10;
}

int DFS(int cur, int x, int y, int z) {
    if (cur >= n) return 0;
    if (g[cur][x][y][z]) return f[cur][x][y][z];
    g[cur][x][y][z] = true;
    int d;
    d = t(b[cur + 1], - x);
    for (int i = 0; i <= d; i++) {
        for (int j = 0; j <= i; j++) {
            f[cur][x][y][z] = std::min(f[cur][x][y][z], DFS(cur + 1, t(y, i), t(z, j), a[cur + 4]) + d);
        }
    }
    d = t(x, - b[cur + 1]);
    for (int i = 0; i <= d; i++) {
        for (int j = 0; j <= i; j++) {
            f[cur][x][y][z] = std::min(f[cur][x][y][z], DFS(cur + 1, t(y, - i), t(z, - j), a[cur + 4]) + d);
        }
    }
    //if (f[cur][x][y][z] < inf) 
    //printf("%d %d %d %d: %d\n", cur, x, y, z, f[cur][x][y][z]);
    return f[cur][x][y][z];
}

void mian() {
    std::memset(f, 0x3f, sizeof(f));
    std::memset(g, 0, sizeof(g));
    n = std::strlen(A + 1);
    for (int i = 1; i <= n; i++) a[i] = A[i] - '0';
    for (int i = 1; i <= n; i++) b[i] = B[i] - '0';
    std::cout << DFS(0, a[1], a[2], a[3]) << '\n';
    return;
}

int main() {
    //freopen("test.in", "r", stdin);
    //freopen("test.out", "w", stdout);
    while (scanf("%s%s", A + 1, B + 1) != EOF) mian();
    return 0;
}