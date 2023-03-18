#include <iostream>
#include <cmath>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxQ = 1e5;
const int maxR = 1e7;
const int tot[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int Q;
lxl r[maxQ + 10];
lxl t[maxQ + 10];

int D[maxR + 10], M[maxR + 10], Y[maxR + 10];

bool run(int y) {
    if (y < 0) y++;
    if (y <= 1582) {
        if (y % 4 == 0) {
            return true;
        } else {
            return false;
        }
    } else {
        if (y % 400 == 0) {
            return true;
        } else if (y % 100 == 0) {
            return false;
        } else if (y % 4 == 0) {
            return true;
        } else {
            return false;
        }
    }
}

void getNext(int &d, int &m, int &y) {
    if (d == 4 && m == 10 && y == 1582) {
        d = 15;
        m = 10;
        y = 1582;
        return;
    }
    d++;
    if (d > tot[m] + (m == 2 && run(y))) {
        d = 1;
        m++;
    }
    if (m > 12) {
        m = 1;
        y++;
    }
    if (y == 0) {
        y = 1;
    }
    return;
}

int main() {
    promote();
    int d = 1;
    int m = 1;
    int y = - 4713;
    for (int i = 0; i <= maxR; i++) {
        D[i] = d;
        M[i] = m;
        Y[i] = y;
        getNext(d, m, y);
    }
    std::cin >> Q;
    for (int i = 1; i <= Q; i++) {
        std::cin >> r[i];
        if (r[i] > maxR) {
            lxl c = std::ceil(1.0 * (r[i] - maxR) / 146097);
            r[i] -= c * 146097;
            t[i] += c * 400;
        }
        if (Y[r[i]] > 0) {
            std::cout << D[r[i]] << ' ' << M[r[i]] << ' ' << Y[r[i]] + t[i] << '\n';
        } else {
            std::cout << D[r[i]] << ' ' << M[r[i]] << ' ' << - Y[r[i]] << ' ' << "BC" << '\n';
        }
    }
    return 0;
}