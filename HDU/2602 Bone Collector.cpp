#include <iostream>
#include <algorithm>

const int maxN = 1000;
const int maxV = 1000;

int t;
int n, V;
int w[maxN + 10];
int v[maxN + 10];
int f[maxN + 10];

void mian() {
    std::fill(f, f + sizeof(f) / 4, 0);
    std::cin >> n >> V;
    for (int i = 1; i <= n; i++) std::cin >> w[i];
    for (int i = 1; i <= n; i++) std::cin >> v[i];
    for (int i = 1; i <= n; i++) {
        for (int j = V; j >= v[i]; j--) {
            f[j] = std::max(f[j], f[j - v[i]] + w[i]);
        }
    }
    for (int i = 1; i <= V; i++) f[0] = std::max(f[0], f[i]);
    std::cout << f[0] << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}