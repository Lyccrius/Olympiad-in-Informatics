#include <iostream>

typedef char chr;
typedef unsigned long long ull;

const int maxN = 1000;
const int maxM = 1000;
const int maxX = 100;
const int maxY = 100;
const ull base1 = 131;
const ull base2 = 13331;

int t;
int n, m;
int x, y;
chr A[maxN + 10][maxM + 10];
chr B[maxX + 10][maxY + 10];
ull a[maxN + 10][maxM + 10];
ull b[maxN + 10][maxM + 10];
ull p1[maxM + 10];
ull p2[maxN + 10];
int ans;

void init() {
    p1[0] = 1;
    p2[0] = 1;
    for (int i = 1; i <= maxM; i++) p1[i] = p1[i - 1] * base1;
    for (int i = 1; i <= maxN; i++) p2[i] = p2[i - 1] * base2;
    return;
}

ull hash(int x1, int y1, int x2, int y2) {
    //printf("(%d, %d), (%d, %d) = %u\n", x1, y1, x2, y2,  a[x2][y2] - a[x1 - 1][y2] * p2[x] - a[x2][y1 - 1] * p1[y] + a[x1 - 1][y1 - 1] * p2[x] * p1[y]);
    return a[x2][y2] - a[x1 - 1][y2] * p2[x] - a[x2][y1 - 1] * p1[y] + a[x1 - 1][y1 - 1] * p2[x] * p1[y];
}

void mian() {
    ans = 0;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cin >> A[i][j];
        }
    }
    std::cin >> x >> y;
    for (int i = 1; i <= x; i++) {
        for (int j = 1; j <= y; j++) {
            std::cin >> B[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            a[i][j] = A[i][j] - 'a';
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            a[i][j] = a[i][j] + a[i][j - 1] * base1;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            a[i][j] = a[i][j] + a[i - 1][j] * base2;
        }
    }
    /*
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                printf("%u ", a[i][j]);
            }
            printf("\n");
        }
            printf("\n");
    */
    for (int i = 1; i <= x; i++) {
        for (int j = 1; j <= y; j++) {
            b[i][j] = B[i][j] - 'a';
        }
    }
    for (int i = 1; i <= x; i++) {
        for (int j = 1; j <= y; j++) {
            b[i][j] = b[i][j] + b[i][j - 1] * base1;
        }
    }
    for (int i = 1; i <= x; i++) {
        for (int j = 1; j <= y; j++) {
            b[i][j] = b[i][j] + b[i - 1][j] * base2;
        }
    }
    //printf("b = %u\n", b[x][y]);
    for (int i = 1; i <= n - x + 1; i++) {
        for (int j = 1; j <= m - y + 1; j++) {
            if (hash(i, j, i + x - 1, j + y - 1) == b[x][y]) {
                ans++;
                //printf("(%d, %d)\n", i, j);
            }
        }
    }
    std::cout << ans << '\n';
    return;
}

int main() {
    init();
    std::cin >> t;
    while (t--) mian();
    return 0;
}