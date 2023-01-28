#include <iostream>
#include <queue>
#include <cstring>

const int maxN = 100;

int t;
int n;
int a[maxN + 10][maxN + 10];
int c[maxN + 10];
int v[maxN + 10];

void mian() {
    std::memset(c, 0, sizeof(c));
    std::memset(v, 0, sizeof(v));
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < n; j++) {
            std::cin >> a[i][j];
        }
    }
    int end;
    for (int i = 1; i <= n; i++) c[a[i][n - 1]]++;
    for (int i = 1; i <= n; i++) if (c[i] == n - 1) end = i;
    //printf("end = %d\n", end);
    std::memset(c, 0, sizeof(c));
    for (int j = 1; j < n; j++) {
        int res = 0;
        for (int i = 1; i <= n; i++) {
            c[a[i][j]]++;
            if (c[a[i][j]] == n - 1 && a[i][j] != end) {
                res = a[i][j];
            }
        }
        std::cout << res << ' ';
        v[res] = true;
    }
    std::cout << end;
    std::cout << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}