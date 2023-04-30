#include <iostream>

const int maxN = 2e5;
const int maxM = 2e5;
const int maxQ = 2e5;

int n, m, q;
int x, y;
int a[maxN + maxM + 10];
bool ok = true;

bool near(int x, int y, int a, int b) {
    int x_;
    int y_;
    if (a > b) {
        x_ = x - 1;
        y_ = y + 1;
    } else {
        x_ = x + 1;
        y_ = y - 1;
    }
    if (1 > x_ || x_ > 2 * n) return false;
    if (1 > y_ || y_ > 2 * m) return false;
    return true;
}

int main() {
    std::cin >> n >> m >> q;
    /*
    for (int i = 1; i <= n * 2; i++) {
        for (int j = 1; j <= m * 2; j++) {
            if ((i + j) & 1) {
                std::cout << 0 << ' ';
            } else {
                std::cout << (i - j) / 2 + m << ' ';
            }
        }
        std::cout << '\n';
    }
    */
    for (int i = 1; i <= q; i++) {
        std::cin >> x >> y;
        int r = (x - y) / 2 + m;
        int t = (x & 1) ? 1 : 2;
        /*
        printf("(%d, %d) at row %d, type = %d\n", x, y, r, t);
        printf("row[%d] has %d\n", r - 1, a[r - 1]);
        printf("row[%d] has %d\n", r, a[r]);
        printf("row[%d] has %d\n", r + 1, a[r + 1]);
        */
        
        if (a[r] && a[r] != t) ok = false;
        if (near(x, y, r, r + 1)) if (a[r + 1] && a[r + 1] != t) ok = false;
        if (near(x, y, r, r - 1)) if (a[r - 1] && a[r - 1] != t) ok = false;
        
        //if (a && a != t) ok = false;
        if (ok) {
            std::cout << "YES" << '\n';
        } else {
            std::cout << "NO" << '\n';
        }
        a[r] = t;
        if (near(x, y, r, r - 1)) a[r - 1] = t;
        if (near(x, y, r, r + 1)) a[r + 1] = t;
    }
    return 0;
}