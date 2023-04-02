#include <iostream>

typedef char chr;

const int maxT = 10;
const int maxN = 10;
const int maxM = 10;

int id, T;
int n, m;
chr a[maxN + 10][maxM + 10];
int rx1, ry1;
int rx2, ry2;
int bx, by;

namespace s14 {
    const int dx[5] = {0, 0, 1, -1, 0};
    const int dy[5] = {0, 1, 0, 0, -1};

    bool canmove(int x, int y, int x_, int y_) {
        for (int i = 1; i <= 4; i++) {
            int xx = x + dx[i];
            int yy = y + dy[i];
            if (xx < 1 || xx > n) continue;
            if (yy < 1 || yy > m) continue;
            if (a[xx][yy] != '#' && ((xx != x_) || (yy != y_))) return true;
        }
        return false;
    }

    void main() {
        if (canmove(rx1, ry1, rx2, ry2) == false && canmove(rx2, ry2, rx1, ry1) == false) {
            std::cout << "Black 0" << '\n';
        } else {
            std::cout << "Tie" << '\n';
        }
        return;
    }
}

namespace s56 {
    int abs(int x) {
        if (x < 0) x = - x;
        return x;
    }

    bool near() {
        int dif = abs(rx1 - bx) + abs(ry1 - by);
        if (dif == 1) {
            return true;
        } else {
            return false;
        }
    }

    void main() {
        if (rx1 == n) {
            rx1 = rx2;
            ry1 = ry2;
        }
        if (near()) {
            std::cout << "Red 1" << '\n';
            return;
        }
        if (rx1 >= bx) {
            std::cout << "Black " << (bx - 1) * 2 << '\n';
            return;
        }
        
    }
}

namespace s79 {
    void main() {
        
    }
}

namespace s1013 {
    bool DFSR(int now, int lim, int rx1, int ry1, int rx2, int ry2, int bx, int by);
    bool DFSB(int now, int lim, int rx1, int ry1, int rx2, int ry2, int bx, int by);

    const int dxr[5] = {0, 1, -1, 0, 0};
    const int dyr[5] = {0, 0, 0, 1, -1};
    const int dxb[5] = {0, 0, 0, -1};
    const int dyb[5] = {0, 1, -1, 0};

    bool canmoveR(int x, int y, int x_, int y_) {
        for (int i = 1; i <= 4; i++) {
            int xx = x + dxr[i];
            int yy = y + dyr[i];
            if (xx < 1 || xx > n) continue;
            if (yy < 1 || yy > m) continue;
            if (a[xx][yy] != '#' && ((xx != x_) || (yy != y_))) return true;
        }
        return false;
    }

    bool canmoveB(int x, int y) {
        for (int i = 1; i <= 3; i++) {
            int xx = x + dxb[i];
            int yy = y + dyb[i];
            if (xx < 1 || xx > n) continue;
            if (yy < 1 || yy > m) continue;
            if (a[xx][yy] != '#') return true;
        }
        return false;
    }

    bool check(int rx1, int ry1, int rx2, int ry2, int bx, int by) {
        if (bx == rx1 && by == ry1) return true;
        if (bx == rx2 && by == ry2) return true;
        if (bx == 1) return true;
        if (canmoveR(rx1, ry1, rx2, ry2) == false && canmoveR(rx2, ry2, rx1, ry2) == false) return true;
        if (canmoveB(bx, by) == false) return true;
        return false;
    }

    bool DFSR(int now, int lim, int rx1, int ry1, int rx2, int ry2, int bx, int by) {
        if (now > lim) {
            if (check(rx1, ry1, rx2, ry2, bx, by)) return true;
            return false;
        }
        for (int i = 1; i <= 4; i++) {
            int xx = rx1 + dxr[i];
            int yy = ry1 + dyr[i];
            if (xx < 1 || xx > n) continue;
            if (yy < 1 || yy > m) continue;
            if (a[xx][yy] != '#' && ((xx != rx2) || (yy != ry2))) {
                if (DFSB(now + 1, lim, xx, yy, rx2, ry2, bx, by)) {
                    return true;
                }
            }
        }
        for (int i = 1; i <= 4; i++) {
            int xx = rx2 + dxr[i];
            int yy = ry2 + dyr[i];
            if (xx < 1 || xx > n) continue;
            if (yy < 1 || yy > m) continue;
            if (a[xx][yy] != '#' && ((xx != rx1) || (yy != ry1))) {
                if (DFSB(now + 1, lim, rx1, ry1, xx, yy, bx, by)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool DFSB(int now, int lim, int rx1, int ry1, int rx2, int ry2, int bx, int by) {
        if (now > lim) {
            if (check(rx1, ry1, rx2, ry2, bx, by)) {
                return true;
            } else {
                return false;
            }
        }
        for (int i = 1; i <= 3; i++) {
            int xx = bx + dxb[i];
            int yy = by + dyb[i];
            if (xx < 1 || xx > n) continue;
            if (yy < 1 || yy > m) continue;
            if (a[xx][yy] != '#') {
                if (DFSR(now + 1, lim, rx1, ry1, rx2, ry2, xx, yy)) {
                    return true;
                }
            }
        }
        return false;
    }

    void main(int lim) {
        for (int i = 1; i <= lim; i++) {
            if (DFSR(1, i, rx1, ry1, rx2, ry2, bx, by)) {
                if (i & 1) {
                    std::cout << "Red " << i << '\n';
                } else {
                    std::cout << "Black " << i << '\n';
                }
                return;
            }
        }
        std::cout << "Tie" << '\n';
        return;
    }
}

void mian() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) std::cin >> a[i][j];
    rx1 = ry1 = 0;
    rx2 = ry2 = 0;
    bx = by = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == '.') continue;
            if (a[i][j] == '#') continue;
            if (a[i][j] == 'X') {
                bx = i;
                by = j;
            }
            if (a[i][j] == 'O') {
                if (rx1 == 0) {
                    rx1 = i;
                    ry1 = j;
                } else {
                    rx2 = i;
                    ry2 = j;
                }
            }
        }
    }
    if (id <= 4) s14::main();
    //else if (id <= 6) s56::main();
    //else if (id <= 9) s79::main();
    else if (10 <= id && id <= 13) s1013::main(9);
    else s1013::main(n * m * 2);
    return;
}

int main() {
    freopen("zu.in", "r", stdin);
    freopen("zu.out", "w", stdout);
    std::cin >> id >> T;
    while (T--) mian();
    return 0;
}