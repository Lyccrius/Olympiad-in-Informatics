#include <iostream>

const int maxN = 1e3;
const int maxP = 1e7;

int T;
int p;
int phi[maxP + 10];

void calcPhi(int n) {
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (phi[i]) continue;
        for (int j = i; j <= n; j += i) {
            if (!phi[j]) phi[j] = j;
            phi[j] = phi[j] / i * (i - 1);
        }
    }
    return;
}

int pow(int a, int b, int mod) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1ll * ret * a % mod;
        a = 1ll * a * a % mod;
        b = b / 2;
    }
    return ret;
}

int solve(int mod) {
    if (mod == 1) return 0;
    return pow(2, solve(phi[mod]) + phi[mod], mod);
}

void mian() {
    std::cin >> p;
    std::cout << solve(p) << '\n';
    return;
}

int main() {
    calcPhi(maxP);
    std::cin >> T;
    while (T--) mian();
    return 0;
}