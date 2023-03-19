#include <iostream>
#include <vector>

typedef std::vector<int> vic;

int a, b;
int f[20][10];

int abs(int x) {
    return x > 0 ? x : - x;
}

void init() {
    for (int j = 0; j <= 9; j++) f[1][j] = 1;
    for (int i = 2; i <= 10; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int k = 0; k <= 9; k++) {
                if (abs(j - k) >= 2) {
                    f[i][j] += f[i - 1][k];
                }
            }
        }
    }
    return;
}

int solve(int n) {
    if (!n) return 0;
    vic bit;
    int ret = 0;
    int last = - 2;
    while (n) bit.push_back(n % 10), n /= 10;
    for (int i = 0; i < bit.size() - 1; i++) {
        for (int j = 1; j <= 9; j++) {
            ret += f[i + 1][j];
        }
    }
    for (int i = bit.size() - 1; i >= 0; i--) {
        int now = bit[i];
        for (int j = (i == (bit.size() - 1)); j < now; j++) {
            if (abs(j - last) >= 2) {
                ret += f[i + 1][j];
            }
        }
        if (abs(now - last) >= 2) last = now;
        else break;
        if (i == 0) ret++;
    }
    return ret;
}

int main() {
    std::cin >> a >> b; init();
    std::cout << solve(b) - solve(a - 1);
    return 0;
}