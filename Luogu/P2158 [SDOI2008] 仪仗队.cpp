#include <iostream>

const int maxN = 40000;

int N;
int phi[maxN + 10];
int ans;

void calcPhi() {
    phi[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (phi[i]) continue;
        for (int j = i; j <= N; j += i) {
            if (!phi[j]) phi[j] = j;
            phi[j] = phi[j] / i * (i - 1);
        }
    }
    /*
    for (int i = 1; i <= N; i++) {
        printf("phi[%d] = %d\n", i, phi[i]);
    }
    */
    return;
}

int main() {
    std::cin >> N;
    if (N == 1) {
        std::cout << 0 << '\n';
        return 0;
    }
    calcPhi();
    for (int i = 1; i < N; i++) ans += phi[i];
    std::cout << 2 * ans + 1 << '\n';
    return 0;
}