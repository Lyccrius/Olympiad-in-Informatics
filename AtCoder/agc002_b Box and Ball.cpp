#include <iostream>

const int maxN = 1e5;
const int maxM = 1e5;

int n, m;
int x, y;
int c[maxN + 10];
int r[maxN + 10];
int s;

int main() {
    r[1] = 1;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) c[i] = 1;
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y;
        if (c[x] == 0) continue;
        c[x]--;
        c[y]++;
        if (r[x]) r[y] = true;
        if (c[x] == 0) r[x] = false;
    }
    for (int i = 1; i <= n; i++) if (r[i]) s++;
    std::cout << s;
    return 0;
}