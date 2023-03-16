#include <iostream>
#include <cstring>

typedef char chr;

const int maxN = 10;
const int maxM = 10;

int kase;
int n, m;
int a[maxN + 10][maxM + 10];
int r[maxN + 10];
int c[maxM + 10];
int s[maxN + 10];
int e[maxM + 10];
int lim;

void init() {
    kase++;
    std::memset(a, 0, sizeof(a));
    std::memset(r, 0, sizeof(r));
    std::memset(c, 0, sizeof(c));
    std::memset(s, 0, sizeof(s));
    std::memset(e, 0, sizeof(e));
    return;
}

bool check() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!a[i][j]) continue;
            if (r[i]) continue;
            if (c[j]) continue;
            if (s[i + j - 1]) continue;
            if (e[j - i + 9]) continue;
            return false;
        }
    }
    return true;
}

bool vis(int i, int j) {
    if (!r[i]) return false;
    if (!c[j]) return false;
    if (!s[i + j - 1]) return false;
    if (!e[j - i + 9]) return false;
    return true;
}

bool DFS(int now) {
    if (now == lim) {
        if (check()) {
            return true;
        } else {
            return false;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (vis(i, j)) continue;
            int br = r[i];
            int bc = c[j];
            int bs = s[i + j - 1];
            int be = e[j - i + 9];
            r[i] = true;
            c[j] = true;
            s[i + j - 1] = true;
            e[j - i + 9] = true;
            if (DFS(now + 1)) return true;
            r[i] = br;
            c[j] = bc;
            s[i + j - 1] = bs;
            e[j - i + 9] = be;
        }
    }
    return false;
}

void mian() {
    init();
    chr ch;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cin >> ch;
            if (ch == 'X') {
                a[i][j] = true; 
            } else {
                a[i][j] = false;
            }
        }
    }
    for (lim = 0; lim <= 10; lim++) {
        if (DFS(0)) {
            break;
        }
    }
    std::cout << "Case " << kase << ": " << lim << '\n';
    return;
}

int main() {
    while (std::cin >> n && n) std::cin >> m, mian();
    return 0;
}