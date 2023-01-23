#include <iostream>
#include <cstring>

const int maxN = 100;

int t;
int n;
int a[maxN + 10];
int b[maxN + 10];

void mian() {
    int ans = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) {
        if ((i == 1) || ((a[i] & 1) != (a[i - 1] & 1))) ;
        else ans++;
    }
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}