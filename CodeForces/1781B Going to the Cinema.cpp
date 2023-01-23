#include <iostream>
#include <algorithm>

const int maxN = 2e5;

int t;

int n;
int a[maxN + 10];

void mian() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    std::sort(a + 1, a + n + 1);
    int ans = 0;
    a[0] = -1;
    a[n + 1] = n + 1;
    for (int i = 0; i <= n; i++) {
        if (a[i] <= i - 1 && a[i + 1] > i) ans++;
    }
    //if (dif == false && a[1] < n) ans ++;
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}