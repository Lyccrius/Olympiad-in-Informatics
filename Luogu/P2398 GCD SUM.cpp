#include <iostream>

typedef long long lxl;

const int maxN = 1e5;

int n;
int phi[maxN + 10];
lxl pre[maxN + 10];
lxl ans;

void calcPhi() {
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

int main() {
    std::cin >> n;
    calcPhi();
    for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + phi[i];
    for (int i = 1; i <= n; i++) ans += (2ll * pre[n / i] - 1) * i;
    std::cout << ans << '\n';
    return 0;
}