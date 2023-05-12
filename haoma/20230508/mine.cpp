#include <iostream>
#include <algorithm>

typedef char chr;

const int maxW = 300;
const int maxH = 300;
const int dx[10] = {0, -1, -1, -1, 0, 0, 0, 1, 1, 1};
const int dy[10] = {0, -1, 0, 1, -1, 0, 1, -1, 0, 1};

int w, h;
chr a[maxW + 10][maxH + 10];

namespace S1 {
    bool is() {
        return (w <= 3) && (h <= 3);
    }

    void mian() {
        
        return;
    }
}

namespace S2 {
    bool is() {
        return (w == 1) || (h == 1);
    }

    void mian() {
        if (w > h) {
            for (int i = 1; i <= w; i++) a[1][i] = a[i][1];
            std::swap(w, h);
        }
        int l = 1;
        int r = h;
    }
}

int main() {
    freopen("mine.in", "r", stdin);
    freopen("mine.out", "w", stdout);
    std::cin >> w >> h;
    for (int i = 1; i <= w; i++) {
        for (int j = 1; j <= h; j++) {
            std::cin >> a[i][j];
        }
    }
    //if (S1::is()) S1::mian();
    //else if (S2::is()) S2::mian();
    for (int i = 1; i <= w; i++) {
        for (int j = 1; j <= h; j++) {
            std::cout << a[i][j];
        }
        std::cout << '\n';
    }
    return 0;
}