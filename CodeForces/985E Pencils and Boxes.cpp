#include <iostream>
#include <algorithm>

const int maxN = 5e5;

int n, k, d;
int a[maxN + 10];
int f[maxN + 10];

int main() {
    std::cin >> n >> k >> d;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    std::sort(a + 1, a + n + 1); f[0] = true;
    for (int i = 1, j = 1; i <= n; i++) {
        if (f[i - 1]) {
            j = std::max(j, i + k - 1);
            while (j <= n && a[j] - a[i] <= d) {
                f[j] = true; j++;
            }
        }
    }
    if (f[n]) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
    return 0;
}